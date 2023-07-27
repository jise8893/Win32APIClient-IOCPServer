#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "CObject.h"
#include "Texture.h"
#include "TimeMgr.h"
#include "Camera.h"
void Animation::Update()
{
	if (mFinished)
		return;

	mfAccTime += TimeMgr::GetInst()->GetDelTime();
	if (mVecFrm[mCurFrm].fDuration < mfAccTime)
	{
		++mCurFrm;
		
		if (mCurFrm > mVecFrm.size()-1) 
		{
			mFinished = true; 
			mCurFrm = 0;
			mfAccTime = 0;
			return;
		}
		mfAccTime = mfAccTime - mVecFrm[mCurFrm-1].fDuration;
	
	}
}

void Animation::Render(HDC hdc)
{
	if (mFinished)
		return;

	shared_ptr<CObject> pObj = pAnimator.lock()->GetObj();
	Vec2 vPos=pObj->GetPos();

	vPos += mVecFrm[mCurFrm].vOffset;
	vPos = Camera::GetInst()->GetRenderPos(vPos);
	TransparentBlt(hdc,
		int(vPos.x - mVecFrm[mCurFrm].vSlice.x / 2.f),
		int(vPos.y - mVecFrm[mCurFrm].vSlice.y / 2.f),
		(int)mVecFrm[mCurFrm].vSlice.x,
		(int)mVecFrm[mCurFrm].vSlice.y,
		pATex->GetDC(),
		(int)mVecFrm[mCurFrm].vLeftTop.x,//자를 프레임 위치
		(int)mVecFrm[mCurFrm].vLeftTop.y,
		(int)mVecFrm[mCurFrm].vSlice.x,
		(int)mVecFrm[mCurFrm].vSlice.y,
		RGB(255, 0, 255)
	);

}


void Animation::Create(shared_ptr<Texture> pTex, Vec2 vLpos, Vec2 sliceSize, Vec2 vInterval, UINT frameSize,float fDuration)
{
	pATex = pTex;
	tAnimFrm tFrm = {};
	for (UINT i = 0; i < frameSize; i++)
	{
		
		tFrm.fDuration = fDuration; 
		tFrm.vInterval = vInterval; 
		tFrm.vLeftTop = vLpos + (vInterval * i); 
		tFrm.vSlice = sliceSize; 
		mVecFrm.push_back(tFrm); 
	}
}

Animation::Animation(const shared_ptr<Animator> pAnim) :mStrName{} ,pATex(nullptr),mfAccTime(0.f)
{
	pAnimator = pAnim;
	mCurFrm = 0;
	mFinished = false;
}

Animation::~Animation()
{
}
