#pragma once
class CObject;
struct tEvent
{
	EVENT_TYPE eType;
	shared_ptr<CObject> lParam; 
	DWORD_PTR wParam;
};
class EventMgr
{
	SINGLE(EventMgr)
private:
	vector<tEvent> mVecEvent;
	vector <shared_ptr<CObject>> vecDeadObj;

public:
	void Update();
	void Execute(const tEvent& tEvt);
public:
	void AddEvent(const tEvent& tEvt)
	{
		mVecEvent.push_back(tEvt);
	}
};

