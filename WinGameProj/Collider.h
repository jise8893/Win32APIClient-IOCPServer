#pragma once
class CObject;
class Collider
{
	static atomic<UINT> sID;
	weak_ptr<CObject> pOwner;//������Ʈ ������
	Vec2 mOffsetPos;//�浹ü ������
	Vec2 mFinalPos;//�浹ü ��ġ

	Vec2 mScale; //�浹ü ũ��
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
	Collider& operator = (Collider& origin) = delete; //��������� ����
public:
	void OnCollision(shared_ptr<Collider> pOther);
	void EnterCollision(shared_ptr<Collider> pOther);
	void ExitCollision(shared_ptr<Collider> pOther);
public:
	Collider() = delete; // default constructure ����
	Collider(const shared_ptr<CObject> obj);
	Collider(const shared_ptr<Collider> origin);
	~Collider();
};