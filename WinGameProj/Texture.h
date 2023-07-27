#pragma once
#include "Resc.h"
class ResMgr; 
class Texture : public Resc 
{
private:
	HDC mhdc;
	HBITMAP mHbitMap;
	BITMAP mBitMapInfo;
public:
	void Load(const wstring& strFilePath);
	UINT GetWidth() { return mBitMapInfo.bmWidth; }
	UINT GetHeight() {return mBitMapInfo.bmHeight; }
	HDC GetDC() { return mhdc; }
 
public:
	Texture();
	~Texture();
};

