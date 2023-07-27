#include "pch.h"
#include "ConnectEvent.h"

bool ConnectEvent::DisPatch(DWORD numOfBytes)
{
	return true;
}

ConnectEvent::ConnectEvent()
{
	SetEventType(IocpEventType::Connect);
}

ConnectEvent::~ConnectEvent()
{
}
