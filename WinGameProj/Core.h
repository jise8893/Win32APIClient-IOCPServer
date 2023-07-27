#pragma once

class Core 
{
	
	SINGLE(Core) 
private:
	HWND	mHwnd; //������ �ڵ�
	POINT	mResolution; //�ػ�
	HDC		mHdc; //device context �׸��� ���ؽ�Ʈ
	
	HBITMAP mBitMap;//��Ʈ�� �ڵ�
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


