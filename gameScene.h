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

	static bool _isInShop, _shouldBePaused;
	static int _countForReEnablingKeyInput;
public:
	gameScene();
	~gameScene() override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	static bool getIsInShop() { return _isInShop; }
	static void setIsInShop(bool b) { _isInShop = b; }
	static void setMapNum(int num) { _mapNum = num; }
	static int getPrevMapNum() { return _prevMapNum; }
	static void goToMap(int num);
	void updateViewport(int x, int y);
	void setViewport(int x, int y);
};

