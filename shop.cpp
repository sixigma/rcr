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


	setMapNum(6);
	shopNumber = 0;
	currPlPos = &pl->getPos();
	*currPlPos = { _totRegion.right - 40, 592,0 };
	prevPlPos = *currPlPos;
	keyEnable = false;
	apply = false;
	tempnum = 0;
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

	gameScene::setViewport(0, 96);
	return S_OK;
}

void shop::release()
{
}

void shop::update()
{
	shopNumber = getShopNum();
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
	int max = 0;

	switch (shopNumber) // 상점번호에따라
	{
	case 1:
		max = 6;
	break;

	case 2:
		max = 6;
	break;

	case 3:
		max = 4;
	break;

	case 4:
		max = 4;
	break;

	}

	for (int i = 0; i < 6; i++)
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

			if (KEY->down('K') && (_point[i].enable))
			{
				temp = _point[i].num;
				if (temp == _itemBox[i].num)
				{
					_itemBox[i].enable = true;
				}
				keyEnable = true;

			}
			if (KEY->down('J'))
			{
				if (keyEnable == false)
				{
					apply = false;
					gameScene::goToMap(3);
				}
				else if (keyEnable == true)
				{
					_itemBox[i].enable = false;
					keyEnable = false;
				}
			}
		}
	}
}

void shop::shopSetting()
{
	if (shopNumber == 1)//RISE & SHINE CAFE
	{
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
		L->CreateLine(MakePt(_shopName.rc.left - 70, _shopName.rc.top + 10), "Metro%Bakery", "n", false);


		L->CreateLine(MakePt(_itemBox[0].rc.left - 70, _itemBox[0].rc.top + 10), "Donut        .80", "n", false);
		L->CreateLine(MakePt(_itemBox[1].rc.left - 70, _itemBox[1].rc.top + 10), "Muffin       .95", "n", false);
		L->CreateLine(MakePt(_itemBox[2].rc.left - 70, _itemBox[2].rc.top + 10), "Bagel        .95", "n", false);
		L->CreateLine(MakePt(_itemBox[3].rc.left - 70, _itemBox[3].rc.top + 10), "Honey Bun   3.30", "n", false);
		L->CreateLine(MakePt(_itemBox[4].rc.left - 70, _itemBox[4].rc.top + 10), "Croissant   4.10", "n", false);
		L->CreateLine(MakePt(_itemBox[5].rc.left - 70, _itemBox[5].rc.top + 10), "Nothing", "n", false);
	}
	if (shopNumber == 3)//Sushi
	{
		L->CreateLine(MakePt(_shopName.rc.left - 70, _shopName.rc.top + 10), "Sushi%Bar", "n", false);


		L->CreateLine(MakePt(_itemBox[0].rc.left - 70, _itemBox[0].rc.top + 10), "Cheaper Sushi", "n", false);
		L->CreateLine(MakePt(_itemBox[1].rc.left - 70, _itemBox[1].rc.top + 10), "Expensive Sushi", "n", false);
		L->CreateLine(MakePt(_itemBox[2].rc.left - 70, _itemBox[2].rc.top + 10), "Rolls", "n", false);
		L->CreateLine(MakePt(_itemBox[3].rc.left - 70, _itemBox[3].rc.top + 10), "Nothing", "n", false);

	}
	if (shopNumber == 4)//bookstore
	{
		L->CreateLine(MakePt(_shopName.rc.left - 70, _shopName.rc.top + 10), "Grotto%Book%Store", "n", false);

		L->CreateLine(MakePt(_itemBox[0].rc.left - 70, _itemBox[0].rc.top + 10), "MAHA PUNCH 26.95", "n", false);
		L->CreateLine(MakePt(_itemBox[1].rc.left - 70, _itemBox[1].rc.top + 10), "MAHA KICK  26.95", "n", false);
		L->CreateLine(MakePt(_itemBox[2].rc.left - 70, _itemBox[2].rc.top + 10), "SCREW BOMER26.95", "n", false);
		L->CreateLine(MakePt(_itemBox[3].rc.left - 70, _itemBox[3].rc.top + 10), "Nothing", "n", false);

	}
	apply = true;

}
