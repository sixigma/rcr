#pragma once
#include "character.h"

class player: public character
{
	STATE _p_state;
	tagCharacterSetting _p_character_set;
	tagStatus _p_status;
	tagState _p_tagState;

	public:
	player() {};
    ~player() override {};

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

