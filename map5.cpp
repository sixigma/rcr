#include "stdafx.h"
#include "map5.h"
#include "player.h"

HRESULT map5::init()
{
	setMapNum(5);
	currPlPos = &pl->getPos();
	if (getPrevMapNum() == 4) *currPlPos = { _totRegion.left + 40, 592, 0 };

	obst.push_back({ 0, 96, 32, 480 });
	obst.push_back({ 32, 352, 1120, 476 });
	obst.push_back({ 1120, 96, 1184, 480 });
	obst.push_back({ 1376, 352, _totRegion.right, 476 });

	unlandable = { 1184, 96, 1376, 428 }; // 다음 구역으로 가는 길을 막는다.

	prevPlPos = *currPlPos;
	gameScene::setViewport(pl->getPos().x, pl->getPos().y);

	L->AllDeleteLine();
	L->trgLine(MAP5, "Map Name");

	return S_OK;
}

void map5::release()
{
	obst.clear();
}

void map5::update()
{
	if (currPlPos->x < 32) gameScene::goToMap(4);

	if (currPlPos->y - 4 < unlandable.bottom && prevPlPos.y - 4 >= unlandable.bottom &&
		currPlPos->x + 32 >= unlandable.left && currPlPos->x - 32 <= unlandable.right)
		currPlPos->y = unlandable.bottom + 4;

	for (size_t i = 0; i < obst.size(); ++i)
	{
		/*if (currPlPos->y < obst[i].top - 1 && prevPlPos.y > obst[i].top - 1 &&
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
			currPlPos->x = obst[i].left - 32;*/
		if (currPlPos->x + 32 >= obst[i].left && currPlPos->x - 32 <= obst[i].right
			&&currPlPos->y >= obst[i].bottom + 4 && currPlPos->y <= obst[i].bottom + 8)

		{
			if (currPlPos->y + currPlPos->z >= obst[i].top - 1 && pl->getJump() && pl->jumpDown() && currPlPos->y + currPlPos->z <= obst[i].top + 2)
			{
				currPlPos->z = (obst[i].top - 1) - currPlPos->y;
				pl->setPlState(IDLE);
				pl->setJump(false);
				pl->setPlWD(false);
			}
		}

		else if (
			currPlPos->y - 4 < obst[i].bottom &&
			prevPlPos.y - 4 >= obst[i].bottom &&
			currPlPos->x + 32 > obst[i].left && currPlPos->x - 32 < obst[i].right)
		{
			currPlPos->y = obst[i].bottom + 4;
		}

		if (currPlPos->x <= 1888 && currPlPos->x - 32 >= 1850 && currPlPos->z != 0 && pl->getJump() == false)//right->left
		{
			pl->setPlWD(true);
			currPlPos->y = obst[i].bottom + 4;
		}

		if (currPlPos->x - 32 > obst[i].left && currPlPos->x - 32 < obst[i].right
			&& currPlPos->y - 4 < obst[i].bottom && prevPlPos.x != currPlPos->x&&currPlPos->y + currPlPos->z >= obst[i].top - 1)
		{
			currPlPos->x = obst[i].right + 32;
		}
		else if (currPlPos->x + 32 > obst[i].left && currPlPos->x + 32 < obst[i].right
			&& currPlPos->y - 4 < obst[i].bottom && prevPlPos.x != currPlPos->x&&currPlPos->y + currPlPos->z >= obst[i].top - 1)
		{
			currPlPos->x = obst[i].left - 32;
		}
	}

	if (currPlPos->y > 96 + 640) currPlPos->y = 96 + 640;

	if (currPlPos->x + 32 > _totRegion.right) currPlPos->x = _totRegion.right - 32;

	if (currPlPos->x > 228 && currPlPos->x < 1500 && currPlPos->y > 552)
	{
		// 낙사 처리


		gameScene::goToMap(3);
	}


	gameScene::updateViewport(currPlPos->x, currPlPos->y);
	prevPlPos = *currPlPos;
}

void map5::render()
{
	IMG->find("맵 5")->render(getMemDC(), _currOrg.x, 96, _currOrg.x, 0, WINW, 640);

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
