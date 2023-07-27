#pragma once
#include <thread>
#include <functional>

class ThreadMgr
{
public:
	static ThreadMgr* GetInst() {
		static ThreadMgr mgr;
		return &mgr;
	}
public:
	void Join();
	void Launch(function<void(void)> callback);
private:
	ThreadMgr();
	~ThreadMgr();
private:
	mutex mutex;
	vector<thread> vThreads;

};

