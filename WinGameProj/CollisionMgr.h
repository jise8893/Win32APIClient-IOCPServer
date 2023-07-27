#pragma once
class Collider;
union COLLIDER_ID{
	struct {
		UINT iLeft;
		UINT iRight;
	};
	ULONGLONG ID;
};
class CollisionMgr
{
	SINGLE(CollisionMgr)
private:
	//���� ������ �浹 ����
	map<ULONGLONG, bool> mMapPrevColInfo;

	UINT mArrCheck[(UINT)GROUP_TYPE::END]; //�浹 üũ ��Ʈ����

public:
	void Init();
	void Update();
	void CheckGroup(GROUP_TYPE gltype, GROUP_TYPE grtype);
	void Reset();
private:
	void ColllisionUpdateGroup(GROUP_TYPE gltype,GROUP_TYPE grtype);
	bool IsCollision(shared_ptr<Collider> pLeftCollider, shared_ptr<Collider> pRightCollider);
};

