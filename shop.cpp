#include "stdafx.h"
#include "shop.h"
#include "player.h"

HRESULT shop::init()
{

	if (SND->isPlaying("4 - Running Around.mp3"))
	{
		SND->stop("4 - Running Around.mp3");
	}
	if (!SND->isPlaying("5 - Menu.mp3"))
	{
		SND->play("5 - Menu.mp3", _currMasterVolume * _currBGMVolume);
		SND->findChannel("5 - Menu.mp3")->setLoopPoints(66137, FMOD_TIMEUNIT_MS, 133153, FMOD_TIMEUNIT_MS);
		SND->findChannel("5 - Menu.mp3")->setPosition(66137, FMOD_TIMEUNIT_MS);
		SND->findChannel("5 - Menu.mp3")->setLoopCount(-1);
	}

	L->AllDeleteLine();

	setMapNum(6);
	shopNumber = 0;
	currPlPos = &pl->getPos();
	*currPlPos = { _totRegion.right - 40, 592,0 };
	prevPlPos = *currPlPos;
	keyEnable = false;
	yesNoEnable = false;
	yesNoApply = false;
	apply = false;
	buy = false;
	_cMoney = 2000;
	_price = 0;
	shopIndex = 0;
	tempnum = 0;
	max = 0;
	tempStr = to_string(_cMoney);
	tempStr.insert(tempStr.end() - 2, 1, '.');

	for (int i = 0; i < 6; i++)
	{
		_point[i].enable = false;
		_point[i].num = tempnum;
		tempnum++;
	}

	tempnum = 0;
	for (int i = 0; i < 6; i++)
	{
		_itemBox[i].enable = false;
		_itemBox[i].num = tempnum;
		tempnum++;
	}

	for (int i = 0; i < 2; i++)
	{
		_yesNoPoint[i].enable = false;
		_yesNoPoint[i].num = tempnum;
		tempnum++;
	}

	tempnum = 0;
	for (int i = 0; i < 2; i++)
	{
		_yesNoBox[i].enable = false;
		_yesNoBox[i].num = tempnum;
		tempnum++;
	}

	//이미지 디스플레이
	_display.rc = MakeRct(145, 220, 265, 265);

	//상점이름
	_shopName.rc = MakeRct(145, 530, 265, 170);

	//달러소지금
	_money.rc = MakeRct(330, 120, 100, 40);

	//포인터 상자
	_point[0].rc = MakeRct(480, 241, 40, 40);
	_point[0].enable = true;
	_point[1].rc = MakeRct(480, 301, 40, 40);
	_point[2].rc = MakeRct(480, 361, 40, 40);
	_point[3].rc = MakeRct(480, 421, 40, 40);
	_point[4].rc = MakeRct(480, 481, 40, 40);
	_point[5].rc = MakeRct(480, 541, 40, 40);

	//아이템상자
	_itemBox[0].rc = MakeRct(530, 236, 500, 50);
	_itemBox[1].rc = MakeRct(530, 296, 500, 50);
	_itemBox[2].rc = MakeRct(530, 356, 500, 50);
	_itemBox[3].rc = MakeRct(530, 416, 500, 50);
	_itemBox[4].rc = MakeRct(530, 476, 500, 50);
	_itemBox[5].rc = MakeRct(530, 536, 500, 50);

	//YES NO
	_yesNoPoint[0].rc = MakeRct(520, 680, 40, 40);
	_yesNoPoint[1].rc = MakeRct(800, 680, 40, 40);

	_yesNoBox[0].rc = MakeRct(570, 680, 200, 40);
	_yesNoBox[1].rc = MakeRct(850, 680, 200, 40);

	gameScene::setViewport(0, 96);
	return S_OK;
}

void shop::release()
{
}

void shop::update()
{
	shopNumber = getShopNum();
	shopbuy();
	_cMoney = pl->currentMoney();
	
	if ((keyEnable == true) && (yesNoApply == true))
	{
		L->CreateLine(MakePt(_yesNoBox[0].rc.left - 70, _yesNoBox[0].rc.top + 5), "YES", "n", false, 0);
		L->CreateLine(MakePt(_yesNoBox[1].rc.left - 70, _yesNoBox[1].rc.top + 5), "NO", "n", false, 0);
	}

	

	if (!apply)
	{
		shopSetting();
	}
	pointmove();
}

