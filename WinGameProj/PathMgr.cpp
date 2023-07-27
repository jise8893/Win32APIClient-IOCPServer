#include "pch.h"
#include "PathMgr.h"
#include "Core.h"
void PathMgr::Init()
{ 
	GetCurrentDirectory(255, mSzContentPath); 
	int iLen = wcslen(mSzContentPath);
	for (int i = iLen - 1; i >= 0; --i)
	{
		if ('\\' == mSzContentPath[i])
		{
			mSzContentPath[i] = '\0';
			break;
		}
	}
	wcscat_s(mSzContentPath, 255, L"\\Release\\Contents\\"); 

	SetWindowText(Core::GetInst()->GetMainHwnd(), mSzContentPath); 
}

PathMgr::PathMgr()
{
}

PathMgr::~PathMgr()
{
}
