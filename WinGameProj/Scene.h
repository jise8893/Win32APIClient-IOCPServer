#pragma once

class CObject;//�����Ϸ� ���� ���� ���� ���漱��

class Scene
{
private:
	std::vector<std::shared_ptr<CObject>>	mVecObjGroup[(int)GROUP_TYPE::END];
	wstring									mStrName;
	mutex									mMutex;
public:
	void SetName(const wstring& strName) { mStrName = strName; }
	const wstring& GetName() { return mStrName; }

	virtual void Enter()=0; //Scene ����
	virtual void Exit() = 0;//Scene Ż��
	void Render(HDC hdc);
	virtual void Update();
	void FinalUpdate();
	const std::vector<shared_ptr<CObject>>& GetGroupObject(GROUP_TYPE gtype);
public:
	mutex& GetMutex() { return mMutex; }
public:
	void AddObject(shared_ptr<CObject> pObj, GROUP_TYPE gtype);
	void DeleteGroup(GROUP_TYPE gType);
	void DeleteAll();
public:
	Scene();
	virtual ~Scene();
};

