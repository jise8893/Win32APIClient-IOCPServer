#pragma once
class CObject;
class Camera
{
	SINGLE(Camera)
private:
	Vec2 mLookAt; //카메라가 보는 위치
	Vec2 mPrevLookAt; //이전 카메라 프레임 위치
	shared_ptr<CObject> pTObj; //카메라의 오브젝트 
	Vec2 mDiff;//상대거리 카메라 lookat
public:
	void SetLookAt(Vec2 vLook) { mLookAt = vLook; }
	void SetTarget(shared_ptr<CObject> target) { pTObj = target; }
	Vec2 GetRenderPos(Vec2 vObjPos) { return vObjPos-mDiff; }
	Vec2 GetRealPos(Vec2 vRenderPos) { return vRenderPos + mDiff; }
public:
	void Update();
	void CalDiff();
};