void shop::render()
{
	IMG->find("상점맵")->render(getMemDC(), _newOrg.x, 96, 0, 0, WINW, 640);

	switch (shopNumber)
	{
	case 1:
		IMG->find("카페")->render(getMemDC(), _display.rc.left, _display.rc.top, 0, 0, 265, 265);
	break;
	
	case 2:
		IMG->find("빵집")->render(getMemDC(), _display.rc.left, _display.rc.top, 0, 0, 265, 265);
	break;
	
	case 3:
		IMG->find("초밥집")->render(getMemDC(), _display.rc.left, _display.rc.top, 0, 0, 265, 265);
	break;
	
	case 4:
		IMG->find("서점")->render(getMemDC(), _display.rc.left, _display.rc.top, 0, 0, 265, 265);
	break;
	}

	for (int i = 0; i < 6; i++)
	{
		if (_point[i].enable)
		{
			IMG->find("포인터")->render(getMemDC(), _point[i].rc.left, _point[i].rc.top, 0, 0, 40, 40);
		}
		if (_itemBox[i].enable)
		{
			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
			HPEN hOPen = (HPEN)SelectObject(getMemDC(), hPen);
			HBRUSH hOBrush = (HBRUSH)SelectObject(getMemDC(), hBrush);
			DrawRct(getMemDC(), _itemBox[i].rc);
			DeleteObject(SelectObject(getMemDC(), hOPen));
			DeleteObject(SelectObject(getMemDC(), hOBrush));
		}
	}
	//yesNo
	if ((keyEnable) && (yesNoApply))
	{
		for (int i = 0; i < 2; i++)
		{
			if (_yesNoPoint[i].enable)
			{
				IMG->find("포인터")->render(getMemDC(), _yesNoPoint[i].rc.left, _yesNoPoint[i].rc.top, 0, 0, 40, 40);
			}
			if (_yesNoBox[i].enable)
			{
				HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
				HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
				HPEN hOPen = (HPEN)SelectObject(getMemDC(), hPen);
				HBRUSH hOBrush = (HBRUSH)SelectObject(getMemDC(), hBrush);
				DrawRct(getMemDC(), _yesNoBox[i].rc);
				DeleteObject(SelectObject(getMemDC(), hOPen));
				DeleteObject(SelectObject(getMemDC(), hOBrush));
			}
		}
	}
	if (KEY->isToggledOn(VK_CAPITAL))
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
		HPEN hOPen = (HPEN)SelectObject(getMemDC(), hPen);
		HBRUSH hOBrush = (HBRUSH)SelectObject(getMemDC(), hBrush);
		for (size_t i = 0; i < itemmax; i++)
		{
			DrawRct(getMemDC(), _itemBox[i].rc);
			DrawRct(getMemDC(), _point[i].rc);
			DrawRct(getMemDC(), _display.rc);
			DrawRct(getMemDC(), _shopName.rc);
		}
		DrawRct(getMemDC(), _money.rc);
		DeleteObject(SelectObject(getMemDC(), hOPen));
		DeleteObject(SelectObject(getMemDC(), hOBrush));
	}
}

