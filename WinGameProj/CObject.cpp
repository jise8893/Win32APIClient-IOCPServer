#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "RigidBody.h"

void CObject::CreateCollider()
{
	pCollider = make_shared<Collider>(shared_from_this());

}

void CObject::CreateAnimator()
{
	pAnimator = make_shared<Animator>(shared_from_this());
}

void CObject::CreateRigidBody()
{
	pRigidBody = make_shared<RigidBody>(shared_from_this());
}

void CObject::FinalUpdate()
{

	if (pCollider!= nullptr)
		pCollider->FinalUpdate();

	if (pRigidBody != nullptr)
		pRigidBody->FinalUpdate();
}

void CObject::Render(HDC hdc)
{
	

}

void CObject::ComponentRender(HDC hdc)
{
	if(pCollider!=nullptr)
		pCollider->Render(hdc);
	if (pAnimator != nullptr)
		pAnimator->Render(hdc);

}

void CObject::Init()
{
	if (pCollider != nullptr)
	{
		pCollider->SetOwner(shared_from_this()); 
	}

	if (pAnimator != nullptr)
	{
		pAnimator->SetOwner(shared_from_this());
	}
	if (pRigidBody != nullptr)
	{
		pRigidBody->SetOwner(shared_from_this());
	}

}

CObject::CObject() : mptPos{},mptScale{},mAlive(true),pAnimator(nullptr),pCollider(nullptr)
{
	
}

CObject::CObject(const shared_ptr<CObject> origin) :strName(origin->strName), mptPos(origin->mptPos), mptScale(origin->mptScale), pCollider(nullptr), mAlive(true)
{
	if (origin->pCollider)
	{
		pCollider = make_shared<Collider>(origin->pCollider); 
	}

	if (origin->pAnimator)
	{
		pAnimator = make_shared<Animator>(origin->pAnimator);
	}
}


CObject::~CObject()
{
	if (nullptr != pCollider)
		pCollider = nullptr;
	if (nullptr != pAnimator)
		pAnimator = nullptr;
}
