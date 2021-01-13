#pragma once
#include "gameNode.h"


constexpr int VIEWPORT_UPDATE_OFFSET = 2;

class player;
class map_;

class gameScene : public gameNode
{
private:
	static player* _p;

	static vector<map_*> _mapList;
	static map_* _currMap;

	static int _prevMapNum, _mapNum;

	static int _countForReEnablingKeyInput;

	int topBoxAdjX; // 상단 영역 이동 시 사용하는 변수
	int bottomBoxAdjX; // 하단 영역 이동 시 사용하는 변수
public:
	gameScene();
	~gameScene() override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	static void setMapNum(int num) { _mapNum = num; }
	static int getPrevMapNum() { return _prevMapNum; }
	static void goToMap(int num);
	void updateViewport(int x, int y);
	void setViewport(int x, int y);
};

