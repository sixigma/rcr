#include "stdafx.h"
#include "map1.h"
#include "player.h"

HRESULT map1::init()
{
	setRoomIdx(1);
	if (getPrevRoomIdx() == 2) pl->getPos().x = 3025;
	gameScene::setViewport(pl->getPos().x, pl->getPos().y);
	return S_OK;
}

void map1::release()
{
}

void map1::update()
{
	pl->update();

	if (pl->getPos().x > 3026)
		gameScene::goToRoom(2);


	gameScene::updateViewport(pl->getPos().x, pl->getPos().y);
}

void map1::render()
{
	IMG->find("ÀüÅõ ¸Ê 1")->render(getMemDC(), _currOrg.x, 96, _currOrg.x, 0, WINW, 640);
}
