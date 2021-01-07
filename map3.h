#pragma once
#include "map_.h"

class map3: public map_
{
	public:
	map3() {}
	~map3() override {}
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

