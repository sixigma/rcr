#include "stdafx.h"
#include "gameScene.h"
#include "player.h"
#include "item.h"

void gameScene::drawTopSecondBox()
{
	BitBlt(getMemDC(), 0, 0, WINW - _topBoxAdjX, 96, getMemDC(), _topBoxAdjX, 0, SRCCOPY);
	PatBlt(_hBoxDC, 0, 96 + 640, WINW, WINH - 640 - 96, BLACKNESS);

	string tempStr = _p->getPlayerChName() + "    $   " + to_string(_p->currentMoney());
	tempStr.insert(tempStr.end() - 2, 1, '.');

	DrawText(_hBoxDC, tempStr.c_str(), -1, &_topBoxTextArea, DT_LEFT | DT_TOP | DT_SINGLELINE);

	BitBlt(getMemDC(), WINW - _topBoxAdjX, 0, _topBoxAdjX, 96, _hBoxDC, 0, 0, SRCCOPY);
}

void gameScene::drawBottomSecondBox()
{
	BitBlt(getMemDC(), 0, 96 + 640, WINW - _bottomBoxAdjX, WINH - 640 - 96, getMemDC(), _bottomBoxAdjX, 96 + 640, SRCCOPY);
	PatBlt(_hBoxDC, 0, 96 + 640, WINW, WINH - 640 - 96, BLACKNESS);

	DrawText(_hBoxDC, "BELONGINGS", -1, &_bottomBoxTextArea[0], DT_LEFT | DT_TOP | DT_SINGLELINE);
	DrawText(_hBoxDC, "VOLUME", -1, &_bottomBoxTextArea[1], DT_LEFT | DT_TOP | DT_SINGLELINE);
	DrawText(_hBoxDC, "LEVELS", -1, &_bottomBoxTextArea[2], DT_LEFT | DT_TOP | DT_SINGLELINE);
	DrawText(_hBoxDC, "STATUS", -1, &_bottomBoxTextArea[3], DT_LEFT | DT_TOP | DT_SINGLELINE);
	DrawText(_hBoxDC, "HELP", -1, &_bottomBoxTextArea[4], DT_LEFT | DT_TOP | DT_SINGLELINE);

	if (_shouldShowBottomBoxArrow)
	{
		IMG->frameRender("타일셋", _hBoxDC, _bottomBoxArrowPos[_bottomBoxArrowPosIdx].x + _currOrg.x, _bottomBoxArrowPos[_bottomBoxArrowPosIdx].y + _currOrg.y, 11, 3);
	}

	BitBlt(getMemDC(), WINW - _bottomBoxAdjX, 96 + 640, _bottomBoxAdjX, WINH - 640 - 96, _hBoxDC, 0, 96 + 640, SRCCOPY);
}

void gameScene::showBelongingsScr()
{
	// 하단 영역 화살표 표시
	if (_shouldShowBottomBoxArrow)
	{
		PatBlt(_hBoxDC, 0, 96 + 640, WINW, WINH - 640 - 96, BLACKNESS);
		IMG->frameRender("타일셋", _hBoxDC, _bottomBoxArrowPos[_bottomBoxArrowPosIdx].x + _currOrg.x, _bottomBoxArrowPos[_bottomBoxArrowPosIdx].y + _currOrg.y, 11, 3);
		BitBlt(getMemDC(), 0, 96 + 640, WINW, WINH - 640 - 96, _hBoxDC, 0, 96 + 640, SRCCOPY);
	}

	// 주 화면 영역 화살표 표시
	if (_shouldShowMainBoxArrow)
	{
		PatBlt(_hBoxDC, 0, 96, WINW, 640, BLACKNESS);
		IMG->frameRender("타일셋", _hBoxDC, _mainBoxArrowPos[_mainBoxArrowPosIdx].x + _currOrg.x, _mainBoxArrowPos[_mainBoxArrowPosIdx].y + _currOrg.y, 10, 2);
		BitBlt(getMemDC(), 0, 96, WINW, 640, _hBoxDC, 0, 96, SRCPAINT);
	}



	//if (!_itemNameTextArea.empty())
	//{
	//	for (int i = 0; i < _itemList.size(); ++i)
	//	{
	//		Rectangle(getMemDC(), _itemNameTextArea[i].left, _itemNameTextArea[i].top, _itemNameTextArea[i].right, _itemNameTextArea[i].bottom);
	//	}
	//}
	L->render();
}

void gameScene::showVolumeScr()
{

}

void gameScene::showLevelsScr()
{

}

void gameScene::showStatusScr()
{

}

void gameScene::showHelpScr()
{

}

