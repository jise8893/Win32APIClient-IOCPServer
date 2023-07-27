#include "pch.h"
#include "RecvEvent.h"
#include "NetMgr.h"
bool RecvEvent::DisPatch(DWORD numOfBytes)
{
	NetMgr::GetInst()->ProcessRecvEvent(numOfBytes);
	NetMgr::GetInst()->RegisterRecvEvent();
	return true;
}
