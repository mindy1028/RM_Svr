/*************************************************

Copyright:Lemon Mindy

File:RMThreadPool.h

Author:Mindy

Date:2022-4-10

Description:RM_Svr threadpool tool

Brief:Arbitrary parameter thread pool based on C++11, providing high-performance queue support

**************************************************/
#ifndef RM_THREAD_POOL_H
#define RM_THREAD_POOL_H
#pragma warning(disable: 4018)

#include "RMQueue.h"

#include <functional>
#include <thread>
#include <memory>
#include <vector>
#include <mutex>
#include <utility>
#include <future>
#include <chrono>       

namespace Rose_Mindy{
	template<typename T>
	class ThreadQueue
	{
	private:
		RM_Queue<T> m_queue;

		std::mutex m_mutex;
	public:
		ThreadQueue() {}
		ThreadQueue(ThreadQueue&&) {}
		~ThreadQueue() {}

		bool empty()
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			return m_queue.empty();
		}

		int size()
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			return m_queue.size_approx();
		}

		void enqueue(T& t)
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_queue.enqueue(t);
		}

		bool dequeue(T& t)
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			if (m_queue.empty())
				return false;
			if (!m_queue.try_dequeue(t))
				return false;
			return true;
		}
	};

	class RM_ThreadPool
	{
	private:
		class ThreadWorker
		{
		private:
			int m_id;
			RM_ThreadPool* m_pool;
		public:
			ThreadWorker(RM_ThreadPool* pool, const int _id) : m_pool(pool), m_id(_id) {
			}

			void operator()()
			{
				std::function<void()> func;
				bool dequeued; 
				while (!m_pool->m_shutdown)
				{
					{
						std::unique_lock<std::mutex> lock(m_pool->m_conditional_mutex);
						if (m_pool->m_queue.empty())
						{
							m_pool->m_conditional_lock.wait(lock);
						}

						dequeued = m_pool->m_queue.dequeue(func);
					}

					if (dequeued)
						func();
				}
			}
		};

		bool m_shutdown;
		ThreadQueue<std::function<void()>> m_queue;
		std::vector<std::thread> m_threads;
		std::mutex m_conditional_mutex;
		std::condition_variable	m_conditional_lock;
	public:
		RM_ThreadPool(const int thread_count = 4) : m_threads(std::vector<std::thread>(thread_count)) {
			Init();
		}

		RM_ThreadPool(const RM_ThreadPool&) = delete;
		RM_ThreadPool(const RM_ThreadPool&&) = delete;
		RM_ThreadPool& operator=(const RM_ThreadPool&) = delete;
		RM_ThreadPool& operator=(const RM_ThreadPool&&) = delete;

		void Init() {
			for (int i = 0; i < m_threads.size(); i++) {
				m_threads.at(i) = std::thread(ThreadWorker(this, i));
			}
		}

		void shutdown() {
			m_shutdown = true;
			m_conditional_lock.notify_all();

			for (int i = 0; i < m_threads.size(); i++) {
				m_threads.at(i).join();
			}
		}

		template <typename F, typename... Args>
		auto submit(F&& f, Args &&...args) -> std::future<decltype(f(args...))>
		{
			std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
			auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

			std::function<void()> warpper_func = [task_ptr]() {
				(*task_ptr)();
			};

			m_queue.enqueue(warpper_func);
			m_conditional_lock.notify_one();
			return task_ptr->get_future();
		}
	};
}

#endif