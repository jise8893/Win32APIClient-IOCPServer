#pragma once
#include "Camera.h"
class Collider;
class Animator;
class RigidBody; 
class CObject : public enable_shared_from_this<CObject>
{
private:
	Vec2 mptPos;
	Vec2 mptScale;
	//Component
	shared_ptr<Collider> pCollider;
	shared_ptr<Animator> pAnimator;
	shared_ptr<RigidBody> pRigidBody;
	GROUP_TYPE gType;
	wstring strName;
	bool mAlive;
private:
	void SetDead() { mAlive = false; }
	friend class EventMgr;
public:
	bool IsDead() { return !mAlive; } 
	void SetPos(Vec2 pos) { mptPos.x = pos.x; mptPos.y = pos.y; }
	void SetScale(Vec2 scale) { mptScale.x = scale.x; mptScale.y = scale.y; }
	Vec2 GetPos() { return mptPos; }
	Vec2 GetScale() { return mptScale; }
	GROUP_TYPE GetGroupType() { return gType; }
	const wstring& GetName() { return strName; }
	void SetName(const wstring& _name) { strName = _name; }
public:
	void CreateCollider();
	shared_ptr<Collider> GetCollider() { return pCollider; }

public:
	void CreateAnimator();
	shared_ptr<Animator> GetAnimator() { return pAnimator; }
public:
	void CreateRigidBody();
	shared_ptr<RigidBody> GetRigidBody() { return pRigidBody; }
public:
	virtual void Update()=0;
	virtual void FinalUpdate() final;
	virtual void Render(HDC hdc);
	void ComponentRender(HDC hdc);
	virtual void Init(); //복사생성자 사용시 Init() 호출
	virtual shared_ptr<CObject> Clone()=0;
public:
	virtual void OnCollision(shared_ptr<Collider> pOther) {}
	virtual void EnterCollsion(shared_ptr<Collider> pOther) {}
	virtual void ExitCollision(shared_ptr<Collider> pOther) {}
public:
	CObject();
	CObject(const shared_ptr<CObject> origin);
	virtual ~CObject();
};