void shop::pointmove()
{
	int temp = 0;

	for (int i = 0; i < max; i++)
	{
		if (_point[i].enable == true)
		{
			if(KEY->down('W') && (_point[0].enable == false) && (keyEnable == false))
			{
				_point[i].enable = false;
				_point[i - 1].enable = true;
				break;
			}

			if (KEY->down('S') && (_point[max-1].enable == false) && (keyEnable == false))
			{
				_point[i].enable = false;
				_point[i + 1].enable = true;
				break;
			}
			// YES NO 등장할지 안등장할지 지정
			if (keyEnable == true && (!((shopNumber == 3)&&(shopIndex == 0))))
			{
				if (yesNoApply == false)
				{
					_yesNoPoint[0].enable = true;
					yesNoApply = true;
				}
				if (KEY->down('A') && (_yesNoPoint[0].enable == false))
				{
					_yesNoPoint[1].enable = false;
					_yesNoPoint[0].enable = true;
					break;
				}
				if (KEY->down('D') && (_yesNoPoint[1].enable == false))
				{
					_yesNoPoint[0].enable = false;
					_yesNoPoint[1].enable = true;
					break;
				}
			}

			if (KEY->down('K') && (keyEnable == true))
			{
				if (_yesNoPoint[0].enable)
				{
					//구매
					_yesNoPoint[0].enable = false;
					_yesNoPoint[1].enable = false;
					yesNoApply = false;
					yesNoEnable = false;
					keyEnable = false;
					buy = true;
					apply = false;
				}
				if (_yesNoPoint[1].enable)
				{
					//되돌아가기
					_yesNoPoint[0].enable = false;
					_yesNoPoint[1].enable = false;
					yesNoApply = false;
					yesNoEnable = false;
					_itemBox[i].enable = false;
					keyEnable = false;
				}
				break;
			}

			if (KEY->down('K') && (_point[i].enable))
			{
				if (_point[i].num == _itemBox[i].num)
				{
					if (i == (max - 1) && (shopIndex == 0)) //
					{
						apply = false;
						L->AllDeleteLine();
						gameScene::goToMap(3);
						gameScene::setShopNum(0);
						
					}
					else if (i == (max - 1) && (shopIndex != 0))
					{
						L->setKill("b");
						shopIndex = 0;
						_point[max - 1].enable = false;	//포인터값 초기화
						_point[0].enable = true;		//포인터값 위치 초기화
						apply = false;
					}
					if (i != (max - 1) && (!((shopNumber == 3) && (shopIndex == 0)))) //스시집이자 스시 index가0이 아닐때.
					{
						_itemBox[i].enable = true;
						keyEnable = true;
					}
					else if (i != (max - 1) && (shopNumber == 3) && (shopIndex == 0)) //스시집일때
					{
						if (i == 0)
						{
							L->setKill("a");
							shopIndex = 1;
							apply = false;
						}
						if (i == 1)
						{
							L->setKill("a");
							shopIndex = 2;
							apply = false;
						}
						if (i == 2)
						{
							L->setKill("a");
							shopIndex = 3;
							apply = false;
						}
					}

				}
			}
			if (KEY->down('J'))
			{
				if (keyEnable == false && (!((shopNumber == 3) && ((shopIndex == 1) || (shopIndex == 2) || (shopIndex == 3)))))
				{
					apply = false;
					L->AllDeleteLine();
					gameScene::goToMap(3);
					gameScene::setShopNum(0);
				}
				else if (keyEnable == false && (((shopNumber == 3) && ((shopIndex == 1) || (shopIndex == 2) || (shopIndex == 3)))))
				{
					L->setKill("b");
					shopIndex = 0;
					_point[i].enable = false;	//포인터값 초기화
					_point[0].enable = true;		//포인터값 위치 초기화
					apply = false;
				}
				else if (keyEnable == true)
				{
					if (yesNoEnable == true) //yes no가 활성화 되었을때
					{
						_yesNoPoint[0].enable = false;
						_yesNoPoint[1].enable = false;
						yesNoApply = false;
						yesNoEnable = false;
						keyEnable = false;
					}
					else if (yesNoEnable == false) //yesno가 비활성화됫을때
					{
						_itemBox[i].enable = false;
						keyEnable = false;
					}
				}
				break;
			}
		}
	}
}

