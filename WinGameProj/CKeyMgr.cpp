#include "pch.h"
#include "CKeyMgr.h"
#include "Core.h"
int KeyArr[(int)KEY::LAST] =
{
	VK_LEFT, 
	VK_RIGHT, 
	VK_UP, 
	VK_DOWN, 
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',
	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,
	VK_LBUTTON,
	VK_RBUTTON,
};
void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		mVecKey.push_back(tKeyInfo{ KEYSTATE::NONE,KEYSTATE::NONE,false });
	}
}     
void CKeyMgr::Update()
{
	HWND hWnd = GetFocus();
	
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			if (GetAsyncKeyState(KeyArr[i]) & 0x8000)
			{
				if (mVecKey[i].bPrev)
				{  
					mVecKey[i].eState = KEYSTATE::HOLD;
				}
				else
				{
					mVecKey[i].eState = KEYSTATE::TAP;
				}
				mVecKey[i].bPrev = true;
			}
			else
			{
				if (mVecKey[i].bPrev)
				{
					mVecKey[i].eState = KEYSTATE::AWAY;
				}
				else
				{
					mVecKey[i].eState = KEYSTATE::NONE;
				}
				mVecKey[i].bPrev = false;
			}
		}
		//마우스 위치 계산
		POINT ptPos = {};
		GetCursorPos(&ptPos);
		ScreenToClient(Core::GetInst()->GetMainHwnd(), &ptPos);
		mCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);
	}
	else //non-focusing
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			mVecKey[i].bPrev = false;
			if (KEYSTATE::TAP == mVecKey[i].eState || KEYSTATE::HOLD == mVecKey[i].eState)
			{
				mVecKey[i].eState = KEYSTATE::AWAY;
			}
			else if (KEYSTATE::AWAY == mVecKey[i].eState)
			{
				mVecKey[i].eState = KEYSTATE::NONE;
			}
		}

	}
	

}
KEYSTATE CKeyMgr::GetKeyState(KEY key)
{
	return mVecKey[(int)key].eState;
	
}
KEYSTATE CKeyMgr::GetPrevKeyState(KEY key)
{
	return mVecKey[(int)key].ePrevState;
}
Vec2 CKeyMgr::GetMousePos()
{
	return mCurMousePos;
}
CKeyMgr::CKeyMgr()
{

}
CKeyMgr::~CKeyMgr() {

}
