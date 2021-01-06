#pragma once
#include "gameNode.h"

class character: public gameNode
{
	protected:
	POINT pos;

	public:
	character() {};
	~character() override {};

	POINT& getPos() { return pos; }

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

