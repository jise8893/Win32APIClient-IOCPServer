#include "pch.h"
#include "EventMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "CObject.h"
void EventMgr::Update()
{
	//Execute to Delete Object
	for (size_t i = 0; i < vecDeadObj.size(); i++)
	{

	}

	for (size_t i = 0; i < mVecEvent.size(); i++)
	{
		Execute(mVecEvent[i]);
	}
	mVecEvent.clear();
}
void EventMgr::Execute(const tEvent& tEvt)
{
	switch (tEvt.eType)
	{
	case EVENT_TYPE::CREATE_OBJECT: 
	{
		//LPARAM OBJECT ADDRESS
		//RPARAM GROUP_TYPE 
		shared_ptr<Scene> curScene = SceneMgr::GetInst()->GetCurScene();
		curScene->AddObject(tEvt.lParam, (GROUP_TYPE)tEvt.wParam); 

	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		//lparam object address
		//wparam change object state -> dead
		shared_ptr<CObject> pObj = tEvt.lParam;
		pObj->SetDead();
		vecDeadObj.push_back(pObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		//wParam SCENE_TYPE
		SceneMgr::GetInst()->ChangeScene((SCENE_TYPE)tEvt.wParam);
		
	}
		break;
	}
}
EventMgr::EventMgr()
{

}
EventMgr::~EventMgr()
{

}