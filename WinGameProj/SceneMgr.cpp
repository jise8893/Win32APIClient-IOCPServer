#include "pch.h"
#include "SceneMgr.h"
#include "CSceneStart.h"
#include "Scene_Tool.h"
#include "EventMgr.h"
void SceneMgr::Init()
{
	//Scene »ý¼º
	mVecScene.resize((int)SCENE_TYPE::END);
	mVecScene[(int)SCENE_TYPE::START] = make_shared<CSceneStart>(); 
	mVecScene[(int)SCENE_TYPE::START]->SetName(L"StartScene");
	
	mVecScene[(int)SCENE_TYPE::TOOL] = make_shared<Scene_Tool>();
	mVecScene[(int)SCENE_TYPE::TOOL]->SetName(L"TooL");
	
	mCurScene = mVecScene[(int)SCENE_TYPE::START];
	mCurScene->Enter();

}

void SceneMgr::Update()
{
	mCurScene->Update();  
	mCurScene->FinalUpdate();
}




void SceneMgr::Render(HDC hdc)
{
	mCurScene->Render(hdc);
	
}

void SceneMgr::ChangeScene(SCENE_TYPE sType)
{
	mCurScene->Exit(); 
	mCurScene = nullptr; 
	mCurScene = mVecScene[(UINT)sType]; 
	mCurScene->Enter(); 
}




SceneMgr::SceneMgr() :mCurScene(nullptr),mVecScene{}
{
	
}

SceneMgr::~SceneMgr()
{
	for (int i = 0; i < (int)SCENE_TYPE::END; i++)
	{
		mVecScene[i] = nullptr;
	}
}


