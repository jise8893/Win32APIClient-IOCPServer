#pragma once
class Animator;
class Texture;

struct tAnimFrm
{
	Vec2 vLeftTop;
	Vec2 vInterval;
	Vec2 vSlice;
	Vec2 vOffset;
	float fDuration;
};


class Animation
{
private:
	wstring mStrName;
	weak_ptr<Animator> pAnimator;
	shared_ptr<Texture> pATex; //texture pointer
	vector<tAnimFrm> mVecFrm; //모든 프레임 정보
	int mCurFrm; //현재 프레임 넘버
	float mfAccTime; //누적 시간 

	bool mFinished;
public:
	void Update();
	void Render(HDC hdc);
	bool IsFinished() { return mFinished; }
	void SetRepeat() { mFinished = false; mCurFrm = 0; mfAccTime = 0.f; }
public:
	void SetName(const wstring& strName) { mStrName = strName; }
	const wstring& GetName() { return mStrName; }
	void Create(shared_ptr<Texture> pTex, Vec2 vLpos, Vec2 sliceSize, Vec2 vInterval, UINT frameSize,float fDuraion);
	UINT GetMaxFrame() { return mVecFrm.size(); }
	tAnimFrm& GetFrame(int idx)
	{
		return mVecFrm[idx];
	}
public:
	Animation()=delete;
	Animation(const shared_ptr<Animator> pAnim);
	~Animation();
};