void gameScene::updateMenuScr(BYTE idx)
{
	switch (idx)
	{
		case 0: // Belongings
			{
				// 창 끄기
				if (KEY->down('J') || (KEY->down('K') && _bottomBoxArrowPosIdx == 1))
				{
					_itemNameTextArea.clear();
					removeMenuScr(0);
					return;
				}

				// 아이템 사용하기


				// 아이템 버리기



				// 창 내용 표시하기
				_itemPtrList = _p->getVItem();
				_itemList.clear();
				if (_itemPtrList.empty())
				{
					_itemList.push_back("Nothing");
					//_itemList.push_back("Nothing"); // 리마인더: 시험용
					//_itemList.push_back("Nothing"); // 리마인더: 시험용
					//_itemList.push_back("Nothing"); // 리마인더: 시험용
					//_itemList.push_back("Nothing"); // 리마인더: 시험용
					//_itemList.push_back("Nothing"); // 리마인더: 시험용
					//_itemList.push_back("Nothing"); // 리마인더: 시험용
					//_itemList.push_back("Nothing"); // 리마인더: 시험용
				}
				else
				{
					for (int i = 0; i < _itemList.size(); ++i)
					{
						_itemList.push_back(_itemPtrList[i]->getName());
					}
				}

				if (_itemNameTextArea.size() != _itemList.size())
				{
					_shouldShowBottomBoxArrow =	_shouldShowMainBoxArrow = false;
					_itemNameTextArea.clear(); _itemNameTextArea.reserve(_itemList.size());
					_mainBoxArrowPos.clear(); _mainBoxArrowPos.reserve(_itemList.size());
					L->AllDeleteLine();

					string tempStr = "";
					for (int i = 0; i < _itemList.size(); ++i)
					{
						_itemNameTextArea.push_back({ 128, 200 + 60 * i, 462, 200 + 60 * i + 36 });
						tempStr += _itemList[i] + "%";

						_mainBoxArrowPos.push_back({66, 200 + 60 * i});
					}
					L->CreateLine({ _itemNameTextArea[0].left, _itemNameTextArea[0].top }, tempStr, "itemList", false);
					
					// 플레이어 캐릭터 이름 및 체력 표시 준비
					_hPString = "";
					size_t hPBarsToDraw = static_cast<size_t>(_p->currentHP() + 7) / 8llu;
					for (size_t i = 0; i < (hPBarsToDraw >> 1); ++i)
					{
						_hPString += '{';
					}
					if (hPBarsToDraw % 2 == 1) _hPString += '}';
					L->calmLine({ 64, 36 }, _p->getPlayerChName() + " " + _hPString);
				}
				else
				{
					L->update();
					int itemListSizeTimesTen = _itemList.size() * 8;
					if (_bottomBoxCountForBelongings < itemListSizeTimesTen) ++_bottomBoxCountForBelongings;
					else if (_bottomBoxCountForBelongings == itemListSizeTimesTen)
					{
						L->CreateLine({ 64, 768 }, "Select belonging & its use.%   USE    EXIT    THROW AWAY", "bottomBoxText", false);
						++_bottomBoxCountForBelongings;
					}
					else if (_bottomBoxCountForBelongings < itemListSizeTimesTen + 40)
						++_bottomBoxCountForBelongings;
					else if (_bottomBoxCountForBelongings == itemListSizeTimesTen + 40)
					{
						_bottomBoxArrowPos.clear();
						_bottomBoxArrowPos.reserve(3);
						_bottomBoxArrowPos = { { 128, 828 }, { 352, 828 }, { 608, 828 } };
						SND->play("36.wav", _currMasterVolume * _currSFXVolume);

						_bottomBoxArrowPosIdx = 0;
						_shouldShowBottomBoxArrow = true;
						++_bottomBoxCountForBelongings;

						_mainBoxArrowPosIdx = 0;
						_shouldShowMainBoxArrow = true;
					}
				}
			}
			break;
		case 1: // Volume
			{
				// 창 끄기
				if (KEY->down('J'))
				{
					removeMenuScr(1);
					return;
				}
			}
			break;
		case 2: // Levels
			{
				// 창 끄기
				if (KEY->down('J') || KEY->down(VK_RETURN))
				{
					removeMenuScr(2);
					return;
				}
			}
			break;
		case 3: // Status
			{
				// 창 끄기
				if (KEY->down('J') || KEY->down(VK_RETURN))
				{
					removeMenuScr(3);
					return;
				}
			}
			break;
		case 4: // Help
			{
				// 창 끄기
				if (KEY->down('J') || KEY->down(VK_RETURN))
				{
					removeMenuScr(4);
					return;
				}
			}
			break;
	}
}

void gameScene::removeMenuScr(BYTE prevBottomBoxArrowPosIdx)
{
	L->AllDeleteLine();
	_bottomBoxArrowPosIdx = prevBottomBoxArrowPosIdx;
	_shouldShowMenuScreen = _shouldShowBottomBoxArrow = _shouldShowMainBoxArrow = false;

	_bottomBoxTextArea.clear();
	_bottomBoxTextArea.reserve(5);
	_bottomBoxTextArea = { {100, 768 - 12, 418, 796 + 8}, {724, 768 - 12, 912, 796 + 8}, {100, 832 - 12, 292, 860 + 8}, {426, 832 - 12, 620, 860 + 8}, {788, 832 - 12, 912, 860 + 8} };
	_bottomBoxArrowPos.clear();
	for (int i = 0; i < _bottomBoxTextArea.size(); ++i)
		_bottomBoxArrowPos.push_back({ _bottomBoxTextArea[i].left - 32, _bottomBoxTextArea[i].top + 14 });
	_shouldFadeOut = TRUE;
}