#pragma once
#include "gameNode.h"

class progressBar: public gameNode
{
private:
	RECT _rctProgress;
	float _x, _y, _width;

	image* _progressBarFront;
	image* _progressBarBack;

public:
	progressBar() {};
	~progressBar() override {};

	HRESULT init(int x, int y, int width, int height);
	void release() override;
	void update() override;
	void render() override;

	void setGauge(float currentGauge, float maxGauge);

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
};

