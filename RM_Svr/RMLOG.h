#ifndef RM_LOG
#define RM_LOG

#include "RM_Queue.h"
#include <thread>

// ��־������
class RM_Log_Producer
{
private:
	std::thread _proTh;
};
// ��־������
class RM_Log_ Consumer
{
private:
	std::thread _conTh;
};

class RM_Log_Handle
{
public:
	static RM_Log_Handle* get_Instance() {
		return m_Instance;
	}

private:
	RM_Log_Handle* m_Instance;
	RM_Log_Handle() {};
	~RM_Log_Handle() {};

private:
	RM_Queue<std::string> _logQueue;
};

RM_Log* RM_Log::m_Instance = new RM_Log();
#endif