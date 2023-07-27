#pragma once
class CObject;
class Collider
{
	static atomic<UINT> sID;
	weak_ptr<CObject> pOwner;//오브젝트 포인터
	Vec2 mOffsetPos;//충돌체 오프셋
	Vec2 mFinalPos;//충돌체 위치

	Vec2 mScale; //충돌체 크기
	UINT mid;
	UINT mCol;
public:
	void SetOffsetPos(Vec2 pos) { mOffsetPos = pos; }
	void SetScale(Vec2 vScale) { mScale = vScale; }
	void SetOwner(shared_ptr<CObject> pObj) { pOwner = pObj; }

	void FinalUpdate();
public:
	void Render(HDC hdc);
	UINT GetID() { return mid; }
	Vec2 GetFinalPos() { return mFinalPos; }
	Vec2 GetScale() { return mScale; }
	shared_ptr<CObject> GetObj() { return pOwner.lock(); }
	Collider& operator = (Collider& origin) = delete; //복사생성자 삭제
public:
	void OnCollision(shared_ptr<Collider> pOther);
	void EnterCollision(shared_ptr<Collider> pOther);
	void ExitCollision(shared_ptr<Collider> pOther);
public:
	Collider() = delete; // default constructure 삭제
	Collider(const shared_ptr<CObject> obj);
	Collider(const shared_ptr<Collider> origin);
	~Collider();
};