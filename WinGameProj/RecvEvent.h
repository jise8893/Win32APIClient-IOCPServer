#pragma once
#include "IocpEvent.h"

class RecvEvent : public IocpEvent
{
public:
	virtual bool DisPatch(DWORD numOfBytes);
private:

};

