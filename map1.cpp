#include "stdafx.h"
#include "map1.h"
#include "player.h"

HRESULT map1::init()
{
	if (SND->isPlaying("3 - Title Screen.mp3"))
	{
		SND->stop("3 - Title Screen.mp3");
	}
	if (!SND->isPlaying("4 - Running Around.mp3"))
	{
		SND->play("4 - Running Around.mp3", _currMasterVolume * _currBGMVolume);
		SND->findChannel("4 - Running Around.mp3")->setLoopPoints(0, FMOD_TIMEUNIT_MS, 101084, FMOD_TIMEUNIT_MS);
		SND->findChannel("4 - Running Around.mp3")->setPosition(0, FMOD_TIMEUNIT_MS);
		SND->findChannel("4 - Running Around.mp3")->setLoopCount(-1);
	}

	setMapNum(1);
	currPlPos = &pl->getPos();
	if (getPrevMapNum() == 0) *currPlPos = { 154, 568, 0 };
	else if (getPrevMapNum() == 2) *currPlPos = { _totRegion.right - 48, 568, 0 };
	else *currPlPos = { 154, 568, 0 };

	obst.push_back({ 0, 300, 92, 480 });
	obst.push_back({ 92, 292, 160, 484 });
	obst.push_back({ 352, 296, 416, 484 });
	obst.push_back({ 416, 292, 484, 484 });
	obst.push_back({ 484, 300, 3036, 480 });
	unlandable = { 160, 0, 352, 480 };

	prevPlPos = *currPlPos;
	gameScene::setViewport(currPlPos->x, currPlPos->y);

	L->AllDeleteLine();
	L->trgLine(MAP1, "Map Name");

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
		if (currPlPos->x + 32 >= obst[i].left && currPlPos->x - 32 <= obst[i].right		//pos.x +-32 내부에 obst가 있을 시(들어가 있을 시)
			&&currPlPos->y >= obst[i].bottom + 4 && currPlPos->y <= obst[i].bottom + 8	//pos.y -4~8 내부에 obst가 들어갈 시
			&& currPlPos->y + currPlPos->z >= obst[i].top - 1 && currPlPos->y + currPlPos->z <= obst[i].top + 9	//pos.y+pos.z
			&& pl->getJump() && pl->jumpDown() )

		{
			currPlPos->z = (obst[i].top - 1) - currPlPos->y;
			pl->setPlState(IDLE);
			pl->setJump(false);
			pl->setPlWD(false);
		}

		else if (currPlPos->y - 4 < obst[i].bottom && prevPlPos.y - 4 >= obst[i].bottom &&
			currPlPos->x + 32 > obst[i].left && currPlPos->x - 32 < obst[i].right) 
		{
			currPlPos->y = obst[i].bottom + 4;
		}

		if (currPlPos->x <= 92 && currPlPos->x - 32 >= 55 && currPlPos->z != 0 && pl->getJump() == false)//right->left
		{
			pl->setPlWD(true);
			currPlPos->y = obst[i].bottom + 4;
		}
		else if (currPlPos->x >= unlandable.left && currPlPos->x + 32 < unlandable.right && currPlPos->z != 0 && pl->getJump() == false)//left->right
		{
			pl->setPlWD(true);
			currPlPos->y = unlandable.bottom + 4;

		}
		else if (currPlPos->x <= unlandable.right && currPlPos->x - 32 > unlandable.left && currPlPos->z != 0 && pl->getJump() == false)//right->left
		{
			pl->setPlWD(true);
			currPlPos->y = unlandable.bottom + 4;
		}
		else if (currPlPos->x <= 416 && currPlPos->x - 32 >= 375 && currPlPos->z != 0 && pl->getJump() == false)//right->left
		{
			pl->setPlWD(true);
			currPlPos->y = obst[i].bottom + 4;
		}
		else if (currPlPos->x >= 480 && currPlPos->x + 32 < 520 && currPlPos->z != 0 && pl->getJump() == false)//left->right
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

void map1::render()
{
	IMG->find("맵 1")->render(getMemDC(), _currOrg.x, 96, _currOrg.x, 0, WINW, 640);

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
