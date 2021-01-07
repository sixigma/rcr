#pragma once
#include "map_.h"

class map4: public map_
{
	private:
	RECT unlandable;
	public:
	map4() {}
	~map4() override {}
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

