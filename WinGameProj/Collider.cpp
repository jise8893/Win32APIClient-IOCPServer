#include "pch.h"
#include "Collider.h"
#include "CObject.h"
#include "Core.h"
#include "SelectGdi.h"
#include "Camera.h"
atomic<UINT> Collider::sID = 0; //mmo를 위한 동시성 

void Collider::FinalUpdate()
{
	shared_ptr<CObject> pObj = pOwner.lock();
	Vec2 objectPos = pObj->GetPos();
	mFinalPos =objectPos + mOffsetPos;
	assert(mCol >= 0);
}

void Collider::Render(HDC hdc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;
	if (mCol)
	{
		ePen = PEN_TYPE::RED; 
	}
	SelectGdi brush(hdc, BRUSH_TYPE::HOLLOW); 
	SelectGdi pen(hdc,ePen); 
	mFinalPos = Camera::GetInst()->GetRenderPos(mFinalPos);
	Rectangle(hdc,(int)mFinalPos.x - mScale.x/2.f, (int)mFinalPos.y - mScale.y/2.f, (int)mFinalPos.x + mScale.x / 2.f, (int)mFinalPos.y + mScale.y / 2.f);

}

void Collider::OnCollision(shared_ptr<Collider> pOther)
{
	shared_ptr<CObject> pObj = pOwner.lock();
	pObj->OnCollision(pOther);
}

void Collider::EnterCollision(shared_ptr<Collider> pOther)
{
	shared_ptr<CObject> pObj = pOwner.lock();
	pObj->EnterCollsion(pOther);
	mCol++;
}

void Collider::ExitCollision(shared_ptr<Collider> pOther)
{
	shared_ptr<CObject> pObj = pOwner.lock();
	pObj->ExitCollision(pOther); 
	mCol--; 
}

Collider::Collider(const shared_ptr<CObject> obj)
{
	pOwner = obj;
	mid = sID.fetch_add(1);
	mCol = 0;
}

Collider::Collider(const shared_ptr<Collider> origin)
	:pOwner(origin->pOwner), mOffsetPos(origin->mOffsetPos), mScale(origin->mScale), mid(sID.fetch_add(1)), mCol(0)
{
}



Collider::~Collider()
{
	pOwner.lock() = nullptr;
}
