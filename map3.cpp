#include "stdafx.h"
#include "map3.h"
#include "player.h"

HRESULT map3::init()
{
	if (SND->isPlaying("5 - Menu.mp3"))
	{
		SND->stop("5 - Menu.mp3");
	}
	if (!SND->isPlaying("4 - Running Around.mp3"))
	{
		SND->play("4 - Running Around.mp3", _currMasterVolume * _currBGMVolume);
		SND->findChannel("4 - Running Around.mp3")->setLoopPoints(0, FMOD_TIMEUNIT_MS, 101084, FMOD_TIMEUNIT_MS);
		SND->findChannel("4 - Running Around.mp3")->setPosition(0, FMOD_TIMEUNIT_MS);
		SND->findChannel("4 - Running Around.mp3")->setLoopCount(-1);
	}
	setMapNum(3);
	currPlPos = &pl->getPos();
	
	if (getPrevMapNum() == 4) *currPlPos = { _totRegion.right - 40, 592, 0 };
	else if (getShopNum() == 1) *currPlPos = { 338, 484 + 8 };
	else if (getShopNum() == 2) *currPlPos = { 734, 484 + 8 };
	else if (getShopNum() == 3) *currPlPos = { 1144, 484 + 8 };
	else if (getShopNum() == 4) *currPlPos = { 1824, 484 + 8 };
	else *currPlPos = { _totRegion.left + 40, 592, 0 };

	obst.push_back({ 0, 96, 416, 480 });
	obst.push_back({ 416, 96, 480, 484 });
	obst.push_back({ 480, 96, 1950, 480 });
	obst.push_back({ 1950, 96, _totRegion.right, 484 });

	prevPlPos = *currPlPos;
	gameScene::setViewport(pl->getPos().x, pl->getPos().y);

	L->AllDeleteLine();
	L->trgLine(MAP3, "Map Name");

	return S_OK;
}

void map3::release()
{
	obst.clear();
}

void map3::update()
{
	if (currPlPos->x < 32) gameScene::goToMap(2);
	else if (currPlPos->x + 32 > _totRegion.right) gameScene::goToMap(4);
	else if (currPlPos->y <= 484 && KEY->press('W'))
	{
		if (currPlPos->x - 32 >= 288 && currPlPos->x + 32 <= 388)
		{
			gameScene::setShopNum(1); //1번 상점으로
			gameScene::goToMap(6); 
		}
		else if (currPlPos->x - 32 >= 644 && currPlPos->x + 32 <= 824)
		{
			gameScene::setShopNum(2); //2번 상점으로
			gameScene::goToMap(6);
		}
		else if (currPlPos->x - 32 >= 1068 && currPlPos->x + 32 <= 1220)
		{
			gameScene::setShopNum(3); //2번 상점으로
			gameScene::goToMap(6);
		}
		else if (currPlPos->x - 32 >= 1732 && currPlPos->x + 32 <= 1916)
		{
			gameScene::setShopNum(4); //2번 상점으로
			gameScene::goToMap(6);
		}
	}

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

void map3::render()
{
	IMG->find("맵 3")->render(getMemDC(), _currOrg.x, 96, _currOrg.x, 0, WINW, 640);

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
