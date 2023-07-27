#include "pch.h"
#include "ThreadMgr.h"

void ThreadMgr::Join()
{
	for (thread& t : vThreads)
	{
		if (t.joinable())
			t.join();
	}
	vThreads.clear();
}

void ThreadMgr::Launch(function<void(void)> callback)
{
	lock_guard<std::mutex> LockGurad(mutex);

	vThreads.push_back(thread([=]()
		{
			callback();
		}
	));
}



ThreadMgr::ThreadMgr()
{
}

ThreadMgr::~ThreadMgr()
{
}
