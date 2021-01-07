#include "stdafx.h"
#include "map1.h"
#include "player.h"

HRESULT map1::init()
{
	setMapNum(1);
	currPlPos = &pl->getPos();
	if (getPrevMapNum() == 0) *currPlPos = { 154, 568 };
	else if (getPrevMapNum() == 2) *currPlPos = { _totRegion.right - 48, 568 };
	else *currPlPos = { 154, 568 };

	obst.push_back({ 0, 300, 92, 480 });
	obst.push_back({ 92, 292, 160, 484 });
	obst.push_back({ 352, 296, 416, 484 });
	obst.push_back({ 416, 292, 484, 484 });
	obst.push_back({ 484, 300, 3036, 480 });
	unlandable = { 160, 0, 352, 480 };

	prevPlPos = *currPlPos;
	gameScene::setViewport(currPlPos->x, currPlPos->y);

	return S_OK;
}

void map1::release()
{
	obst.clear();
}

void map1::update()
{
	if (currPlPos->x + 32 > 3026) gameScene::goToMap(2);

	if (currPlPos->x < 32) currPlPos->x = 32;

	if (currPlPos->y - 4 < unlandable.bottom && prevPlPos.y - 4 >= unlandable.bottom &&
	currPlPos->x + 32 >= unlandable.left && currPlPos->x - 32 <= unlandable.right)
		currPlPos->y = unlandable.bottom + 4;

	for (size_t i = 0; i < obst.size(); ++i)
	{
		if (currPlPos->y < obst[i].top - 1 && prevPlPos.y > obst[i].top - 1 &&
			currPlPos->x + 32 >= obst[i].left && currPlPos->x - 32 <= obst[i].right)
			currPlPos->y = obst[i].top - 1;
		else if (currPlPos->y - 4 < obst[i].bottom && prevPlPos.y - 4 >= obst[i].bottom &&
			currPlPos->x + 32 > obst[i].left && currPlPos->x - 32 < obst[i].right)
			currPlPos->y = obst[i].bottom + 4;
		if (currPlPos->x - 32 > obst[i].left && currPlPos->x - 32 < obst[i].right
			&& currPlPos->y - 4 < obst[i].bottom && prevPlPos.x != currPlPos->x)
			currPlPos->x = obst[i].right + 32;
		else if (currPlPos->x + 32 > obst[i].left && currPlPos->x + 32 < obst[i].right
				 && currPlPos->y - 4 < obst[i].bottom && prevPlPos.x != currPlPos->x)
			currPlPos->x = obst[i].left - 32;
	}

	if (currPlPos->y > 96 + 640) currPlPos->y = 96 + 640;

	gameScene::updateViewport(currPlPos->x, currPlPos->y);
	prevPlPos = *currPlPos;
}

void map1::render()
{
	IMG->find("¸Ê 1")->render(getMemDC(), _currOrg.x, 96, _currOrg.x, 0, WINW, 640);

#ifdef _DEBUG
	{
		if (KEY->isToggledOn(VK_CAPITAL))
		{
			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
			HPEN hOPen = (HPEN)SelectObject(getMemDC(), hPen);
			HBRUSH hOBrush = (HBRUSH)SelectObject(getMemDC(), hBrush);
			for (size_t i = 0; i < obst.size(); ++i)
			{
				DrawRct(getMemDC(), obst[i]);
			}
			DeleteObject(SelectObject(getMemDC(), hOPen));
			DeleteObject(SelectObject(getMemDC(), hOBrush));
			hPen = CreatePen(PS_SOLID, 1, RGB(200, 50, 0));
			hBrush = CreateSolidBrush(RGB(200, 50, 0));
			hOPen = (HPEN)SelectObject(getMemDC(), hPen);
			hOBrush = (HBRUSH)SelectObject(getMemDC(), hBrush);
			DrawRct(getMemDC(), unlandable);
			DeleteObject(SelectObject(getMemDC(), hOPen));
			DeleteObject(SelectObject(getMemDC(), hOBrush));
		}
	}
#endif
}
