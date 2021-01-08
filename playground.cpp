#include "stdafx.h"
#include "playground.h"
#include "loadingScene.h"

playground::playground()
{
}


playground::~playground()
{
}

HRESULT playground::init()
{
	gameNode::init(true);
	keysToCheck = { VK_SPACE, VK_ESCAPE, VK_RETURN, VK_CAPITAL, VK_F1, VK_F2, VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP, VK_LBUTTON, VK_RBUTTON, 'Q', 'E', 'W', 'A', 'S', 'D', 'J', 'K' }; // 입력을 확인할 키 나열(토글 키 제외)
	SC->addScene("로딩 장면", new loadingScene);

	_moveKeyDisabled = FALSE;

	SC->changeScene("로딩 장면");


	return S_OK;
}


void playground::release()
{
	gameNode::release();


}

void playground::update()
{
	KEY->updateKeyState(keysToCheck);
	gameNode::update();
	SC->update();
}


void playground::render()
{
	//PatBlt(getMemDC(), 0, 0, WINW, WINH, BLACKNESS);

	SC->render();
	TIME->render(getMemDC());

	_backBuffer->render(getHDC(), _currOrg.x, _currOrg.y, 0, 0, WINW, WINH);
}

