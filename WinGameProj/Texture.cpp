#include "pch.h"
#include "Texture.h"
#include "Core.h"


void Texture::Load(const wstring& strFilePath)
{
 
	mHbitMap=(HBITMAP)LoadImage(NULL, strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE|LR_DEFAULTSIZE);

	if (mHbitMap == NULL)
	{
		DWORD lastError = GetLastError();
		return;
	}
	assert(mHbitMap);
	mhdc =CreateCompatibleDC(Core::GetInst()->GetMainDC()); 
	//BITMAP DC CONNECT
	HBITMAP hPrevBit = (HBITMAP)SelectObject(mhdc, mHbitMap); 
	DeleteObject(hPrevBit); 
	//가로세로 길이
	BITMAP tInfo = {};
	GetObject(mHbitMap, sizeof(BITMAP), &tInfo); 
	mBitMapInfo.bmWidth = tInfo.bmWidth; 
	mBitMapInfo.bmHeight = tInfo.bmHeight; 

	

}

Texture::Texture():mHbitMap(0),mhdc(0),mBitMapInfo{}
{

}

Texture::~Texture() 
{
	DeleteDC(mhdc);
	DeleteObject(mHbitMap);
}
