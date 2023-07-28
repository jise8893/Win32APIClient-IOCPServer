#include "pch.h"
#include "Scene.h"
#include "CObject.h" 
#include "func.h"
void Scene::Render(HDC hdc)
{
	for (int i = 0; i < (int)GROUP_TYPE::END; i++)  
	{
		for (auto itr = mVecObjGroup[i].begin(); itr != mVecObjGroup[i].end();) 
		{
			shared_ptr<CObject> vObj = *itr;  
			if (!(vObj->IsDead()))
			{
				vObj->Render(hdc);
				itr++;
			}
			else
			{
				itr=mVecObjGroup[i].erase(itr);
			}
		}
	}
}

void Scene::Update()
{
	for (int i = 0; i < (int)GROUP_TYPE::END; i++)
	{
		
			lock_guard<std::mutex> lockGuard(mMutex);
			for (auto itr = mVecObjGroup[i].begin(); itr != mVecObjGroup[i].end(); itr++)
			{

				shared_ptr<CObject> vObj = *itr;
				if (!(vObj->IsDead()))
				{
					vObj->Update();
				}
			}
		

	}
}

void Scene::FinalUpdate()
{
	for (int i = 0; i < (int)GROUP_TYPE::END; i++) 
	{
		
			lock_guard<std::mutex> lockGuard(mMutex);
			for (auto itr = mVecObjGroup[i].begin(); itr != mVecObjGroup[i].end(); itr++)
			{

				shared_ptr<CObject> vObj = *itr;
				vObj->FinalUpdate();
			}
		

	}
}

const std::vector<shared_ptr<CObject>>& Scene::GetGroupObject(GROUP_TYPE gtype)
{
	// TODO: 여기에 return 문을 삽입합니다.
	return mVecObjGroup[(UINT)gtype];
}

void Scene::AddObject(shared_ptr<CObject> pObj, GROUP_TYPE gtype)
{
	lock_guard<std::mutex> lockGuard(mMutex);
	mVecObjGroup[(UINT)gtype].push_back(pObj);

}

void Scene::DeleteGroup(GROUP_TYPE gType)
{
	SafeDeleteVec(mVecObjGroup[(UINT)gType]);
}

void Scene::DeleteAll() 
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

Scene::Scene() :mStrName{}
{

}

Scene::~Scene()
{
	
	for (int i = 0; i < (int)GROUP_TYPE::END; i++)
	{
		for (auto itr = mVecObjGroup[i].begin(); itr != mVecObjGroup[i].end(); itr++)
		{
			*itr = nullptr;
		}
	}

}
