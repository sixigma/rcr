#pragma once

constexpr float PI = 3.1415927f; // pi
constexpr float PI2 = 6.283185f; // 2 pi

namespace utils
{
	float Distance(float x1, float y1, float x2, float y2);
	float Angle(float x1, float y1, float x2, float y2);
}

inline void DrawLine(HDC hDC, int x1, int y1, int x2, int y2)
{
	MoveToEx(hDC, x1 - _currOrg.x, y1 - _currOrg.y, nullptr);
	LineTo(hDC, x2 - _currOrg.x, y2 - _currOrg.y);
}

inline POINT MakePt(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

inline RECT MakeRct(int x, int y, int width, int height)
{
	RECT rct = { x, y, x + width, y + height };

	return rct;
}

inline RECT MakeRctC(int x, int y, int width, int height)
{
	RECT rct = { x - (width / 2) , y - (height / 2), x + (width / 2), y + (height / 2) };
	return rct;
}

inline void DrawRct(HDC hDC, int x, int y, int width, int height)
{
	Rectangle(hDC, x - _currOrg.x, y - _currOrg.y, x + width - _currOrg.x, y + height - _currOrg.y);
}

inline void DrawRctC(HDC hDC, int x, int y, int width, int height)
{
	Rectangle(hDC, x - (width / 2) - _currOrg.x, y - (height / 2) - _currOrg.y, x + (width / 2) - _currOrg.x, y + (height / 2) - _currOrg.y);
}

inline void DrawRct(HDC hDC, RECT& rct)
{
	Rectangle(hDC, rct.left - _currOrg.x, rct.top - _currOrg.y, rct.right - _currOrg.x, rct.bottom - _currOrg.y);
}

inline void DrawElp(HDC hDC, int x, int y, int width, int height)
{
	Ellipse(hDC, x - _currOrg.x, y - _currOrg.y, x + width - _currOrg.x, y + height - _currOrg.y);
}

inline void DrawElpC(HDC hDC, int x, int y, int width, int height)
{
	Ellipse(hDC, x - (width / 2) - _currOrg.x, y - (height / 2) - _currOrg.y, x + (width / 2) - _currOrg.x, y + (height / 2) - _currOrg.y);
}

inline void DrawElp(HDC hDC, RECT& rct)
{
	Ellipse(hDC, rct.left - _currOrg.x, rct.top - _currOrg.y, rct.right - _currOrg.x, rct.bottom - _currOrg.y);
}