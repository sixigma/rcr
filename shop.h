#pragma once
#include "map_.h"
#include "gameScene.h"
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
	
	bool apply;
	bool keyEnable;
	Flist _display;
	Flist _shopName;
	Flist _money;
	Flist _itemBox[itemmax];
	Flist _point[itemmax];
	Flist _yesNoBox[itemmax];
	Flist _yesNoPoint[itemmax];


	int tempnum;

	shop(){}
	~shop() override {}
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	void pointmove();
	void shopSetting();
};

