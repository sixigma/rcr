#include "stdafx.h"
#include "map2.h"
#include "player.h"

HRESULT map2::init()
{
	setMapNum(2);
	currPlPos = &pl->getPos();
	if (getPrevMapNum() == 1) *currPlPos = { _totRegion.left + 48, 568, 0 };
	else if (getPrevMapNum() == 3) *currPlPos = { 1792, 516, 0 };

	obst.push_back({ 0, 96, 32, 480 });
	obst.push_back({ 32, 352, 1632, 476 });
	obst.push_back({ 1632, 96, 1696, 480 });
	obst.push_back({ 1888, 352, _totRegion.right, 476 });

	prevPlPos = *currPlPos;
	gameScene::setViewport(pl->getPos().x, pl->getPos().y);

	L->AllDeleteLine();
	L->trgLine(MAP2, "Map Name");

	return S_OK;
}

void map2::release()
{
	obst.clear();
}

void map2::update()
{
	if (currPlPos->x < 32) gameScene::goToMap(1);
	else if (currPlPos->y < 428 && currPlPos->x >= 1696 + 32 && currPlPos->x + 32 <= 1888)
		gameScene::goToMap(3);

	if (currPlPos->x + 32 > _totRegion.right) currPlPos->x = _totRegion.right - 32;

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

	gameScene::updateViewport(currPlPos->x, currPlPos->y);
	prevPlPos = *currPlPos;
}

void map2::render()
{
	IMG->find("¸Ê 2")->render(getMemDC(), _currOrg.x, 96, _currOrg.x, 0, WINW, 640);

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
		}
	}
#endif
}
