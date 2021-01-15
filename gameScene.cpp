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
#include "item.h"

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

	_shouldShowBottomBoxArrow = false;
	_shouldShowMenuScreen = FALSE;

	_hFont = CreateFont(46, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FIXED_PITCH | FF_MODERN, "RCR_Mono2");
	
	_bottomBoxArrowPosIdx = 0;
	_bottomBoxTextArea = { {100, 768 - 12, 418, 796 + 8}, {724, 768 - 12, 912, 796 + 8}, {100, 832 - 12, 292, 860 + 8}, {426, 832 - 12, 620, 860 + 8}, {788, 832 - 12, 912, 860 + 8} };
	_topBoxTextArea = {64, 36 - 14, WINW - 64, 64 + 8};

	for (int i = 0; i < _bottomBoxTextArea.size(); ++i)
		_bottomBoxArrowPos.push_back({ _bottomBoxTextArea[i].left - 32, _bottomBoxTextArea[i].top + 14});

	_hBoxDC = CreateCompatibleDC(getMemDC());
	_hBoxBitmap = CreateCompatibleBitmap(getMemDC(), WINW, WINH);
	_hOBoxBitmap = (HBITMAP)SelectObject(_hBoxDC, _hBoxBitmap);
	SetTextColor(_hBoxDC, RGB(255, 255, 255));
	SetBkMode(_hBoxDC, TRANSPARENT);
	_hOFont = (HFONT)SelectObject(_hBoxDC, _hFont);

	_hBrush1 = CreateSolidBrush(RGB(127, 127, 127));
	_hBrush2 = CreateSolidBrush(RGB(152, 232, 0));

	_countForFading = 0;
	_shouldShowMoneyOnTop = false;

	_xPosForLevels = 0;
	switch (_lineSpd)
	{
		case 1:
			_yPosForLevels = 2;
			break;
		case 3:
			_yPosForLevels = 1;
			break;
		case 5:
			_yPosForLevels = 0;
			break;
		default:
			_yPosForLevels = 1;
			break;
	}

	return S_OK;
}

void gameScene::release()
{
	if (!_p->getVItem().empty())
	{
		for (int i = 0; i < _p->getVItem().size(); ++i)
		{
			SAFE_DEL(_p->getVItem()[i]);
		}
	}

	_p->release();
	SAFE_DEL(_p);
	_currMap->release();
	for (size_t i = 0; i < _mapList.size(); ++i)
	{
		SAFE_DEL(_mapList[i]);
	}

	SelectObject(_hBoxDC, _hOFont);
	DeleteObject(_hFont);
	DeleteObject(SelectObject(_hBoxDC, _hOBoxBitmap));
	DeleteObject(_hBrush1);
	DeleteObject(_hBrush2);
}

