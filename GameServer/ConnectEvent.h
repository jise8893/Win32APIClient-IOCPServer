#pragma once
#include "IocpEvent.h"
class ConnectEvent :public IocpEvent
{
public:
	virtual bool DisPatch(DWORD numOfBytes);
public:
	ConnectEvent();
	~ConnectEvent();
};

