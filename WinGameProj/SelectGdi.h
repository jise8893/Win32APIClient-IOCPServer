#pragma once
class SelectGdi
{
private:
	HDC mHdc;
	HPEN mDefaultPen;
	HBRUSH mDefaultBrush;

public:

	SelectGdi()=delete;
	SelectGdi(HDC hdc, PEN_TYPE pType);
	SelectGdi(HDC hdc, BRUSH_TYPE bType);
	~SelectGdi();
};

