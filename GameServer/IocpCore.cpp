#include "pch.h" 
#include "IocpCore.h"
#include "Session.h"
#include "ServerCore.h"
#include "IocpEvent.h"
#include "AcceptEvent.h"
void IocpCore::RegisterAccept(SOCKET serverSocket)
{
	shared_ptr<Session> pSess = pServerCore.lock()->CreateSession(serverSocket);
	pSess->pAcceptEvent->SetSession(pSess);

	pSess->SetIocpCore(shared_from_this());
	
	pSess->pAcceptEvent->SetEventType(IocpEventType::Accept);

	pServerCore.lock()->AddSession(pSess);

	DWORD bytesReceived = 0;
	if (false == AcceptEx(serverSocket,
		pSess->GetSocket() ,
		pSess->mRecvBuffer.GetWritePos(),
		0,
		sizeof(SOCKADDR_IN)+16,
		sizeof(SOCKADDR_IN)+16,
		&bytesReceived,
		pSess->pAcceptEvent
	))
	{
		const int errorCode = WSAGetLastError();

		if (errorCode != WSA_IO_PENDING)
		{
			RegisterAccept(serverSocket);
		}
	}  

}

IocpCore::IocpCore()
{
}

IocpCore::~IocpCore()
{

}

void IocpCore::DisPatch(IocpEvent* iocpEvent, DWORD numOfBytes)
{


	if (iocpEvent->DisPatch(numOfBytes) == false)
	{
		if (iocpEvent->mEventType == IocpEventType::Accept) //Accept 이벤트 실행 실패시
		{
			RegisterAccept(GetServerCore()->mServerSocket);
		}

	}


 
	


}

void IocpCore::Init()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData)!=0)
	{
		MessageBox(0, L"ERROR_WSA_STARTUP", 0, 0);
	}
	mIocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	
}

void IocpCore::RegisterIocp(SOCKET Socket)
{
	if (NULL == CreateIoCompletionPort((HANDLE)Socket, mIocpHandle, 0, 0))
		return;
}