void shop::shopSetting()
{
	if (_cMoney >= 100)
	{
		tempStr = to_string(_cMoney);
		tempStr.insert(tempStr.end() - 2, 1, '.');
		L->setKill("a");																   //소지금 갱신
		L->CreateLine(MakePt(_money.rc.left - 70, _money.rc.top + 5), tempStr, "a", false);
	}
	else if (_cMoney < 100 && 10 <= _cMoney)//소지금 출력 소지금 출력이 터져서
	{
		tempStr = to_string(_cMoney);
		L->setKill("a");																   //소지금 갱신
		L->CreateLine(MakePt(_money.rc.left - 70, _money.rc.top + 5), "0." + tempStr, "a", false);
	}
	else if (_cMoney < 10)
	{
		tempStr = to_string(_cMoney);
		L->setKill("a");																   //소지금 갱신
		L->CreateLine(MakePt(_money.rc.left - 70, _money.rc.top + 5), "0.0" + tempStr, "a", false);
	}

	if (shopNumber == 1)//RISE & SHINE CAFE
	{
		max = 6;
		L->CreateLine(MakePt(_shopName.rc.left - 70, _shopName.rc.top + 10), "Rise &%Shine%Cafe", "n", false);


		L->CreateLine(MakePt(_itemBox[0].rc.left - 70, _itemBox[0].rc.top + 10), "Coffee       .95", "n", false);
		L->CreateLine(MakePt(_itemBox[1].rc.left - 70, _itemBox[1].rc.top + 10), "Tea          .95", "n", false);
		L->CreateLine(MakePt(_itemBox[2].rc.left - 70, _itemBox[2].rc.top + 10), "Hot Cocoa   1.25", "n", false);
		L->CreateLine(MakePt(_itemBox[3].rc.left - 70, _itemBox[3].rc.top + 10), "Pancakes    3.30", "n", false);
		L->CreateLine(MakePt(_itemBox[4].rc.left - 70, _itemBox[4].rc.top + 10), "Waffles     4.10", "n", false);
		L->CreateLine(MakePt(_itemBox[5].rc.left - 70, _itemBox[5].rc.top + 10), "Nothing", "n", false);
	}
	if (shopNumber == 2)//Bakery
	{
		max = 6;
		L->CreateLine(MakePt(_shopName.rc.left - 70, _shopName.rc.top + 10), "Metro%Bakery", "n", false);


		L->CreateLine(MakePt(_itemBox[0].rc.left - 70, _itemBox[0].rc.top + 10), "Donut        .80", "n", false);
		L->CreateLine(MakePt(_itemBox[1].rc.left - 70, _itemBox[1].rc.top + 10), "Muffin       .90", "n", false);
		L->CreateLine(MakePt(_itemBox[2].rc.left - 70, _itemBox[2].rc.top + 10), "Bagel        .90", "n", false);
		L->CreateLine(MakePt(_itemBox[3].rc.left - 70, _itemBox[3].rc.top + 10), "Honey Bun    .90", "n", false);
		L->CreateLine(MakePt(_itemBox[4].rc.left - 70, _itemBox[4].rc.top + 10), "Croissant   1.00", "n", false);
		L->CreateLine(MakePt(_itemBox[5].rc.left - 70, _itemBox[5].rc.top + 10), "Nothing", "n", false);
	}
	if (shopNumber == 3)//Sushi
	{
		L->CreateLine(MakePt(_shopName.rc.left - 70, _shopName.rc.top + 10), "Sushi%Bar", "n", false);

		if (shopIndex == 0)
		{
			max = 4;
			L->CreateLine(MakePt(_itemBox[0].rc.left - 70, _itemBox[0].rc.top + 10), "Cheaper Sushi", "a", false);
			L->CreateLine(MakePt(_itemBox[1].rc.left - 70, _itemBox[1].rc.top + 10), "Expensive Sushi", "a", false);
			L->CreateLine(MakePt(_itemBox[2].rc.left - 70, _itemBox[2].rc.top + 10), "Rolls", "a", false);
			L->CreateLine(MakePt(_itemBox[3].rc.left - 70, _itemBox[3].rc.top + 10), "Nothing", "a", false);
		}

		if (shopIndex == 1)//cheaperSushi
		{
			max = 6;
			L->CreateLine(MakePt(_itemBox[0].rc.left - 70, _itemBox[0].rc.top + 10), "Egg         2.25", "b", false);
			L->CreateLine(MakePt(_itemBox[1].rc.left - 70, _itemBox[1].rc.top + 10), "Octopus     2.25", "b", false);
			L->CreateLine(MakePt(_itemBox[2].rc.left - 70, _itemBox[2].rc.top + 10), "Squid       2.25", "b", false);
			L->CreateLine(MakePt(_itemBox[3].rc.left - 70, _itemBox[3].rc.top + 10), "Conger Eel  3.75", "b", false);
			L->CreateLine(MakePt(_itemBox[4].rc.left - 70, _itemBox[4].rc.top + 10), "Prawn       6.00", "b", false);
			L->CreateLine(MakePt(_itemBox[5].rc.left - 70, _itemBox[5].rc.top + 10), "Main Menu", "b", false);
		}

		if (shopIndex == 2)//expensiveSushi
		{
			max = 6;
			L->CreateLine(MakePt(_itemBox[0].rc.left - 70, _itemBox[0].rc.top + 10), "Salmon      8.25", "b", false);
			L->CreateLine(MakePt(_itemBox[1].rc.left - 70, _itemBox[1].rc.top + 10), "Ark Shell   9.00", "b", false);
			L->CreateLine(MakePt(_itemBox[2].rc.left - 70, _itemBox[2].rc.top + 10), "Sea Urchin 11.50", "b", false);
			L->CreateLine(MakePt(_itemBox[3].rc.left - 70, _itemBox[3].rc.top + 10), "Halibut    18.50", "b", false);
			L->CreateLine(MakePt(_itemBox[4].rc.left - 70, _itemBox[4].rc.top + 10), "Swordfish  28.75", "b", false);
			L->CreateLine(MakePt(_itemBox[5].rc.left - 70, _itemBox[5].rc.top + 10), "Main Menu", "b", false);
		}

		if (shopIndex == 3)//Roll
		{
			max = 5;
			L->CreateLine(MakePt(_itemBox[0].rc.left - 70, _itemBox[0].rc.top + 10), "Salad Roll  2.00", "b", false);
			L->CreateLine(MakePt(_itemBox[1].rc.left - 70, _itemBox[1].rc.top + 10), "Tuna Roll   3.75", "b", false);
			L->CreateLine(MakePt(_itemBox[2].rc.left - 70, _itemBox[2].rc.top + 10), "Shrimp Roll 6.25", "b", false);
			L->CreateLine(MakePt(_itemBox[3].rc.left - 70, _itemBox[3].rc.top + 10), "Mixed Roll 10.50", "b", false);
			L->CreateLine(MakePt(_itemBox[4].rc.left - 70, _itemBox[4].rc.top + 10), "Main Menu", "b", false);
		}


	}
	if (shopNumber == 4)//bookstore
	{
		L->CreateLine(MakePt(_shopName.rc.left - 70, _shopName.rc.top + 10), "Grotto%Book%Store", "n", false);
		max = 4;
		L->CreateLine(MakePt(_itemBox[0].rc.left - 70, _itemBox[0].rc.top + 10), "MAHA PUNCH 26.95", "n", false);
		L->CreateLine(MakePt(_itemBox[1].rc.left - 70, _itemBox[1].rc.top + 10), "MAHA KICK  26.95", "n", false);
		L->CreateLine(MakePt(_itemBox[2].rc.left - 70, _itemBox[2].rc.top + 10), "SCREW BOMER26.95", "n", false);
		L->CreateLine(MakePt(_itemBox[3].rc.left - 70, _itemBox[3].rc.top + 10), "Nothing", "n", false);

	}
	apply = true;

}

