#include "pch.h"
#include "AcceptEvent.h"
#include "Session.h"
#include "IocpCore.h"
#include "ServerCore.h"
AcceptEvent::AcceptEvent() : pSession(nullptr) 
{
	
}
AcceptEvent::~AcceptEvent()
{
	pSession = nullptr;
}

bool AcceptEvent::DisPatch(DWORD numOfBytes)
{
	//printf("Progress AcceptEvent Dispatch\n");
	SOCKADDR_IN sockAddress;
	int sizeOfSockAddr = sizeof(sockAddress);


	SetUpdateAcceptSocket(pSession->GetSocket(),pSession->GetIocpCore()->GetServerCore()->GetServerSocket() ); 
	//AcceptEx 호출 후 GetPeerName 호출 시 사용 MSDN
	
	if (SOCKET_ERROR == ::getpeername(pSession->GetSocket(), OUT reinterpret_cast<SOCKADDR*>(&sockAddress), &sizeOfSockAddr)) 
	{
		return false;
	}

	pSession->SetAddress(sockAddress); 
	pSession->ProcessConnect(numOfBytes);

	return true;
}
