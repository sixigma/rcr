#include "stdafx.h"
#include "map2.h"
#include "player.h"

HRESULT map2::init()
{
	setRoomIdx(2);
	pl->getPos().x = 10;
	gameScene::setViewport(pl->getPos().x, pl->getPos().y);
	return S_OK;
}

void map2::release()
{
}

void map2::update()
{
	pl->update();

	if (pl->getPos().x < 10)
		gameScene::goToRoom(1);

	gameScene::updateViewport(pl->getPos().x, pl->getPos().y);
}

void map2::render()
{
	IMG->find("ÀüÅõ ¸Ê 2")->render(getMemDC(), _currOrg.x, 96, _currOrg.x, 0, WINW, 640);
}
