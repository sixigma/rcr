#pragma once
#include "character.h"
class enemy :
    public character
{
	public:
	enemy();
    ~enemy() override = 0;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

