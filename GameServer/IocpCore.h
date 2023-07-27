#pragma once
class Session;
class ServerCore;
class AcceptEvent;
class IocpCore :public enable_shared_from_this<IocpCore>
{
private:
	HANDLE mIocpHandle;
	void RegisterAccept(SOCKET serverSocket);
	weak_ptr<ServerCore> pServerCore;

public: 
	IocpCore();
	~IocpCore();
	void DisPatch(class IocpEvent* iocpEvent, DWORD numOfBytes);
	void Init();
	shared_ptr<ServerCore> GetServerCore() { return pServerCore.lock(); }
	void SetServer(shared_ptr<ServerCore> pServ) { pServerCore = pServ; }
	HANDLE GetIocpHandle() { return mIocpHandle; }
	void RegisterIocp(SOCKET serverSocket);
	friend class ServerCore;
};

