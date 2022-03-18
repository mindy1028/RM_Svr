/*************************************************

Copyright:Lemon Mindy

File:RMQueue.h

Author:Mindy

Date:2022-3-19

Description:RM_Svr base queue file

Brief:Contains RM_Svr low-level queue struct

**************************************************/

#ifndef RMQUEUE_H
#define RMQUEUE_H
#include "RM_Svr_globaldef.h"
#include "RM_Svr_include.h"
#include <atomic>
#include <cassert>
#include <cstddef> 
#include <limits>
#include <memory>
#include <new> 
#include <stdexcept>

namespace Rose_Mindy {
    #ifndef __cpp_aligned_new
    #ifdef _WIN32
    #include <malloc.h>
    #else
    #include <stdlib.h> 
    #endif
    #endif
    
    #ifdef __cpp_lib_hardware_interference_size
        static constexpr size_t hardwareInterferenceSize =
            std::hardware_destructive_interference_size;
    #else
        static constexpr size_t hardwareInterferenceSize = 64;
    #endif
    
    #if defined(__cpp_aligned_new)
        template <typename T> using AlignedAllocator = std::allocator<T>;
    #else
        template <typename T> struct AlignedAllocator {
            using value_type = T;
    
            T* allocate(std::size_t n) {
                if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) {
                    throw std::bad_array_new_length();
                }
    #ifdef _WIN32
                auto* p = static_cast<T*>(_aligned_malloc(sizeof(T) * n, alignof(T)));
                if (p == nullptr) {
                    throw std::bad_alloc();
                }
    #else
                T* p;
                if (posix_memalign(reinterpret_cast<void**>(&p), alignof(T),
                    sizeof(T) * n) != 0) {
                    throw std::bad_alloc();
                }
    #endif
                return p;
            }
    
