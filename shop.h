#pragma once
#include "map_.h"
#include "gameScene.h"
#include "item.h"
#define itemmax 20
struct Flist
{
	RECT rc;
	bool use; // 사용여부
	bool enable;
	int num;
};
class shop: public map_
{
private:
	int shopNumber;
public:
	
	bool buy;
	bool apply;
	bool keyEnable;
	bool yesNoApply;
	bool yesNoEnable;
	int _price;
	int _cMoney;

	string tempStr;
	string _itemName;
	Flist _display;
	Flist _shopName;
	Flist _money;
	Flist _itemBox[itemmax];
	Flist _point[itemmax];
	Flist _yesNoBox[2];
	Flist _yesNoPoint[2];

	item* _itemL;

	int max;
	int tempnum;
	int shopIndex;

	shop(){}
	~shop() override {}
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	void pointmove();
	void shopSetting();
	void shopbuy();
};