void gameScene::update()
{
	if (_moveKeyDisabled)
	{
		if (_countForReEnablingKeyInput == 10) _shouldFadeOut = FALSE;
		if (_countForReEnablingKeyInput == 0) _moveKeyDisabled = FALSE;
		if (_countForReEnablingKeyInput > 0) --_countForReEnablingKeyInput;
	}

	if (!_shouldFadeOut && !_shouldShowMenuScreen)
	{
		if (!_shouldBePaused)
		{
			_p->update();
			_currMap->update();
		}

		if (_mapNum > 0)
		{
			_hPString = "";
			size_t hPBarsToDraw = static_cast<size_t>(_p->currentHP() + 7) / 8llu;
			for (size_t i = 0; i < (hPBarsToDraw >> 1); ++i)
			{
				switch (_mapNum)
				{
					case 1:
						_hPString += '[';
						break;
					case 2:
						_hPString += '<';
						break;
					case 3:
						_hPString += '(';
						break;
					case 4:
						_hPString += '^';
						break;
					case 402:
						_hPString += '@';
						break;
					case 5:
						_hPString += '~';
						break;
					case 6:
						_hPString += '{';
						break;
				}	
			}
			if (hPBarsToDraw % 2 == 1)
			{
				switch (_mapNum)
				{
					case 1:
						_hPString += ']';
						break;
					case 2:
						_hPString += '>';
						break;
					case 3:
						_hPString += ')';
						break;
					case 4:
						_hPString += '_';
						break;
					case 402:
						_hPString += '|';
						break;
					case 5:
						_hPString += '+';
						break;
					case 6:
						_hPString += '}';
						break;
				}
			}
			L->selectDeleteLine("CaLm");
			L->calmLine({ 64, 36 }, _p->getPlayerChName() + " " + _hPString);
		}
	}

	if (KEY->down(VK_RETURN) && !_isInShop)
	{
		if (!_shouldBePaused)
		{
			SND->pauseAll();
			SND->play("35.wav", _currMasterVolume * _currSFXVolume);
			_shouldBePaused = !_shouldBePaused;
		}
		else if (!_shouldShowMenuScreen)
		{
			SND->resumeAll();
			_bottomBoxArrowPosIdx = 0;
			_shouldShowBottomBoxArrow = false;
			_shouldBePaused = !_shouldBePaused;
		}
	}
	
	if (KEY->down(VK_RSHIFT) && !_isInShop && !_shouldFadeOut && !_shouldShowMenuScreen)
	{
		SND->play("41.wav", _currMasterVolume * _currSFXVolume);
		_shouldShowMoneyOnTop = !_shouldShowMoneyOnTop;
	}

	if (!_shouldBePaused)
	{
		L->update();
		if (_bottomBoxAdjX != 0) _bottomBoxAdjX -= min(20, _bottomBoxAdjX);
	}
	else if (_bottomBoxAdjX != WINW)
	{
		_bottomBoxAdjX += min(20, WINW - _bottomBoxAdjX);
	}
	else if (_bottomBoxAdjX == WINW && !_shouldShowBottomBoxArrow && !_shouldShowMenuScreen)
	{
		if (_countForFading == 0) SND->play("36.wav", _currMasterVolume * _currSFXVolume);
		_shouldShowBottomBoxArrow = true;
	}

	if (_shouldShowMoneyOnTop) _topBoxAdjX += min(20, WINW - _topBoxAdjX);
	else if (_topBoxAdjX != 0) _topBoxAdjX -= min(20, _topBoxAdjX);

	if (_shouldShowBottomBoxArrow)
	{
		if (KEY->down('D') && _bottomBoxArrowPosIdx < _bottomBoxArrowPos.size() - 1)
		{
			SND->play("36.wav", _currMasterVolume * _currSFXVolume);
			++_bottomBoxArrowPosIdx;
		}
		else if (KEY->down('A') && _bottomBoxArrowPosIdx > 0)
		{
			SND->play("36.wav", _currMasterVolume * _currSFXVolume);
			--_bottomBoxArrowPosIdx;
		}
		else if (KEY->down('K') && !_shouldShowMenuScreen && _countForFading == 0)
		{
			_shouldShowMenuScreen = TRUE;
			_shouldShowBottomBoxArrow = false;
			L->AllDeleteLine();
			_countForFading = 0;
		}
	}

	if (_shouldShowMenuScreen)
	{
		if (!_mainBoxArrowPos.empty() && _shouldShowMainBoxArrow)
		{
			if (KEY->down('S') && _mainBoxArrowPosIdx < _mainBoxArrowPos.size() - 1)
			{
				SND->play("36.wav", _currMasterVolume * _currSFXVolume);
				++_mainBoxArrowPosIdx;
			}
			else if (KEY->down('W') && _mainBoxArrowPosIdx > 0)
			{
				SND->play("36.wav", _currMasterVolume * _currSFXVolume);
				--_mainBoxArrowPosIdx;
			}
		}

		if (_countForFading == 0)
		{
			_shouldFadeOut = TRUE;
			_currMenuIdx = _bottomBoxArrowPosIdx;
			++_countForFading;
		}
		else if (_countForFading > 0 && _countForFading < 21)
		{
			++_countForFading;
		}
		else if (_countForFading > 20 && _countForFading < 41)
		{
			if (_shouldFadeOut) _shouldFadeOut = FALSE;
			++_countForFading;
			if (_countForFading == 40)
			{
				switch (_currMenuIdx)
				{
					case 0:
						{
							if (!SND->isPlaying("5 - Menu.mp3"))
							{
								SND->play("5 - Menu.mp3", _currMasterVolume * _currBGMVolume);
							}
							_bottomBoxCountForBelongings = 0;
						}
						break;
					case 1:
						{
							if (!SND->isPlaying("6 - Password.mp3"))
							{
								SND->play("6 - Password.mp3", _currMasterVolume * _currBGMVolume);
							}
							_bottomBoxCountForVolume = 0;
						}
						break;
					case 2:
						{
							if (!SND->isPlaying("1 - Game Mode & Character Select.mp3"))
							{
								SND->play("1 - Game Mode & Character Select.mp3", _currMasterVolume * _currBGMVolume);
							}
							_bottomBoxCountForLevels = 0;
						}
						break;
					case 3:
						{
							if (!SND->isPlaying("2 - Prologue & Epilogue.mp3"))
							{
								SND->play("2 - Prologue & Epilogue.mp3", _currMasterVolume * _currBGMVolume);
							}
							_bottomBoxCountForStatus = 0;
						}
						break;
					case 4:
						{
							if (!SND->isPlaying("6 - Password.mp3"))
							{
								SND->play("6 - Password.mp3", _currMasterVolume * _currBGMVolume);
							}
							_bottomBoxCountForHelp = 0;
						}
						break;
				}
			}
			if (_currMenuIdx > 1) updateMenuScr(_currMenuIdx);
		}
		else if (_countForFading > 40)
		{
			updateMenuScr(_currMenuIdx);
		}	
	}
	else if (_countForFading > 40 && _countForFading < 60)
	{
		switch (_currMenuIdx)
		{
			case 0: SND->stop("5 - Menu.mp3"); break;
			case 1: SND->stop("6 - Password.mp3"); break;
			case 2: SND->stop("1 - Game Mode & Character Select.mp3"); break;
			case 3: SND->stop("2 - Prologue & Epilogue.mp3"); break;
			case 4: { SND->stop("6 - Password.mp3"); SND->stop("5 - Menu.mp3"); } break;
		}

		L->AllDeleteLine();
		++_countForFading;
	}
	else if (_countForFading > 59 && _countForFading < 70)
	{
		_shouldFadeOut = FALSE;
		++_countForFading;
	}
	else if (_countForFading == 70)
	{
		_countForFading = 0;
	}

#ifdef _DEBUG
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
		_p->setPlayerChName(INI->loadDataString("STATUS", "PLAYER", "NAME").substr(0, 5));
		_p->setEndure(INI->loadDataInteger("STATUS", "PLAYER", "ENDURE") % 64);
		_p->setEnergy(INI->loadDataInteger("STATUS", "PLAYER", "ENERGY") % 64);
		_p->setGuard(INI->loadDataInteger("STATUS", "PLAYER", "GUARD") % 64);
		_p->setHP(INI->loadDataInteger("STATUS", "PLAYER", "HP") % 128);
		_p->setMaxHP(INI->loadDataInteger("STATUS", "PLAYER", "MAXHP") % 128);
		_p->setKick(INI->loadDataInteger("STATUS", "PLAYER", "KICK") % 64);
		_p->setPower(INI->loadDataInteger("STATUS", "PLAYER", "POWER") % 64);
		_p->setWeapon(INI->loadDataInteger("STATUS", "PLAYER", "WEAPON") % 64);
		_p->setAgility(INI->loadDataInteger("STATUS", "PLAYER", "AGILITY") % 64);
		_p->setPunch(INI->loadDataInteger("STATUS", "PLAYER", "PUNCH") % 64);
		_p->setMoney(INI->loadDataInteger("STATUS", "PLAYER", "MONEY") % 999991);
	}