            void deallocate(T* p, std::size_t) {
    #ifdef WIN32
                _aligned_free(p);
    #else
                free(p);
    #endif
            }
        };
    #endif
    
        template <typename T> struct Slot {
            ~Slot() noexcept {
                if (turn & 1) {
                    destroy();
                }
            }
    
            template <typename... Args> void construct(Args &&... args) noexcept {
                static_assert(std::is_nothrow_constructible<T, Args &&...>::value,
                    "T must be nothrow constructible with Args&&...");
                new (&storage) T(std::forward<Args>(args)...);
            }
    
            void destroy() noexcept {
                static_assert(std::is_nothrow_destructible<T>::value,
                    "T must be nothrow destructible");
                reinterpret_cast<T*>(&storage)->~T();
            }
    
            T&& move() noexcept { return reinterpret_cast<T&&>(storage); }
    
    
            alignas(hardwareInterferenceSize) std::atomic<size_t> turn = { 0 };
            typename std::aligned_storage<sizeof(T), alignof(T)>::type storage;
        };
    
        template <typename T, typename Allocator = AlignedAllocator<Slot<T>>>
        class Queue {
        private:
            static_assert(std::is_nothrow_copy_assignable<T>::value ||
                std::is_nothrow_move_assignable<T>::value,
                "T must be nothrow copy or move assignable");
    
            static_assert(std::is_nothrow_destructible<T>::value,
                "T must be nothrow destructible");
    
        public:
            explicit Queue(const size_t capacity,
                const Allocator& allocator = Allocator())
                : capacity_(capacity), allocator_(allocator), head_(0), tail_(0) {
                if (capacity_ < 1) {
                    throw std::invalid_argument("capacity < 1");
                }
    
                slots_ = allocator_.allocate(capacity_ + 1);
    
                if (reinterpret_cast<size_t>(slots_) % alignof(Slot<T>) != 0) {
                    allocator_.deallocate(slots_, capacity_ + 1);
                    throw std::bad_alloc();
                }
                for (size_t i = 0; i < capacity_; ++i) {
                    new (&slots_[i]) Slot<T>();
                }
                static_assert(
                    alignof(Slot<T>) == hardwareInterferenceSize,
                    "Slot must be aligned to cache line boundary to prevent false sharing");
                static_assert(sizeof(Slot<T>) % hardwareInterferenceSize == 0,
                    "Slot size must be a multiple of cache line size to prevent "
                    "false sharing between adjacent slots");
                static_assert(sizeof(Queue) % hardwareInterferenceSize == 0,
                    "Queue size must be a multiple of cache line size to "
                    "prevent false sharing between adjacent queues");
                static_assert(
                    offsetof(Queue, tail_) - offsetof(Queue, head_) ==
                    static_cast<std::ptrdiff_t>(hardwareInterferenceSize),
                    "head and tail must be a cache line apart to prevent false sharing");
            }
    
            ~Queue() noexcept {
                for (size_t i = 0; i < capacity_; ++i) {
                    slots_[i].~Slot();
                }
                allocator_.deallocate(slots_, capacity_ + 1);
            }
    
    
            Queue(const Queue&) = delete;
            Queue& operator=(const Queue&) = delete;
    
            template <typename... Args> void emplace(Args &&... args) noexcept {
                static_assert(std::is_nothrow_constructible<T, Args &&...>::value,
                    "T must be nothrow constructible with Args&&...");
                auto const head = head_.fetch_add(1);
                auto& slot = slots_[idx(head)];
                while (turn(head) * 2 != slot.turn.load(std::memory_order_acquire))
                    ;
                slot.construct(std::forward<Args>(args)...);
                slot.turn.store(turn(head) * 2 + 1, std::memory_order_release);
            }
    
            template <typename... Args> bool try_emplace(Args &&... args) noexcept {
                static_assert(std::is_nothrow_constructible<T, Args &&...>::value,
                    "T must be nothrow constructible with Args&&...");
                auto head = head_.load(std::memory_order_acquire);
                for (;;) {
                    auto& slot = slots_[idx(head)];
                    if (turn(head) * 2 == slot.turn.load(std::memory_order_acquire)) {
                        if (head_.compare_exchange_strong(head, head + 1)) {
                            slot.construct(std::forward<Args>(args)...);
                            slot.turn.store(turn(head) * 2 + 1, std::memory_order_release);
                            return true;
                        }
                    }
                    else {
                        auto const prevHead = head;
                        head = head_.load(std::memory_order_acquire);
                        if (head == prevHead) {
                            return false;
                        }
                    }
                }
            }
    
            void push(const T& v) noexcept {
                static_assert(std::is_nothrow_copy_constructible<T>::value,
                    "T must be nothrow copy constructible");
                emplace(v);
            }
    
            template <typename P,
                typename = typename std::enable_if<
                std::is_nothrow_constructible<T, P&&>::value>::type>
                void push(P&& v) noexcept {
                emplace(std::forward<P>(v));
            }
    
            bool try_push(const T& v) noexcept {
                static_assert(std::is_nothrow_copy_constructible<T>::value,
                    "T must be nothrow copy constructible");
                return try_emplace(v);
            }
    
            template <typename P,
                typename = typename std::enable_if<
                std::is_nothrow_constructible<T, P&&>::value>::type>
                bool try_push(P&& v) noexcept {
                return try_emplace(std::forward<P>(v));
            }
    
            void pop(T& v) noexcept {
                auto const tail = tail_.fetch_add(1);
                auto& slot = slots_[idx(tail)];
                while (turn(tail) * 2 + 1 != slot.turn.load(std::memory_order_acquire))
                    ;
                v = slot.move();
                slot.destroy();
                slot.turn.store(turn(tail) * 2 + 2, std::memory_order_release);
            }
    
            bool try_pop(T& v) noexcept {
                auto tail = tail_.load(std::memory_order_acquire);
                for (;;) {
                    auto& slot = slots_[idx(tail)];
                    if (turn(tail) * 2 + 1 == slot.turn.load(std::memory_order_acquire)) {
                        if (tail_.compare_exchange_strong(tail, tail + 1)) {
                            v = slot.move();
                            slot.destroy();
                            slot.turn.store(turn(tail) * 2 + 2, std::memory_order_release);
                            return true;
                        }
                    }
                    else {
                        auto const prevTail = tail;
                        tail = tail_.load(std::memory_order_acquire);
                        if (tail == prevTail) {
                            return false;
                        }
                    }
                }
            }
    
        private:
            constexpr size_t idx(size_t i) const noexcept { return i % capacity_; }
    
            constexpr size_t turn(size_t i) const noexcept { return i / capacity_; }
    
        private:
            const size_t capacity_;
            Slot<T>* slots_;
    #if defined(__has_cpp_attribute) && __has_cpp_attribute(no_unique_address)
            Allocator allocator_ [[no_unique_address]];
    #else
            Allocator allocator_;
    #endif
    
    
            alignas(hardwareInterferenceSize) std::atomic<size_t> head_;
            alignas(hardwareInterferenceSize) std::atomic<size_t> tail_;
        };
    
        template <typename T,
            typename Allocator = AlignedAllocator<Slot<T>>>
    
            using RMQueue = Queue<T, Allocator>;
    }
#endif // !RMQUEUE_H