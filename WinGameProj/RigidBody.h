#pragma once
class CObject;
class RigidBody
{
private:
	weak_ptr<CObject> pOwner;
	Vec2 mForce;//ũ�� ,����
	Vec2 mAccel; //���ӵ�
	Vec2 mVelocity; //�ӵ�
	float mFmass;//����
	
public:
	RigidBody()=delete;
	RigidBody(const shared_ptr<CObject> pObj) { pOwner = pObj; };
	~RigidBody();
	friend class COjbect;
	virtual void FinalUpdate();
	void SetOwner(shared_ptr<CObject> pObj) { pOwner = pObj; }
};

