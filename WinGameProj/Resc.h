#pragma once
class Resc
{
private:
	wstring mStrKey;//���ҽ� Ű
	wstring mStrRelativePath;//���ҽ� �����
public:
	void SetKey(const wstring& strKey) { mStrKey = strKey; }
	void SetRelativePath(const wstring& strPath) { mStrRelativePath = strPath; }

	const wstring& GetKey() { return mStrKey; }
	const wstring& GetRelativePath() { return mStrRelativePath; }
public:
	Resc();
	virtual ~Resc();
};

