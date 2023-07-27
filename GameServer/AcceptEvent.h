#pragma once
#include "IocpEvent.h"
class Session;
class AcceptEvent :public IocpEvent 
{
public:
	AcceptEvent(); 
	~AcceptEvent();
	void SetSession(shared_ptr<Session> pSess) { pSession = pSess; }
	virtual bool DisPatch(DWORD numOfBytes);
public:

	shared_ptr<Session> pSession; 
};

