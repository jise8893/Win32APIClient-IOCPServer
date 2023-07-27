#pragma once
class CObject;
class Camera
{
	SINGLE(Camera)
private:
	Vec2 mLookAt; //ī�޶� ���� ��ġ
	Vec2 mPrevLookAt; //���� ī�޶� ������ ��ġ
	shared_ptr<CObject> pTObj; //ī�޶��� ������Ʈ 
	Vec2 mDiff;//���Ÿ� ī�޶� lookat
public:
	void SetLookAt(Vec2 vLook) { mLookAt = vLook; }
	void SetTarget(shared_ptr<CObject> target) { pTObj = target; }
	Vec2 GetRenderPos(Vec2 vObjPos) { return vObjPos-mDiff; }
	Vec2 GetRealPos(Vec2 vRenderPos) { return vRenderPos + mDiff; }
public:
	void Update();
	void CalDiff();
};

