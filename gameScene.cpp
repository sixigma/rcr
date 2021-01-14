#include "stdafx.h"
#include "gameScene.h"
#include "player.h"
#include "map1.h"
#include "map2.h"
#include "map3.h"
#include "map4.h"
#include "map4-2.h"
#include "map5.h"
#include "shop.h"

player* gameScene::_p;
vector<map_*> gameScene::_mapList;
map_* gameScene::_currMap;
int gameScene::_prevMapNum, gameScene::_mapNum, gameScene::_prevshopNum, gameScene::_shopNum;
int gameScene::_countForReEnablingKeyInput;

gameScene::gameScene()
{
}

gameScene::~gameScene()
{
}

HRESULT gameScene::init()
{
	_currOrg = _newOrg = { 0, 0 };

	_p = new player;
	_p->init();

	_isInShop = false;
	_shouldBePaused = false;
	
	_mapList.push_back(new map1); // 0
	_mapList.push_back(new map2); // 1
	_mapList.push_back(new map3); // 2
	_mapList.push_back(new map4); // 3
	_mapList.push_back(new map4_2); // 4
	_mapList.push_back(new map5); // 5
	_mapList.push_back(new shop); // 상점

	_prevMapNum = _mapNum =  0;

	_totRegion = { 0, 0, 3036, 640 };
	_camMovLim = { _totRegion.left, _totRegion.top, _totRegion.right - _totRegion.left - WINW, _totRegion.top };
	_currMap = _mapList[0];
	_currMap->setLinkTo(_p);
	_currMap->init();
	return S_OK;
}

void gameScene::release()
{
	_p->release();
	SAFE_DEL(_p);

	_currMap->release();
	for (size_t i = 0; i < _mapList.size(); ++i)
	{
		SAFE_DEL(_mapList[i]);
	}
}

void gameScene::update()
{
	if (_moveKeyDisabled)
	{
		if (_countForReEnablingKeyInput == 10) _shouldFadeOut = FALSE;
		if (_countForReEnablingKeyInput == 0) _moveKeyDisabled = FALSE;
		--_countForReEnablingKeyInput;
	}

	if (!_shouldFadeOut && !_shouldShowMenuScreen && !_shouldBePaused)
	{
		_p->update();
		_currMap->update();
	}

	if (KEY->down(VK_RETURN))
	{
		if (!_shouldBePaused) SND->play("35.wav", _currMasterVolume * _currSFXVolume);
		_shouldBePaused = !_shouldBePaused;
	}
	if (!_shouldBePaused)
	{
		L->update();
	}
	if (KEY->down('2')) //플레이어 status 저장
	{
		string name;
		name = _p->getPlayerChName();
		INI->addData("PLAYER", "NAME", name.c_str());
		string tempString;
		tempString = to_string(_p->currentEndure());
		INI->addData("PLAYER", "ENDURE", tempString.c_str());
		string tempString1;
		tempString1 = to_string(_p->currentEnergy());
		INI->addData("PLAYER", "ENERGY", tempString1.c_str());
		string tempString2;
		tempString2 = to_string(_p->currentGuard());
		INI->addData("PLAYER", "GUARD", tempString2.c_str());
		string tempString3;
		tempString3 = to_string(_p->currentHP());
		INI->addData("PLAYER", "HP", tempString3.c_str());
		string tempString4;
		tempString4 = to_string(_p->currentMaxHP());
		INI->addData("PLAYER", "MAXHP", tempString4.c_str());
		string tempString5;
		tempString5 = to_string(_p->currentKick());
		INI->addData("PLAYER", "KICK", tempString5.c_str());
		string tempString6;
		tempString6 = to_string(_p->currentPower());
		INI->addData("PLAYER", "POWER", tempString6.c_str());
		string tempString7;
		tempString7 = to_string(_p->currentWeapon());
		INI->addData("PLAYER", "WEAPON", tempString7.c_str());
		string tempString8;
		tempString8 = to_string(_p->currentAgility());
		INI->addData("PLAYER", "AGILITY", tempString8.c_str());
		string tempString9;
		tempString9 = to_string(_p->currentPunch());
		INI->addData("PLAYER", "PUNCH", tempString9.c_str());
		string tempString10;
		tempString10 = to_string(_p->currentMoney());
		INI->addData("PLAYER", "MONEY", tempString10.c_str());
		INI->iniSave("STATUS");
	}
	if (KEY->down('3')) //플레이어 status 로드
	{
		_p->setEndure(INI->loadDataInteger("STATUS", "PLAYER", "ENDURE"));
		_p->setEnergy(INI->loadDataInteger("STATUS", "PLAYER", "ENERGY"));
		_p->setGuard(INI->loadDataInteger("STATUS", "PLAYER", "GUARD"));
		_p->setHP(INI->loadDataInteger("STATUS", "PLAYER", "HP"));
		_p->setMaxHP(INI->loadDataInteger("STATUS", "PLAYER", "MAXHP"));
		_p->setKick(INI->loadDataInteger("STATUS", "PLAYER", "KICK"));
		_p->setPower(INI->loadDataInteger("STATUS", "PLAYER", "POWER"));
		_p->setWeapon(INI->loadDataInteger("STATUS", "PLAYER", "WEAPON"));
		_p->setAgility(INI->loadDataInteger("STATUS", "PLAYER", "AGILITY"));
		_p->setPunch(INI->loadDataInteger("STATUS", "PLAYER", "PUNCH"));
		_p->setMoney(INI->loadDataInteger("STATUS", "PLAYER", "MONEY"));
	}

}

