#pragma once

class Scene;

class SceneMgr
{
	SINGLE(SceneMgr)
private:
	vector<shared_ptr<Scene>> mVecScene;
	shared_ptr<Scene> mCurScene;
public:
	void Init();
	void Update();
	void Render(HDC hdc);
public:
	shared_ptr<Scene> GetCurScene() { return mCurScene; }
private:
	void ChangeScene(SCENE_TYPE sType);
	friend class EventMgr;
};

