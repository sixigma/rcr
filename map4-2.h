#pragma once
#include "map_.h"

class map4_2: public map_
{
	private:
	vector<RECT> unlandable;
	public:
	map4_2() {}
	~map4_2() override {}
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

