#pragma once
#include "CObject.h" 
class Monster : public CObject
{
private:
	float mSpeed;
	Vec2 mCenterPos;
	float mDistance;
	int mDir;
	int mHP;
public:
	virtual void Update();
	float GetSpeed() { return mSpeed; }
	void SetSpeed(float _speed) { mSpeed = _speed; }
	void SetCenterPos(Vec2 cntpos) { mCenterPos = cntpos; }
	virtual void Render(HDC _hdc);
	void AllocComp();
	virtual shared_ptr<CObject> Clone()
	{
		shared_ptr<Monster> pObj = make_shared<Monster>(shared_from_this());
		pObj->Init();
		return pObj;
	}
public:
	virtual void OnCollision(shared_ptr<Collider> pOther);
	virtual void EnterCollsion(shared_ptr<Collider> pOther);
	virtual void ExitCollision(shared_ptr<Collider> pOther);
public:
	Monster();
	~Monster();
	Monster(const shared_ptr<CObject> origin) :CObject(origin)
	{
		shared_ptr<Monster> pObj = static_pointer_cast<Monster>(origin);
		mDir = pObj->mDir;
		mHP = pObj->mHP;
		mDistance = pObj->mDistance;
		mCenterPos = pObj->mCenterPos;
		mSpeed = pObj->mSpeed;
	}
};

