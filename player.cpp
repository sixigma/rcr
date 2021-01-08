#include "stdafx.h"
#include "player.h"


HRESULT player::init()
{
	pos = { 10, 400 };
	return S_OK;

	_p_state = IDLE;

	_p_status.agility = 15;
	_p_status.endure = 15;
	_p_status.energy = 15;
	_p_status.guard = 15;
	_p_status.hp = 63;
	_p_status.kick = 15;
	_p_status.power = 15;
	_p_status.punch = 15;
	_p_status.weapon = 15;

}

void player::release()
{
}

void player::update()
{
	if (!_moveKeyDisabled && !_isInShop)
	{
		if (KEY->press('D'))
			pos.x += 12;
		else if (KEY->press('A'))
			pos.x -= 12;
		if (KEY->press('W'))
			pos.y -= 12;
		else if (KEY->press('S'))
			pos.y += 12;
		/*
		if(KEY->press('j'))
			//발차기 공격 & 줍기(&던지기)
		if(KEY->press('k'))
			//주먹 공격 & 줍기(&던지기)
		if(KEY->press('k') && KEY->press('j'))
			//점프

			//대쉬후 점프는 더높이 1번 맵에서 점프후 착지가 가능한 정도의 높이
		*/
	}
}

void player::render()
{
}
