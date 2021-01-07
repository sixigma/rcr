#pragma once
#include "map_.h"

class map2: public map_
{
	public:
	map2() {}
	~map2() override {}
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};