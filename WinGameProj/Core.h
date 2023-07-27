#pragma once

class Core 
{
	
	SINGLE(Core) 
private:
	HWND	mHwnd; //윈도우 핸들
	POINT	mResolution; //해상도
	HDC		mHdc; //device context 그리기 컨텍스트
	
	HBITMAP mBitMap;//비트맵 핸들
	HDC mMemDc; 

	//GDI OBJECT
	HBRUSH mArrBrush[(UINT)BRUSH_TYPE::END];
	HPEN mArrPen[(UINT)PEN_TYPE::END];

public:
	int Init(HWND pMhwnd, POINT pMresolution);
	void Progress();
	HWND GetMainHwnd() { return mHwnd; }
	POINT GetResolution() { return mResolution; }
	HDC	GetMainDC() { return mHdc; }
	void CreateBrushPen();
	
	HBRUSH GetBrush(BRUSH_TYPE btype) { return mArrBrush[(UINT)btype]; }
	HPEN GetPen(PEN_TYPE ptype) { return mArrPen[(UINT)ptype]; }
};


