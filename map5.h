#pragma once
#include "map_.h"

class map5: public map_
{
	private:
	RECT unlandable;
	public:
	map5() {}
	~map5() override {}
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

