#pragma once
class CObject;
class Animation;
class Texture;
class Animator :public enable_shared_from_this<Animator>
{
private:
	weak_ptr<CObject> pOwner; // object 
	map<wstring, shared_ptr<Animation>> mMapAnim; //anim map
	shared_ptr<Animation> pCurAnim;//현재 재생중인 anim
	bool mRepeat; //반복 재생
public:
	void CreateAnimation(const wstring& strName,shared_ptr<Texture> pTex, Vec2 vLpos, Vec2 sliceSize, Vec2 vInterval, UINT frameSize,float fDuraion);
	shared_ptr<Animation> FindAnimation(const wstring& strName);
	void Play(const wstring& strName,bool repeat);
	void SetOwner(shared_ptr<CObject> pObj) { pOwner = pObj; }
	shared_ptr<CObject> GetObj() { return pOwner.lock(); }
public:
	void Render(HDC hdc);
	void Update();


public:
	Animator();
	~Animator();
	Animator(const shared_ptr<Animator> origin);
	Animator(const shared_ptr<CObject> pObj);
	friend class CObject;
};

