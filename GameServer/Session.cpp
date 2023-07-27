#include "pch.h"
#include "Session.h"
#include "IocpCore.h"
#include "ServerCore.h"
#include "Packet.h"
void Session::ProcessConnect(DWORD numOfBytes)
{
	GetIocpCore()->GetServerCore()->AddSession(shared_from_this());

	RegisterRecv(); //수신 등록

}

void Session::RegisterRecv()
{
	mRecvEvent.Init();
	mRecvEvent.SetSession(shared_from_this());
	WSABUF wsaBuf; 
	wsaBuf.buf =(char*) mRecvBuffer.GetWritePos(); 
	wsaBuf.len = mRecvBuffer.GetFreeSize();

	DWORD numOfBytes = 0;
	DWORD flags = 0;
	if (SOCKET_ERROR == ::WSARecv(socket, &wsaBuf, 1, &numOfBytes, &flags, &mRecvEvent, nullptr))
	{
		int errCode = ::WSAGetLastError();
		if (errCode != WSA_IO_PENDING)
		{
			//disconnect 등록
			mRecvEvent.SetSession(nullptr);
		}
	}

	 

}

void Session::ProcessRecv(DWORD numOfBytes)
{
	mRecvBuffer.OnWrite(numOfBytes);
	int processedLen = ProcessData(mRecvBuffer.GetReadPos(), numOfBytes);
	mRecvBuffer.OnRead(processedLen);

	RegisterRecv();
}

int Session::ProcessData(BYTE* byte, int numOfBytes)
{
	int processedLen = 0;

	while (true)
	{
		int dataSize = numOfBytes - processedLen;

		if (dataSize < sizeof(Packet))
			break;

		Packet header = *(reinterpret_cast<Packet*>(&byte[0]));
		if (dataSize < header.size)
			break;
		TranslatePacket(&byte[processedLen], header.size);
		processedLen += header.size;

	}
	//printf("processed len : %d \n", processedLen);
	return processedLen;
}

void Session::TranslatePacket(BYTE* buffer, int len)
{
	Packet* packet = (GetSocketNumPacket*)buffer;
	int packetId = packet->id;
	switch (packetId)
	{
		case 1:
		{
			//Recieved GetSocketNumberPacket id 1
			GetSocketNumPacket packet;
			packet.Init(socket);
			mSendEvent.Init();

			WSABUF wsaBuf;
			wsaBuf.buf = (char*)&packet;
			wsaBuf.len = packet.size;
			DWORD numOfBytes = 0;

			if(WSASend(socket, &wsaBuf, 1, &numOfBytes, 0, &mSendEvent, nullptr))
			{
				int errCode = WSAGetLastError(); 
				if (errCode != WSA_IO_PENDING) 
				{
					WSASend(socket, &wsaBuf, 1, &numOfBytes, 0, &mSendEvent, nullptr);

				}
			}


		}
			break;
		case 3:
		{
			//RecvPos Character
			MoveToPacket *packet;
			packet = (MoveToPacket*)buffer;
			Vec2 m = packet->pos;
			
			//printf("Move to Position x :%f y:%f  socketId: %d PLAYER STATE : %d\n", m.x, m.y,packet->socketId,packet->pState);
			//send BroadCast
			

			BroadCast(buffer);
		}
			break;
	}
}

void Session::BroadCast(BYTE* packet)
{
	GetIocpCore()->GetServerCore()->BroadCast(packet);
}

Session::Session()
{
	socket= ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);  
	InitEvent(); 
}

Session::~Session()
{
}
