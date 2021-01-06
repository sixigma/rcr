#pragma once
#include "gameNode.h"


constexpr int VIEWPORT_UPDATE_OFFSET = 2;

class player;
class map_;
class map1;
class map2;
class gameScene : public gameNode
{
private:
	static player* _p;

	static map1* _map1;
	static map2* _map2;
	static map_* _currMap;

	static int prevMapIdx, mapIdx;

	bool _isInShop, _shouldBePaused;
public:
	gameScene();
	~gameScene() override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	static void setRoomIdx(int idx) { mapIdx = idx; }
	static int getPrevRoomIdx() { return prevMapIdx; }
	static void goToRoom(int idx);
	void updateViewport(int x, int y);
	void setViewport(int x, int y);
};

