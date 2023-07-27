#pragma once
class Packet;
class MoveToPacket; 

#include "SendEvent.h"
#include "RecvEvent.h"
#include "RecvBuffer.h"
struct userData {
	int pState;
	Vec2 pos;
};
class NetMgr
{
	SINGLE(NetMgr)
public:
	HANDLE IocpHandle;
	SOCKET clientSocket;
	SOCKADDR_IN serverAddr;
public:
	SendEvent mSendEvent;
	RecvEvent mRecvEvent;
	vector<Packet*> vPacket;
public:
	RecvBuffer mRecvBuffer;
	int myId;

public:
	//networking
	mutex mutex;
	map<int, userData> mMapOthers; // socketId,userData
public:
	void RegisterRecvEvent();
	void ProcessRecvEvent(DWORD numOfBytes);
	int ProcessData(BYTE* byte, int numOfBytes);
	void TranslatePacket(BYTE* buffer, int len);
	void SendMoveToPacket(MoveToPacket header);
public:
	void EditUserData(BYTE* buffer, int len);
public:
	userData GetUserData(int socketId);
public:
	void Init();
	void DisPatch();
};

