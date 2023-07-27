#include "pch.h"
#include "ResMgr.h"
#include "PathMgr.h"
#include "Texture.h"
#include "func.h"
ResMgr::ResMgr()
{

}
ResMgr::~ResMgr()
{
	SafeDeleteMap(mMapRes);
}
shared_ptr<Texture> ResMgr::FindTexture(const wstring& strKey)
{
	map < wstring, shared_ptr<Texture>>::iterator itr = mMapRes.find(strKey);
	if (itr == mMapRes.end())
	{
		return nullptr;
	}
	return itr->second;
}

shared_ptr<Texture> ResMgr::LoadTexture(const wstring& strKey, const wstring& strRelativePath)
{
	shared_ptr<Texture> pTex = FindTexture(strKey); 
	if (pTex != nullptr)
	{
		return pTex;

	}
	wstring strFilePath = PathMgr::GetInst()->GetContentPath();
	strFilePath += strRelativePath; 
	shared_ptr<Texture> ptexture = make_shared<Texture>(); 
	ptexture->Load(strFilePath);  
	ptexture->SetKey(strKey); 
	ptexture->SetRelativePath(strRelativePath);  
	mMapRes.insert(make_pair(strKey, ptexture)); 
	ptexture = nullptr;
	return mMapRes[strKey];
}

