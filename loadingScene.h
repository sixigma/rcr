#pragma once
#include "gameNode.h"

constexpr int MAX_SLEEP_CALLS = 100;

class progressBar;

class loadingScene: public gameNode
{
private:
	progressBar* _loadingBar;
	image* _background;
	HANDLE hThread;

public:
	loadingScene();
	~loadingScene() override;

	int _currentCount;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	static unsigned CALLBACK threadFunc(LPVOID params);
};

