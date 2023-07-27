#include "pch.h"
#include "SelectGdi.h"
#include "Core.h"


SelectGdi::SelectGdi(HDC hdc, PEN_TYPE pType)
{
	mHdc = hdc;
	HPEN hPen = (HPEN)Core::GetInst()->GetPen(pType);
	mDefaultPen = (HPEN)SelectObject(hdc, hPen);
}

SelectGdi::SelectGdi(HDC hdc, BRUSH_TYPE bType) :mHdc(0),mDefaultBrush(nullptr),mDefaultPen(nullptr)
{
	mHdc = hdc;
	HBRUSH hBrush = (HBRUSH)Core::GetInst()->GetBrush(bType); 
	mDefaultBrush = (HBRUSH)SelectObject(hdc, hBrush); 

}

SelectGdi::~SelectGdi()
{
	SelectObject(mHdc, mDefaultBrush); 
	SelectObject(mHdc, mDefaultPen); 

}
