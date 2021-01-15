#include "stdafx.h"
#include "map4.h"
#include "player.h"

HRESULT map4::init()
{
	if (SND->isPlaying("6 - Password.mp3"))
	{
		SND->stop("6 - Password.mp3");
	}
	if (!SND->isPlaying("4 - Running Around.mp3"))
	{
		SND->play("4 - Running Around.mp3", _currMasterVolume * _currBGMVolume);
		SND->findChannel("4 - Running Around.mp3")->setLoopPoints(0, FMOD_TIMEUNIT_MS, 101084, FMOD_TIMEUNIT_MS);
		SND->findChannel("4 - Running Around.mp3")->setPosition(0, FMOD_TIMEUNIT_MS);
		SND->findChannel("4 - Running Around.mp3")->setLoopCount(-1);
	}

	setMapNum(4);
	currPlPos = &pl->getPos();
	if (getPrevMapNum() == 3) *currPlPos = { _totRegion.left + 40, 592, 0 };
	else if (getPrevMapNum() == 5) *currPlPos = { _totRegion.right - 40, 592, 0 };
	else if (getPrevMapNum() == 402) *currPlPos = { 1536, 508, 0 };

	obst.push_back({ 0, 416, 464, 484 });
	obst.push_back({ 672, 416, 1376, 484 });
	obst.push_back({ 1376, 356, 1440, 488 });
	obst.push_back({ 1632, 356, 1700, 488 });
	obst.push_back({ 1700, 416, _totRegion.right, 484 });
	unlandable = { 464, 416, 672, 484 };

	prevPlPos = *currPlPos;
	gameScene::setViewport(pl->getPos().x, pl->getPos().y);

	L->AllDeleteLine();
	L->trgLine(MAP4, "Map Name");

	return S_OK;
}

void map4::release()
{
	obst.clear();
}

void map4::update()
{
	if (currPlPos->x < 32) gameScene::goToMap(3);
	else if (currPlPos->x + 32 > _totRegion.right) gameScene::goToMap(5);
	else if (currPlPos->y < 428 && currPlPos->x >= 1440 + 32 && currPlPos->x + 32 <= 1632)
		gameScene::goToMap(402);

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

		if (currPlPos->x >= unlandable.left && currPlPos->x + 32 < unlandable.right && currPlPos->z != 0 && pl->getJump() == false)//left->right
		{
			pl->setPlWD(true);
			currPlPos->y = unlandable.bottom + 4;

		}
		else if (currPlPos->x <= unlandable.right && currPlPos->x - 32 > unlandable.left && currPlPos->z != 0 && pl->getJump() == false)//right->left
		{
			pl->setPlWD(true);
			currPlPos->y = unlandable.bottom + 4;
		}
		if (currPlPos->x >= 1376 && currPlPos->x + 32 < 1420 && currPlPos->z != 0 && pl->getJump() == false)//left->right
		{
			pl->setPlWD(true);
			currPlPos->y = unlandable.bottom + 4;

		}
		else if (currPlPos->x <= 1440 && currPlPos->x - 32 > 1400 && currPlPos->z != 0 && pl->getJump() == false)//right->left
		{
			pl->setPlWD(true);
			currPlPos->y = unlandable.bottom + 4;
		}
		if (currPlPos->x >= 1632 && currPlPos->x + 32 < 1670 && currPlPos->z != 0 && pl->getJump() == false)//left->right
		{
			pl->setPlWD(true);
			currPlPos->y = unlandable.bottom + 4;

		}
		else if (currPlPos->x <= 1700 && currPlPos->x - 32 > 1660 && currPlPos->z != 0 && pl->getJump() == false)//right->left
		{
			pl->setPlWD(true);
			currPlPos->y = unlandable.bottom + 4;
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

void map4::render()
{
	IMG->find("¸Ê 4")->render(getMemDC(), _currOrg.x, 96, _currOrg.x, 0, WINW, 640);

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
