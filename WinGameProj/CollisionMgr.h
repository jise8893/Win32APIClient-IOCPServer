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
	//이전 프레임 충돌 정보
	map<ULONGLONG, bool> mMapPrevColInfo;

	UINT mArrCheck[(UINT)GROUP_TYPE::END]; //충돌 체크 매트릭스

public:
	void Init();
	void Update();
	void CheckGroup(GROUP_TYPE gltype, GROUP_TYPE grtype);
	void Reset();
private:
	void ColllisionUpdateGroup(GROUP_TYPE gltype,GROUP_TYPE grtype);
	bool IsCollision(shared_ptr<Collider> pLeftCollider, shared_ptr<Collider> pRightCollider);
};

