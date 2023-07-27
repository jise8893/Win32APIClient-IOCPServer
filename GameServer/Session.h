#pragma once
#include "AcceptEvent.h"
#include "ConnectEvent.h"
#include "SendEvent.h"
#include "RecvEvent.h"
#include "RecvBuffer.h"
#include "SendBuffer.h"
#include "Packet.h"
class IocpCore;
class Session :public enable_shared_from_this<Session>
{
private:
	SOCKET socket;
	
	ConnectEvent mConnectEvent; 
	RecvEvent	mRecvEvent;
	
	weak_ptr<IocpCore> pIocpCore;
public:
	HANDLE GetHandle() { return reinterpret_cast<HANDLE>(socket); }
	SOCKET GetSocket() { return socket; }

	void SetIocpCore(shared_ptr<IocpCore> pIocp) { pIocpCore = pIocp; }
	shared_ptr<IocpCore> GetIocpCore() { return pIocpCore.lock(); }
	void InitEvent()
	{
		pAcceptEvent = new AcceptEvent();
		pAcceptEvent->Init();
		memset(&mConnectEvent, 0, sizeof(mConnectEvent));
		mRecvBuffer.Init();
	} 
	ConnectEvent& GetConnectEvent(){return mConnectEvent;}
	void SetAddress(SOCKADDR_IN addr) { sockAddress = addr; }
public:
	void ProcessConnect(DWORD numOfBytes);
	void RegisterRecv();
	void ProcessRecv(DWORD numOfBytes);
public:
	int ProcessData(BYTE* byte, int numOfBytes);
	void TranslatePacket(BYTE* buffer,int len);
public:
	void BroadCast(BYTE * packet);
public:
	SOCKADDR_IN sockAddress;
	RecvBuffer mRecvBuffer;
	SendBuffer mSendBuffer;
	AcceptEvent* pAcceptEvent;
	SendEvent mSendEvent;
public:
	Session();
	~Session();
};

