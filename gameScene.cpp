#include "stdafx.h"
#include "gameScene.h"
#include "player.h"
#include "map1.h"
#include "map2.h"

player* gameScene::_p;
map1* gameScene::_map1;
map2* gameScene::_map2;
map_* gameScene::_currMap;
int gameScene::prevMapIdx, gameScene::mapIdx;

gameScene::gameScene()
{
}

gameScene::~gameScene()
{
}

HRESULT gameScene::init()
{
	_currOrg = _newOrg = { 0, 0 };
	IMG->addF("테스트", "test.bmp", 624, 184, 6, 2, TRUE, RGB(255, 0, 255));
	IMG->find("테스트")->changeColor(RGB(0, 232, 216), RGB(0, 255, 0));

	_p = new player;
	_p->init();

	_isInShop = false;
	_shouldBePaused = false;
	
	_map1 = new map1;
	_map2 = new map2;

	prevMapIdx = mapIdx = 0;

	_totRegion = { 0, 0, 3036, 640 };
	_camMovLim = { _totRegion.left, _totRegion.top, _totRegion.right - _totRegion.left - WINW, _totRegion.top };
	_currMap = _map1;
	_currMap->setLinkTo(_p);
	_currMap->init();
	return S_OK;
}

void gameScene::release()
{
	_p->release();
	SAFE_DEL(_p);

	_currMap->release();
	SAFE_DEL(_map1);
	SAFE_DEL(_map2);
}

void gameScene::update()
{

	_currMap->update();
}

void gameScene::render()
{
	PatBlt(getMemDC(), 0, 0, WINW, WINH, BLACKNESS);
	_currMap->render();

	IMG->find("테스트")->frameRender(getMemDC(), _p->getPos().x, _p->getPos().y);

	char str[256];
#ifdef _DEBUG
	{
		sprintf_s(str, "Player pos: %d, %d", _p->getPos().x, _p->getPos().y);
		TextOut(getMemDC(), 0, 48, str, static_cast<int>(strlen(str)));
	}
#endif
	
}

void gameScene::goToRoom(int idx)
{
	_currMap->release();

	prevMapIdx = mapIdx;
	switch (idx)
	{
		case 1:
			_totRegion = { 0, 0, 3036, 640 };
			_camMovLim = { _totRegion.left, _totRegion.top, _totRegion.right - _totRegion.left - WINW, _totRegion.top };
			_currMap = _map1;
			break;
		case 2:
			_totRegion = { 0, 0, 2012, 640 };
			_camMovLim = { _totRegion.left, _totRegion.top, _totRegion.right - _totRegion.left - WINW, _totRegion.top };
			_currMap = _map2;
			break;
	}
	_currMap->setLinkTo(_p);
	_currMap->init();
}

void gameScene::updateViewport(int x, int y)
{
	//if (y - VIEWPORT_UPDATE_OFFSET > _currOrg.y + WINH / 2)
	//{
	//	if (_currOrg.y < _camMovLim.bottom)
	//		_newOrg.y = _currOrg.y + static_cast<int>(static_cast<float>(_camMovLim.bottom - _currOrg.y) / 12.f) + 1;
	//	if (y < _newOrg.y + WINH / 2) _newOrg.y = y - WINH / 2;
	//}
	//else if (y + VIEWPORT_UPDATE_OFFSET < _currOrg.y + WINH / 2)
	//{
	//	if (_currOrg.y > _camMovLim.top)
	//		_newOrg.y = _currOrg.y - static_cast<int>(static_cast<float>(_currOrg.y - _camMovLim.top) / 12.f) - 1;
	//	if (y > _newOrg.y + WINH / 2) _newOrg.y = y - WINH / 2;
	//}
	if (x - VIEWPORT_UPDATE_OFFSET > _currOrg.x + WINW / 2)
	{
		if (_currOrg.x < _camMovLim.right)
			_newOrg.x = _currOrg.x + static_cast<int>(static_cast<float>(_camMovLim.right - _currOrg.x) / 12.f) + 1;
		if (x < _newOrg.x + WINW / 2) _newOrg.x = x - WINW / 2;
	}
	else if (x + VIEWPORT_UPDATE_OFFSET < _currOrg.x + WINW / 2)
	{
		if (_currOrg.x > _camMovLim.left)
			_newOrg.x = _currOrg.x - static_cast<int>(static_cast<float>(_currOrg.x - _camMovLim.left) / 12.f) - 1;
		if (x > _newOrg.x + WINW / 2) _newOrg.x = x - WINW / 2;
	}
	if (_newOrg.x != _currOrg.x) // || _newOrg.y != _currOrg.y)
	{
		_currOrg.x = _newOrg.x;
		//_currOrg.y = _newOrg.y;
	}
}

void gameScene::setViewport(int x, int y)
{
	//if (y - VIEWPORT_UPDATE_OFFSET > _currOrg.y + WINH / 2)
	//{
	//	_newOrg.y = min(y - WINH / 2, _camMovLim.bottom);
	//}
	//else if (y + VIEWPORT_UPDATE_OFFSET < _currOrg.y + WINH / 2)
	//{
	//	_newOrg.y = max(y - WINH / 2, _camMovLim.top);
	//}
	if (x - VIEWPORT_UPDATE_OFFSET > _currOrg.x + WINW / 2)
	{
		_newOrg.x = min(x - WINW / 2, _camMovLim.right);
	}
	else if (x + VIEWPORT_UPDATE_OFFSET < _currOrg.x + WINW / 2)
	{
		_newOrg.x = max(x - WINW / 2, _camMovLim.left);
	}
	_currOrg.x = _newOrg.x;
	//_currOrg.y = _newOrg.y;
}