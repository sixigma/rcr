#include "stdafx.h"
#include "loadingScene.h"
#include "gameScene.h"
#include "progressBar.h"
#include <process.h> // _beginthreadex


loadingScene::loadingScene(): _background(nullptr), _loadingBar(nullptr), _currentCount(0) {}

loadingScene::~loadingScene() {}

HRESULT loadingScene::init()
{
	_loadingBar = new progressBar;
	_loadingBar->init(0, WINH - 30, WINW, 30);
	_loadingBar->setGauge(0, 0);

	hThread = (HANDLE)_beginthreadex(NULL, 0, threadFunc, this, CREATE_SUSPENDED, NULL);
	if (!hThread)
	{
		return E_FAIL;
	}
	ResumeThread(hThread);

	return S_OK;
}

void loadingScene::release()
{
	SAFE_DEL(_loadingBar);
}

void loadingScene::update()
{
	_loadingBar->update();
	_loadingBar->setGauge(static_cast<float>(_currentCount), MAX_SLEEP_CALLS);
}

void loadingScene::render()
{
	_loadingBar->render();

	// ·Îµù ¿Ï·á ½Ã
	if (_currentCount == MAX_SLEEP_CALLS)
	{
		CloseHandle(hThread);
		SC->changeScene("°ÔÀÓ Àå¸é");
	}
}

unsigned CALLBACK loadingScene::threadFunc(LPVOID params)
{
	loadingScene* loadingParams = (loadingScene*)params;

	SC->addScene("°ÔÀÓ Àå¸é", new gameScene);
	IMG->add("¸Ê 1", "images/maps/1.bmp", 3036, 640, false, RGB(255, 0, 255));
	IMG->add("¸Ê 2", "images/maps/2.bmp", 2012, 640, false, RGB(255, 0, 255));
	IMG->add("¸Ê 3", "images/maps/3.bmp", 2012, 640, false, RGB(255, 0, 255));
	IMG->add("¸Ê 4", "images/maps/4.bmp", 3040, 640, false, RGB(255, 0, 255));
	IMG->add("¸Ê 4-2", "images/maps/4-2.bmp", 1884, 640, false, RGB(255, 0, 255));
	IMG->add("¸Ê 5", "images/maps/5.bmp", 2012, 640, false, RGB(255, 0, 255));

	while (loadingParams->_currentCount != MAX_SLEEP_CALLS)
	{
		Sleep(1);
		++loadingParams->_currentCount;
	}
	return 0;
}
