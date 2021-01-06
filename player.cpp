#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	pos = { 10, 400 };
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	if (KEY->press('D'))
		pos.x += 12;
	else if (KEY->press('A'))
		pos.x -= 12;
	if (KEY->press('W'))
		pos.y -= 12;
	else if (KEY->press('S'))
		pos.y += 12;
}

void player::render()
{
}
