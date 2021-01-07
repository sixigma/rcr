#pragma once
#include "map_.h"

class map1: public map_
{
	private:
	RECT unlandable;
	public:
	map1() {}
	~map1() override {}
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

