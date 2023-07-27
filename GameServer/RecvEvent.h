#pragma once
#include "IocpEvent.h"
class Session;
class RecvEvent : public IocpEvent
{
public:
	void SetSession(shared_ptr<Session> pSess) { pSession = pSess; }
	virtual bool DisPatch(DWORD numOfBytes);
private:
	shared_ptr<Session> pSession;
};