void shop::shopbuy()
{
	if (buy == true)
	{
		item* _item;
		_item = new item;

		if (shopNumber == 1) //카페
		{
			if (_itemBox[0].enable == true)
			{
				_itemName = "Coffee";
				_itemBox[0].enable = false;
			}
			if (_itemBox[1].enable == true)
			{
				_itemName = "Tea";
				_itemBox[1].enable = false;
			}
			if (_itemBox[2].enable == true)
			{
				_itemName = "HotCocoa";
				_itemBox[2].enable = false;
			}
			if (_itemBox[3].enable == true)
			{
				_itemName = "Pancakes";
				_itemBox[3].enable = false;
			}
			if (_itemBox[4].enable == true)
			{
				_itemName = "Waffles";
				_itemBox[4].enable = false;
			}
		}

		if (shopNumber == 2) // 빵집
		{
			if (_itemBox[0].enable == true)
			{
				_itemName = "Donut";
				_itemBox[0].enable = false;
			}
			if (_itemBox[1].enable == true)
			{
				_itemName = "Muffin";
				_itemBox[1].enable = false;
			}
			if (_itemBox[2].enable == true)
			{
				_itemName = "Bagel";
				_itemBox[2].enable = false;
			}
			if (_itemBox[3].enable == true)
			{
				_itemName = "HoneyBun";
				_itemBox[3].enable = false;
			}
			if (_itemBox[4].enable == true)
			{
				_itemName = "Croissant";
				_itemBox[4].enable = false;
			}
		
		}

		if (shopNumber == 3 && shopIndex == 1) //스시집 싼스시
		{
			if (_itemBox[0].enable == true)
			{
				_itemName = "Egg";
				_itemBox[0].enable = false;
			}
			if (_itemBox[1].enable == true)
			{
				_itemName = "Octopus";
				_itemBox[1].enable = false;
			}
			if (_itemBox[2].enable == true)
			{
				_itemName = "Squid";
				_itemBox[2].enable = false;
			}
			if (_itemBox[3].enable == true)
			{
				_itemName = "CongerEel";
				_itemBox[3].enable = false;
			}
			if (_itemBox[4].enable == true)
			{
				_itemName = "Prawn";
				_itemBox[4].enable = false;
			}

		}

		if (shopNumber == 3 && shopIndex == 2) //스시집 비싼스시
		{
			if (_itemBox[0].enable == true)
			{
				_itemName = "Salmon";
				_itemBox[0].enable = false;
			}
			if (_itemBox[1].enable == true)
			{
				_itemName = "ArkShell";
				_itemBox[1].enable = false;
			}
			if (_itemBox[2].enable == true)
			{
				_itemName = "SeaUrchin";
				_itemBox[2].enable = false;
			}
			if (_itemBox[3].enable == true)
			{
				_itemName = "Halibut";
				_itemBox[3].enable = false;
			}
			if (_itemBox[4].enable == true)
			{
				_itemName = "SwordFish";
				_itemBox[4].enable = false;
			}

		}

		if (shopNumber == 3 && shopIndex == 3) //스시집 ROLL
		{
			if (_itemBox[0].enable == true)
			{
				_itemName = "SaladRoll";
				_itemBox[0].enable = false;
			}
			if (_itemBox[1].enable == true)
			{
				_itemName = "TunaRoll";
				_itemBox[1].enable = false;
			}
			if (_itemBox[2].enable == true)
			{
				_itemName = "ShrimpRoll";
				_itemBox[2].enable = false;
			}
			if (_itemBox[3].enable == true)
			{
				_itemName = "MixedRoll";
				_itemBox[3].enable = false;
			}
			

		}

		_item->init(_itemName);
		_price = _item->getPrice();
		if (_price <= _cMoney)//가격이 소지금 보다 작거나 같을 때
		{
			if (shopNumber == 2)
			{
				if (pl->getVItem().size() < 8)
				{
					pl->getVItem().push_back(_item);
					pl->moneyR(_price);
				}
				else SAFE_DEL(_item);
			}
			else
			{
				pl->setAllStatusValuesUsingShopItem(
					_item->getPlusPunch(),
					_item->getPlusKick(),
					_item->getPlusWeapon(),
					_item->getPlusPower(),
					_item->getPlusAgility(),
					_item->getPlusGuard(),
					_item->getPlusEndure(),
					_item->getPlusEnergy(),
					_item->getRecoveryHp(),
					_item->getPlusMaxHp());
				SAFE_DEL(_item);
				pl->moneyR(_price);
			}
			buy = false;
		}
		else if (_price > _cMoney) //가격이 소지금 보다 클 때
		{
			//소지금이 부족하다고 대사칠때 여기다가 넣으면될듯.
			SAFE_DEL(_item);
			buy = false;
		}
		apply = false;
	}
}

