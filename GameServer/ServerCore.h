#pragma once

class IocpCore;
class Session;
class ServerCore :public enable_shared_from_this<ServerCore>
{
private:
	shared_ptr<IocpCore> pIocpCore;
	SOCKET mServerSocket;
	SOCKADDR_IN servAdr;
	UINT mBackLog;
	vector<shared_ptr<Session>> vSessions;
	mutex mutex;
private:
	shared_ptr<Session> CreateSession(SOCKET serverSocket);
	friend class IocpCore;
public:
	void AddSession(shared_ptr<Session> pSession);
	void BroadCast(BYTE* bytes);
public:
	SOCKET GetServerSocket() { return mServerSocket; }
	void Start();
	void DisPatch();
	ServerCore();
	~ServerCore();
};

