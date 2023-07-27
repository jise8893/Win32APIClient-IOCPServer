#pragma once
#include "IocpEvent.h"
class SendEvent : public IocpEvent
{
public:
	virtual bool DisPatch(DWORD numOfBytes);
};

