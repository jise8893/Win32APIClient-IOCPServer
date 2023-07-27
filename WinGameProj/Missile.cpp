#include "pch.h"
#include "Missile.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "CObject.h"
#include "func.h"
#include "Camera.h"
Missile::Missile():mTheta(PI/2.f), mDir(Vec2(1.f,1.f))
{
	mDir.Normalize();
}

Missile::~Missile() 
{
}

void Missile::Update() 
{ 
	Vec2 vPos = GetPos();
	vPos.x += 600.f * mDir.x * TimeMgr::GetInst()->GetDelTime();
	vPos.y -= 600.f * mDir.y * TimeMgr::GetInst()->GetDelTime();
	SetPos(vPos);
}

void Missile::Render(HDC hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	vPos = Camera::GetInst()->GetRenderPos(vPos);
	Ellipse(hdc, (int)(vPos.x - vScale.x / 2), (int)(vPos.y - vScale.y / 2), (int)(vPos.x + vScale.x / 2), (int)(vPos.y + vScale.y / 2));
	ComponentRender(hdc); 
}

void Missile::EnterCollsion(shared_ptr<Collider> pOther)
{
	shared_ptr<CObject> pObj = pOther->GetObj();
 	if (pObj->GetName() == L"Monster")
	{
		DeleteObject(shared_from_this());
	}
}

void Missile::ExitCollsion(shared_ptr<Collider> pOther)
{
}

void Missile::Init()
{
	CreateCollider(); 
	GetCollider()->SetScale(Vec2(15, 15)); 
	
}

void Missile::SetDir(Vec2 _dir)
{
	mDir = _dir;
	mDir.Normalize();
}
