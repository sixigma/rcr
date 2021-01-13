#include "stdafx.h"
#include "shop.h"
#include "player.h"

HRESULT shop::init()
{
	setMapNum(6);
	int shopnumber = 0;
	currPlPos = &pl->getPos();
	*currPlPos = { _totRegion.right - 40, 592,0 };
	prevPlPos = *currPlPos;
	keyenable = false;
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
		_item[i].enable = false;
		_item[i].num = tempnum;
		tempnum++;
	}

	//이미지 디스플레이
	_display.rc = MakeRct(145, 220, 265, 265);

	//상점이름
	_shopname.rc = MakeRct(145, 530, 265, 170);

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
	_item[0].rc = MakeRct(530, 236, 500, 50);
	_item[1].rc = MakeRct(530, 296, 500, 50);
	_item[2].rc = MakeRct(530, 356, 500, 50);
	_item[3].rc = MakeRct(530, 416, 500, 50);
	_item[4].rc = MakeRct(530, 476, 500, 50);
	_item[5].rc = MakeRct(530, 536, 500, 50);

	gameScene::setViewport(0, 96);
	return S_OK;
}

void shop::release()
{
}

void shop::update()
{
	shopnumber = getShopNum();
	pointmove();
	if (shopnumber == 1)//RISE & SHINE CAFE
	{

	}
	if (shopnumber == 2)
	{

	}
	if (shopnumber == 3)
	{

	}
	if (shopnumber == 4)
	{

	}
}

void shop::render()
{
	IMG->find("상점맵")->render(getMemDC(), _newOrg.x, 96, 0, 0, WINW, 640);
	for (int i = 0; i < 6; i++)
	{
		if (_point[i].enable)
		{
			IMG->find("포인터")->render(getMemDC(), _point[i].rc.left, _point[i].rc.top, 0, 0, 40, 40);
		}
		if (_item[i].enable)
		{
			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
			HPEN hOPen = (HPEN)SelectObject(getMemDC(), hPen);
			HBRUSH hOBrush = (HBRUSH)SelectObject(getMemDC(), hBrush);
			DrawRct(getMemDC(), _item[i].rc);
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
			DrawRct(getMemDC(), _item[i].rc);
			DrawRct(getMemDC(), _point[i].rc);
			DrawRct(getMemDC(), _display.rc);
			DrawRct(getMemDC(), _shopname.rc);
		}
		DrawRct(getMemDC(), _money.rc);
		DeleteObject(SelectObject(getMemDC(), hOPen));
		DeleteObject(SelectObject(getMemDC(), hOBrush));
	}
}

void shop::pointmove()
{
	int temp = 0;
	for (int i = 0; i < 6; i++)
	{
		if (_point[i].enable == true)
		{
			if(KEY->down('W') && (_point[0].enable == false) && (keyenable == false))
			{
				_point[i].enable = false;
				_point[i - 1].enable = true;
				break;
			}

			if (KEY->down('S') && (_point[5].enable == false) && (keyenable == false))
			{
				_point[i].enable = false;
				_point[i + 1].enable = true;
				break;
			}

			if (KEY->down('K') && (_point[i].enable))
			{
				temp = _point[i].num;
				if (temp == _item[i].num)
				{
					_item[i].enable = true;
				}
				keyenable = true;

			}
			if (KEY->down('J'))
			{
				if (keyenable == false)gameScene::goToMap(3);
				else if (keyenable == true)
				{
					_item[i].enable = false;
					keyenable = false;
				}
			}
		}
	}
}
