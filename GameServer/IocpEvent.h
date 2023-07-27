#pragma once
enum class IocpEventType :INT8{
	Connect,
	Accept,
	Recv,
	Send,
	END,
};

class IocpEvent : public OVERLAPPED
{	
public:
	IocpEventType mEventType;
	void Init();
	void SetEventType(IocpEventType eType) { mEventType = eType; }
public:
	IocpEvent();
	virtual ~IocpEvent() {}
	virtual bool DisPatch(DWORD numOfBytes) = 0;
};

