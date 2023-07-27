#include "pch.h"
#include "Core.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "CollisionMgr.h"
#include "EventMgr.h"
int Core::Init(HWND pMhwnd, POINT pMresolution)
{
	
	mHwnd = pMhwnd;
	mResolution = pMresolution;

	RECT rt = {0,0,pMresolution.x,pMresolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(pMhwnd, NULL, 0, 0, rt.right - rt.left, rt.bottom - rt.top, SWP_NOZORDER);
	


	

	mHdc = GetDC(mHwnd);

	//Double buffering
	mBitMap = CreateCompatibleBitmap(mHdc, pMresolution.x, pMresolution.y); 
	mMemDc = CreateCompatibleDC(mHdc); 
	HBITMAP hOldBit = (HBITMAP)SelectObject(mMemDc, mBitMap); 
	DeleteObject(hOldBit);


	//Create Brush
	CreateBrushPen();
	//initialize manager
	TimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init(); 
	PathMgr::GetInst()->Init(); 
	SceneMgr::GetInst()->Init();
	CollisionMgr::GetInst()->Init();


	return S_OK;
}

void Core::Progress() 
{
	TimeMgr::GetInst()->Update();   
	CKeyMgr::GetInst()->Update();  
	Camera::GetInst()->Update(); 
	SceneMgr::GetInst()->Update();  
	CollisionMgr::GetInst()->Update(); 

	//--------------
	// Rendering
	// -------------
	// 화면 Clear
	Rectangle(mMemDc, -1, -1, mResolution.x + 1, mResolution.y + 1); 

	SceneMgr::GetInst()->Render(mMemDc); 
	BitBlt(mHdc, 0, 0, mResolution.x, mResolution.y, mMemDc, 0, 0, SRCCOPY);  
	TimeMgr::GetInst()->Render();   
	//이벤트 지연 처리
	EventMgr::GetInst()->Update(); 
}

void Core::CreateBrushPen()
{
	mArrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	mArrPen[(UINT)PEN_TYPE::RED] = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); 
	mArrPen[(UINT)PEN_TYPE::GREEN] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	mArrPen[(UINT)PEN_TYPE::BLUE] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}



Core::Core() : mHwnd(0),mResolution{}, mHdc(0),mBitMap(0),mMemDc(0)
{

}

Core::~Core()
{
	ReleaseDC(mHwnd,mHdc);
	DeleteDC(mMemDc);
	DeleteObject(mBitMap);
	
	for (int i = 0; i < (int)PEN_TYPE::END; i++)
	{
		DeleteObject(mArrPen[i]);
	}
}
