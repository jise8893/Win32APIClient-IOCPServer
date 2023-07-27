#include "pch.h"
#include "Camera.h"
#include "CObject.h"
#include "Core.h"
Camera::Camera() : pTObj(nullptr),mLookAt(Vec2(0,0))
{
	Vec2 Resolution = Core::GetInst()->GetResolution();
	SetLookAt(Resolution/2.f);
}
Camera::~Camera()
{

}
void Camera::Update()
{
	if (pTObj)
	{
		if (pTObj->IsDead())
		{
			pTObj = nullptr;
		}
		else
		{
			mPrevLookAt = mLookAt;
			mLookAt = pTObj->GetPos(); 
		}
	}
	// ȭ�� �߾� ��ǥ�� ī�޶� lookat ���̰� ���
	CalDiff();
}

void Camera::CalDiff()
{
	Vec2 vResolution = Core::GetInst()->GetResolution(); 
	Vec2 center = vResolution / 2.f;
	mDiff=  mLookAt - center; 
}