void gameScene::render()
{
#ifdef _DEBUG
	if (KEY->down(VK_F1)) _shouldShowMenuScreen = !_shouldShowMenuScreen; // 리마인더: 시험용
#endif

	if (_shouldShowMenuScreen) IMG->render("파란 화면", getMemDC(), _currOrg.x, 96, 0, 0, WINW, 640);
	else
	{
		PatBlt(getMemDC(), 0, 96, WINW, 640, WHITENESS);
		_currMap->render();
		_p->render();

		IMG->execZ();
	}
	
#ifdef _DEBUG
	char str[256];
	if (KEY->isToggledOn(VK_TAB)) DrawRct(getMemDC(), _p->getPos().x - 32, _p->getPos().y - 8, 64, 8);
#endif

	PatBlt(getMemDC(), 0, 0, WINW, 96, BLACKNESS);
	PatBlt(getMemDC(), 0, 96 + 640, WINW, WINH - 640 - 96, BLACKNESS);
	L->render();

#ifdef _DEBUG
		{
			if (KEY->isToggledOn(VK_SCROLL))
			{
				sprintf_s(str, "Player pos: %d, %d", _p->getPos().x, _p->getPos().y);
				TextOut(getMemDC(), 0, 48, str, static_cast<int>(strlen(str)));

				sprintf_s(str, "Pointer pos: %d, %d (%d, %d)", _mouse.x + _currOrg.x, _mouse.y + _currOrg.y, _mouse.x, _mouse.y);
				TextOut(getMemDC(), 0, 64, str, static_cast<int>(strlen(str)));
			}

			if (_mouse.x + 42 < WINW)
			{
				Rectangle(getMemDC(), _mouse.x + 9, _mouse.y + 9, _mouse.x + 10 + 33, _mouse.y + 10 + 33);
				StretchBlt(getMemDC(), _mouse.x + 10, _mouse.y + 10, 32, 32, getMemDC(), _mouse.x - 8, _mouse.y - 8, 16, 16, SRCCOPY);
				DrawLine(getMemDC(), _mouse.x + 26 + _currOrg.x, _mouse.y + 26 + _currOrg.y, _mouse.x + 26 + _currOrg.x, _mouse.y + 30 + _currOrg.y);
				DrawLine(getMemDC(), _mouse.x + 26 + _currOrg.x, _mouse.y + 26 + _currOrg.y, _mouse.x + 30 + _currOrg.x, _mouse.y + 26 + _currOrg.y);
			}
			else
			{
				Rectangle(getMemDC(), _mouse.x - 43, _mouse.y + 9, _mouse.x + 10 - 19, _mouse.y + 10 + 33);
				StretchBlt(getMemDC(), _mouse.x - 42, _mouse.y + 10, 32, 32, getMemDC(), _mouse.x - 8, _mouse.y - 8, 16, 16, SRCCOPY);
				DrawLine(getMemDC(), _mouse.x - 26 + _currOrg.x, _mouse.y + 26 + _currOrg.y, _mouse.x - 26 + _currOrg.x, _mouse.y + 30 + _currOrg.y);
				DrawLine(getMemDC(), _mouse.x - 26 + _currOrg.x, _mouse.y + 26 + _currOrg.y, _mouse.x - 22 + _currOrg.x, _mouse.y + 26 + _currOrg.y);
			}
		}
#endif
}

void gameScene::goToMap(int num)
{
	_shouldFadeOut = TRUE;
	_moveKeyDisabled = TRUE;
	_currMap->release();
	_countForReEnablingKeyInput = 24;
	_prevMapNum = _mapNum;
	switch (num)
	{
		case 1:
			_totRegion = { 0, 96, 3036, 640 };
			_camMovLim = { _totRegion.left, 0, _totRegion.right - _totRegion.left - WINW, 0 };
			_isInShop = false;
			_currMap = _mapList[0];
			break;
		case 2:
			_totRegion = { 0, 96, 2012, 640 };
			_camMovLim = { _totRegion.left, 0, _totRegion.right - _totRegion.left - WINW, 0 };
			_isInShop = false;
			_currMap = _mapList[1];
			break;
		case 3:
			_totRegion = { 0, 96, 2012, 640 };
			_camMovLim = { _totRegion.left, 0, _totRegion.right - _totRegion.left - WINW, 0 };
			_isInShop = false;
			_currMap = _mapList[2];
			break;
		case 4:
			_totRegion = { 0, 96, 3040, 640 };
			_camMovLim = { _totRegion.left, 0, _totRegion.right - _totRegion.left - WINW, 0 };
			_isInShop = false;
			_currMap = _mapList[3];
			break;
		case 402:
			_totRegion = { 0, 96, 1884, 640 };
			_camMovLim = { _totRegion.left, 0, _totRegion.right - _totRegion.left - WINW, 0 };
			_isInShop = false;
			_currMap = _mapList[4];
			break;
		case 5:
			_totRegion = { 0, 96, 2012, 640 };
			_camMovLim = { _totRegion.left, 0, _totRegion.right - _totRegion.left - WINW, 0 };
			_isInShop = false;
			_currMap = _mapList[5];
			break;
		case 6:
			_totRegion = { 0 ,96 , 1024, 640 };
			_camMovLim = { 0, 0, 1024, 640 };
			_isInShop = true;
			_currMap = _mapList[6];
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