#endif
}

void gameScene::render()
{
//#ifdef _DEBUG
//	if (KEY->down(VK_F1))
//	{
//		_shouldShowMenuScreen = !_shouldShowMenuScreen;
//		_countForFading = 0;
//	}
//#endif

	if (!_shouldShowMenuScreen)
	{
		PatBlt(getMemDC(), 0, 96, WINW, 640, WHITENESS);
		_currMap->render();
		_p->render();

		if (!_isInShop) IMG->execZ();
	}
	
#ifdef _DEBUG
	char str[256];
	if (KEY->isToggledOn(VK_TAB)) DrawRct(getMemDC(), _p->getPos().x - 32, _p->getPos().y - 8, 64, 8);
#endif

	PatBlt(getMemDC(), 0, 0, WINW, 96, BLACKNESS);

	if (_shouldBePaused)
	{
		L->selectUpdate("CaLm");
		L->selectRender("CaLm");
	}

	PatBlt(getMemDC(), 0, 96 + 640, WINW, WINH - 640 - 96, BLACKNESS);

	if (_shouldShowMenuScreen)
	{
		if (_countForFading > 20)
		{
			if (_currMenuIdx != 4) IMG->render("파란 화면", getMemDC(), _currOrg.x, 96, 0, 0, WINW, 640);
			else IMG->render("파란 화면", getMemDC(), _currOrg.x, _currOrg.y, 0, 0, WINW, WINH);
			switch (_currMenuIdx)
			{
				case 2:
					showLevelsScr();
					break;
				case 3:
					showStatusScr();
					break;
				case 4:
					showHelpScr();
					break;
				default:
					break;
			}
		}
		
		if (_countForFading > 40)
		{
			switch (_currMenuIdx)
			{
				case 0:
					showBelongingsScr();
					break;
				case 1:
					showVolumeScr();
					break;
				default:
					break;
			}
		}
	}
	else L->render();


	// 하단 영역에 메뉴 보이기
	if (_topBoxAdjX > 0 && (_countForFading < 21 || _countForFading > 59) && !_isInShop)
	{
		drawTopSecondBox();
	}

	// 하단 영역에 메뉴 보이기
	if (_bottomBoxAdjX > 0 && (_countForFading < 21 || _countForFading > 59) && !_isInShop)
	{
		drawBottomSecondBox();
	}

#ifdef _DEBUG
		{
			if (KEY->isToggledOn(VK_SCROLL))
			{
				sprintf_s(str, "Player pos: %d, %d", _p->getPos().x, _p->getPos().y);
				TextOut(getMemDC(), 0, 48, str, static_cast<int>(strlen(str)));

				sprintf_s(str, "Pointer pos: %d, %d (%d, %d)", _mouse.x + _currOrg.x, _mouse.y + _currOrg.y, _mouse.x, _mouse.y);
				TextOut(getMemDC(), 0, 64, str, static_cast<int>(strlen(str)));

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
