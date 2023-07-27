#include "pch.h"
#include "SendEvent.h"
#include "NetMgr.h"
bool SendEvent::DisPatch(DWORD numOfBytes)
{
	NetMgr::GetInst()->RegisterRecvEvent();

	return true;
}
