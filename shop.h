#pragma once
#include "map_.h"
#include "gameScene.h"
#define itemmax 20
struct Flist
{
	RECT rc;
	bool enable;
	int num;
};
class shop: public map_
{
private:
	int shopnumber;
public:
	
	bool keyenable;
	Flist _display;
	Flist _shopname;
	Flist _money;
	Flist _item[itemmax];
	Flist _point[itemmax];

	int tempnum;

	shop(){}
	~shop() override {}
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	void pointmove();
};

