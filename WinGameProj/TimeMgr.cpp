#include "pch.h"
#include "TimeMgr.h"
#include "Core.h"
void TimeMgr::Init()
{
	QueryPerformanceCounter(&mlIPrevCount);
	QueryPerformanceFrequency(&mlIFrequency);//1초당 카운트 발생횟수 

}
void TimeMgr::Update()
{
	QueryPerformanceCounter(&mlICurCount); 

	mDeltaTime = double((double)mlICurCount.QuadPart - (double)mlIPrevCount.QuadPart) / (double) mlIFrequency.QuadPart;
	mlIPrevCount = mlICurCount;

	
}
void TimeMgr::Render()
{
	mCount++; 
	mDeltaAcc += mDeltaTime; 

	if (mDeltaAcc > 1.0) 
	{

		mDeltaAcc = 0;
		mFps = mCount; 
		mCount = 0; 

		wchar_t szBuffer[255] = {}; 
		swprintf_s(szBuffer, L"FPS: %d , DT : %f", mFps, mDeltaTime); 
		SetWindowText(Core::GetInst()->GetMainHwnd(), szBuffer); 
	}
}
TimeMgr::TimeMgr() :mlICurCount{}, mlIFrequency{}, mlIPrevCount{},mDeltaTime(0),mCount(0),mDeltaAcc(0),mFps(0)
{

}
TimeMgr::~TimeMgr()
{

}