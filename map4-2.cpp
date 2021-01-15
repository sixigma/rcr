#include "stdafx.h"
#include "map4-2.h"
#include "player.h"

HRESULT map4_2::init()
{
	if (SND->isPlaying("4 - Running Around.mp3"))
	{
		SND->stop("4 - Running Around.mp3");
	}
	if (!SND->isPlaying("6 - Password.mp3"))
	{
		SND->play("6 - Password.mp3", _currMasterVolume * _currBGMVolume);
		SND->findChannel("6 - Password.mp3")->setLoopPoints(34748, FMOD_TIMEUNIT_MS, 69489, FMOD_TIMEUNIT_MS);
		SND->findChannel("6 - Password.mp3")->setPosition(34748, FMOD_TIMEUNIT_MS);
		SND->findChannel("6 - Password.mp3")->setLoopCount(-1);
	}
	setMapNum(402);
	currPlPos = &pl->getPos();
	if (getPrevMapNum() == 4) *currPlPos = { _totRegion.left + 40, 592, 0 };

	unlandable.push_back({ 0, 96, 96, 336 });
	obst.push_back({ 96, 288, 288, 384 });
	unlandable.push_back({ 288, 96, 352, 336 });
	obst.push_back({ 352, 164, 1440, 352 });
	obst.push_back({ 864, 352, 1184, 416 });
	obst.push_back({ 928, 416, 1120, 480 });
	unlandable.push_back({ 1440, 96, 1504, 336 });
	obst.push_back({ 1504, 288, 1760, 384 });
	unlandable.push_back({ 1760, 96, _totRegion.right, 336 });

	prevPlPos = *currPlPos;
	gameScene::setViewport(pl->getPos().x, pl->getPos().y);

	L->AllDeleteLine();
	L->trgLine(MAP4_2, "Map Name");

	return S_OK;
}

void map4_2::release()
{
	obst.clear();
	unlandable.clear();
}

void map4_2::update()
{
	if (currPlPos->x < 32) gameScene::goToMap(4);
	for (size_t i = 0; i < unlandable.size(); ++i)
	{
		if (currPlPos->y - 4 < unlandable[i].bottom && prevPlPos.y - 4 >= unlandable[i].bottom &&
		currPlPos->x + 32 >= unlandable[i].left && currPlPos->x - 32 <= unlandable[i].right)
			currPlPos->y = unlandable[i].bottom + 4;
	}

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

	if (currPlPos->x + 32 > 1860) currPlPos->x = 1860 - 32;

	gameScene::updateViewport(currPlPos->x, currPlPos->y);
	prevPlPos = *currPlPos;
}

void map4_2::render()
{
	IMG->find("¸Ê 4-2")->render(getMemDC(), _currOrg.x, 96, _currOrg.x, 0, WINW, 640);

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
			for (size_t i = 0; i < unlandable.size(); ++i)
			{
				DrawRct(getMemDC(), unlandable[i]);
			}
			DeleteObject(SelectObject(getMemDC(), hOPen));
			DeleteObject(SelectObject(getMemDC(), hOBrush));
		}
	}
#endif
}
