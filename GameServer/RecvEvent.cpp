#include "pch.h"
#include "RecvEvent.h"
#include "Session.h"
bool RecvEvent::DisPatch(DWORD numOfBytes)
{
	//printf("Progress RecvEvent Dispatch\n");
	pSession->ProcessRecv(numOfBytes);

	return true;
}
