#pragma once
class PathMgr
{
	SINGLE(PathMgr)
private:
	wchar_t mSzContentPath[255];

public:
	void Init();
	const wchar_t* GetContentPath() { return mSzContentPath; }
};

