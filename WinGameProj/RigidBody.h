#pragma once
class CObject;
class RigidBody
{
private:
	weak_ptr<CObject> pOwner;
	Vec2 mForce;//크기 ,방향
	Vec2 mAccel; //가속도
	Vec2 mVelocity; //속도
	float mFmass;//질량
	
public:
	RigidBody()=delete;
	RigidBody(const shared_ptr<CObject> pObj) { pOwner = pObj; };
	~RigidBody();
	friend class COjbect;
	virtual void FinalUpdate();
	void SetOwner(shared_ptr<CObject> pObj) { pOwner = pObj; }
};

