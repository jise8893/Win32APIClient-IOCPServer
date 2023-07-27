#pragma once
#include "CObject.h"
class Missile :public CObject
{
private:
	float	mTheta;
	Vec2	mDir;
public:
	Missile();
	~Missile();
	Missile(const shared_ptr<CObject> origin) :CObject(origin) 
	{
		shared_ptr<Missile> pObj = static_pointer_cast<Missile>(origin);
		mTheta = pObj->mTheta;
		mDir = pObj->mDir;
	}
public:
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void EnterCollsion(shared_ptr<Collider> pOther);
	virtual void ExitCollsion(shared_ptr<Collider> pOther);
	void Init();
	virtual shared_ptr<CObject> Clone()
	{
		shared_ptr<Missile> pObj = make_shared<Missile>(shared_from_this());
		pObj->Init();
		return pObj;
	}
public:
	void SetDir(Vec2 _dir);

};

