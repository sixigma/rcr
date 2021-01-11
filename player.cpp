#include "stdafx.h"
#include "player.h"


HRESULT player::init()
{
	pos = { 10, 400 };
	

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

	_count = 0;

	_walk = IMG->find("p-걷기");
	_run = IMG->find("p-달리기");
	_punch = IMG->find("p-펀치");
	_kick = IMG->find("p-킥");
	_uppercut = IMG->find("p-어퍼컷");
	_highkick = IMG->find("p-하이킥");
	_run_punch = IMG->find("p-달리기펀치");
	_jump = IMG->find("p-점프");
	_jumpkick = IMG->find("p-점프킥");
	_defend = IMG->find("p-방어");
	_beatup = IMG->find("p-피격");
	_ko = IMG->find("p-KO");
	_stick_pipe = IMG->find("p-스틱");
	_chain = IMG->find("p-체인");
	_knuckles = IMG->find("p-너클");
	_rock = IMG->find("p-돌");
	_lift_trashcan = IMG->find("p-쓰레기");
	_lift_create = IMG->find("p-박스");
	_lift_tire = IMG->find("p-타이어");
	_lift_human = IMG->find("p-사람");
	_throw_stick_pipe = IMG->find("p-스틱던지기");
	_throw_chain = IMG->find("p-체인던지기");
	_throw_knuckles = IMG->find("p-너클던지기");
	_throw_rock = IMG->find("p-돌던지기");
	_throw_trashcan = IMG->find("p-쓰레기던지기");
	_throw_crate = IMG->find("p-박스던지기");
	_throw_tire = IMG->find("p-타이어던지기");
	_throw_human = IMG->find("p-사람던지기");
	_roll = IMG->find("p-구르기");
	_shop_stand_order = IMG->find("p-상점주문1");
	_shop_stand_eat = IMG->find("p-상점취식1");
	_shop_sit_order = IMG->find("p-상점주문2");
	_shop_sit_eat = IMG->find("p-상점취식2");


	int _R_walkArr[] = { 0,1,2 };

	_R_walk = new animation;
	_R_walk->init(_walk->getWidth(),
				_walk->getHeight(),
				_walk->getFrameWidth(),
				_walk->getFrameHeight());
	_R_walk->setPlaylist(_R_walkArr, 3, true);
	_R_walk->setFPS(1);

	int _L_walkArr[] = { 3,4,5 };
	
	_L_walk = new animation;
	_L_walk->init(_walk->getWidth(),
		_walk->getHeight(),
		_walk->getFrameWidth(),
		_walk->getFrameHeight());
	_L_walk->setPlaylist(_L_walkArr, 3, true);
	_L_walk->setFPS(1);

	_p_character_set.ch = MakeRct(pos.x - 34, pos.y - 128, 68, 128);

	_p_character_set.img = _walk;
	_p_character_set.ani = _R_walk;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	if (!_moveKeyDisabled && !_isInShop)
	{
		if (KEY->press('D'))
		{
			_p_state = WALK;
			pos.x += 6;
			if (left)left = false;
		}

		if(KEY->up('D'))
		{
			_p_state = IDLE;
		}

		else if (KEY->press('A'))
		{
			pos.x -= 6;
			if (!left)left = true;
			_p_state = WALK;
		}

		if (KEY->up('A'))
		{
			_p_state = IDLE;
		}


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

		_p_character_set.ch = MakeRct(pos.x - 33, pos.y - 130, 66, 130);
		_p_character_set.ani->frameUpdate(TIME->getElapsedTime() * 10);
		_count++;
		if (_count > 400) _count = 0;
		frameUp();


	}
}

void player::render()
{
	//x중앙, y하단
	if (KEY->isToggledOn(VK_TAB)) { DrawRct(getMemDC(), _p_character_set.ch); }

	//이미지 -> 애니렌더(hdc , x씌울곳, y씌울곳, 애니메이션)을 입력합니다
	_p_character_set.img->aniRender(getMemDC(), pos.x - 316/2, pos.y - 408/2, _p_character_set.ani);

}

void player::frameUp()
{
	if (_count % 2 == 0)
	{
		switch (_p_state)
		{
		case IDLE:
			if (left)_p_character_set.ani = _L_walk;
			else if (!left)_p_character_set.ani = _R_walk;
			_p_character_set.ani->stop();
			break;
		case WALK:
			if (left)_p_character_set.ani = _L_walk;
			else if (!left)_p_character_set.ani = _R_walk;
			_p_character_set.ani->resume();
			break;
		default:
			break;
		}
	}
}
