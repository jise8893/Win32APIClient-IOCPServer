#pragma once
class Texture;
class ResMgr
{
	SINGLE(ResMgr)
public:

	shared_ptr<Texture> LoadTexture(const wstring& strKey, const wstring& strRelativePath);

	shared_ptr<Texture> FindTexture(const wstring& strKey);
private:
	map<wstring, shared_ptr<Texture>> mMapRes;
};

