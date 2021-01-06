#pragma once
#include "character.h"
class player: public character
{
	public:
	player() {};
    ~player() override {};

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

