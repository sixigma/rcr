#pragma once
#include "gameScene.h"

class player;
class map_: public gameScene
{
	protected:
	player* pl;

	public:
	map_() {}
	~map_() override {}
	void setLinkTo(player*& p) { pl = p; }

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

