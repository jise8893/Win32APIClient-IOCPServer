#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "func.h"
void Monster::Update()
{
	Vec2 vPos = GetPos();  
	//진행방향 시간당 speed 이동
	vPos.x += TimeMgr::GetInst()->GetDelTime() * mSpeed * mDir;

	float dist = abs(mCenterPos.x - vPos.x) - mDistance;
	if (dist > 0.f)
	{
		//방향변경
		mDir *= -1;
		vPos.x += (float)TimeMgr::GetInst()->GetDelTime() * mSpeed * mDir; 
	}
	//SetPos(vPos); 

}

void Monster::Render(HDC hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	vPos = Camera::GetInst()->GetRenderPos(vPos); 
	Rectangle(hdc, (int)(vPos.x - vScale.x / 2), (int)(vPos.y - vScale.y / 2), (int)(vPos.x + vScale.x / 2), (int)(vPos.y + vScale.y / 2));
	ComponentRender(hdc);
}

void Monster::AllocComp()
{
	CreateCollider();
	shared_ptr<Collider> pCollider=GetCollider();
	pCollider->SetOffsetPos(Vec2(0, 0));
	pCollider->SetScale(Vec2(50, 50));
}

void Monster::OnCollision(shared_ptr<Collider> pOther)
{

}

void Monster::EnterCollsion(shared_ptr<Collider> pOther)
{
	shared_ptr<CObject> pObj = pOther->GetObj();
	if (pObj->GetName() == L"Missile")
	{
		mHP -= 20;
		if (mHP <= 0)
		{
			DeleteObject(shared_from_this()); 
		}

	}
}

void Monster::ExitCollision(shared_ptr<Collider> pOther)
{

}

Monster::Monster() :
			mSpeed(100.f), 
			mCenterPos(Vec2{0.f,0.f}), 
			mDistance(100.f),
			mDir(1),
			mHP(100)
{
}

Monster::~Monster() 
{
}
