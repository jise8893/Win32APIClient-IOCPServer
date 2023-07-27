#include "pch.h"
#include "Animator.h"
#include "func.h"
#include "Animation.h"
#include "Texture.h"
shared_ptr<Animation> Animator::FindAnimation(const wstring& strName) 
{
	auto itr = mMapAnim.find(strName);
	if (itr == mMapAnim.end())
		return nullptr;
	return itr->second;
} 
void Animator::CreateAnimation(const wstring& strName,shared_ptr<Texture> pTex, Vec2 vLpos, Vec2 sliceSize, Vec2 vInterval, UINT frameSize,float fDuration)
{
	
	shared_ptr<Animation> pAni = FindAnimation(strName);
	assert(nullptr == pAni);
	 
	pAni = make_shared<Animation>(shared_from_this()); 
	pAni->SetName(strName); 
	pAni->Create(pTex,vLpos,sliceSize,vInterval,frameSize,fDuration); 
	mMapAnim.insert(make_pair(strName, pAni)); 
}
void Animator::Play(const wstring& strName,bool repeat)
{
	pCurAnim = FindAnimation(strName);
	mRepeat = repeat;
}
void Animator::Render(HDC hdc)
{
	if (pCurAnim != nullptr)
	{
		pCurAnim->Render(hdc);
	}
}
void Animator::Update()
{
	if (pCurAnim != nullptr)
	{
		pCurAnim->Update();
		if (mRepeat && pCurAnim->IsFinished())
		{
			pCurAnim->SetRepeat();
		}
	}
}
Animator::Animator(): pOwner(),pCurAnim(nullptr),mRepeat(false)
{
}

Animator::~Animator()
{
	SafeDeleteMap(mMapAnim); 
}

Animator::Animator(const shared_ptr<Animator> origin) :pOwner(),mMapAnim(origin->mMapAnim),mRepeat(origin->mRepeat)
{

}
Animator::Animator(const shared_ptr<CObject> pObj) :pOwner(), mMapAnim{},mRepeat(false)
{
	pOwner = pObj; 
}