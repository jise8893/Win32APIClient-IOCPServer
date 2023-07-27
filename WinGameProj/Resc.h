#pragma once
class Resc
{
private:
	wstring mStrKey;//리소스 키
	wstring mStrRelativePath;//리소스 상대경로
public:
	void SetKey(const wstring& strKey) { mStrKey = strKey; }
	void SetRelativePath(const wstring& strPath) { mStrRelativePath = strPath; }

	const wstring& GetKey() { return mStrKey; }
	const wstring& GetRelativePath() { return mStrRelativePath; }
public:
	Resc();
	virtual ~Resc();
};

