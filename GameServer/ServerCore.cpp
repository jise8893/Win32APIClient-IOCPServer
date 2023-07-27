#include "pch.h"
#include "ServerCore.h"
#include "IocpCore.h"
#include "Session.h"
shared_ptr<Session> ServerCore::CreateSession(SOCKET serverSocket)
{
	shared_ptr<Session> pSession = make_shared<Session>();

	pIocpCore->RegisterIocp(pSession->GetSocket());
	return pSession;
}

void ServerCore::AddSession(shared_ptr<Session> pSession)
{
	lock_guard<std::mutex> Lockguard(mutex);
	SOCKET socket=GetServerSocket();
	vSessions.push_back(pSession);
}

void ServerCore::BroadCast(BYTE* bytes)
{
	std::lock_guard<std::mutex> lockGuard(mutex);
	for (shared_ptr<Session>& pSession : vSessions)
	{
		

		Packet* packet =(Packet*) bytes;
		if (packet->id == 3) 
		{
			MoveToPacket* packet = (MoveToPacket*)bytes; 

			if ((pSession->GetSocket() == packet->socketId) ) //클라이언트 본인이 보낸 패킷은 전달 x
			{
				continue;
			}

		}

		
		pSession->mSendEvent.Init();
		SendEvent event; 
		WSABUF wsaBuf; 
		//wsaBuf.buf = 
		memcpy(pSession->mSendBuffer.Buffer(),bytes,packet->size);
			//(char*)&bytes; // 따로 생성해서 복사
		wsaBuf.buf = (char*)pSession->mSendBuffer.Buffer();
		wsaBuf.len = packet->size;
		DWORD numOfBytes = 0;
		if (WSASend(pSession->GetSocket(), &wsaBuf, 1, &numOfBytes, 0, &pSession->mSendEvent, nullptr))
		{
			int errCode = WSAGetLastError();
			if (errCode != WSA_IO_PENDING)
			{
				//WSASend(pSession->GetSocket(), &wsaBuf, 1, &numOfBytes, 0, &pSession->mSendEvent, nullptr);
				continue;
			}
		}
	}
}

void ServerCore::Start()
{
	pIocpCore = make_shared<IocpCore>();
	pIocpCore->Init();
	pIocpCore->SetServer(shared_from_this());

	mServerSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED); //Create Server Socket 
	pIocpCore->RegisterIocp(mServerSocket);

	SetReuseAddress(mServerSocket, true);
	SetLinger(mServerSocket, 0, 0);
	 
	memset(&servAdr, 0, sizeof(servAdr));

	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(8000);
	 
	if (bind(mServerSocket, (SOCKADDR*)&servAdr, sizeof(servAdr))) 
	{
		printf("Bind Error\n");
		return;
	}

	if (listen(mServerSocket, mBackLog))
	{
		printf("Listen Error\n");
		return;
	}
	for (int i = 0; i < 2; i++)
	{
		pIocpCore->RegisterAccept(mServerSocket); 
	}



}

void ServerCore::DisPatch()
{
	
	DWORD numOfBytes = 0; 
	ULONG_PTR key = 0; 
	OVERLAPPED* overlapped = nullptr;
	IocpEvent* piocpEvent = nullptr; 
	if (::GetQueuedCompletionStatus(pIocpCore->GetIocpHandle(), &numOfBytes, &key, reinterpret_cast<LPOVERLAPPED*>(&overlapped), 0))
	{
		piocpEvent = (IocpEvent*)overlapped;
		pIocpCore->DisPatch(piocpEvent,numOfBytes); 
	}
	else {
		int errCode = WSAGetLastError();
		switch (errCode)
		{
		case WAIT_TIMEOUT:
			return;
		default:
			//pIocpCore->DisPatch(piocpEvent); 
			break;
		}
	}
	

}


ServerCore::ServerCore() :mBackLog(5)
{

}

ServerCore::~ServerCore()
{
}
