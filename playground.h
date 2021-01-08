#pragma once
#include "gameNode.h"
#include "LineManager.h"

class playground : public gameNode
{
private:
	vector<int> keysToCheck;
	LineManager* l;

public:
	playground();
	~playground() override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

