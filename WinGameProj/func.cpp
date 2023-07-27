#include "pch.h"
#include "func.h"
#include "EventMgr.h"
void CreateObject(shared_ptr<CObject> pObj, GROUP_TYPE gtype)
{
	tEvent event = {};
	event.eType = EVENT_TYPE::CREATE_OBJECT;
	event.lParam = pObj;
	event.wParam = (DWORD_PTR)gtype;
	EventMgr::GetInst()->AddEvent(event);
}

void DeleteObject(shared_ptr<CObject> pObj) 
{
	tEvent event = {}; 
	event.eType = EVENT_TYPE::DELETE_OBJECT; 
	event.lParam = pObj; 
	EventMgr::GetInst()->AddEvent(event); 
}

void ChangeScene(SCENE_TYPE sType)
{
	tEvent event = {};
	event.eType = EVENT_TYPE::SCENE_CHANGE;
	event.wParam = (DWORD_PTR)sType;
	EventMgr::GetInst()->AddEvent(event);
}
