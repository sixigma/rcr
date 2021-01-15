#include "stdafx.h"
#include "player.h"
#include "item.h"

HRESULT player::init()
{
	_count = 0;

	deltaX = 0;

	dash_cnt = 0;

	playerSetStatus();
	playerImgFind();
	playerSetAni();


	_p_character_set.ch = MakeRct(pos.x - 34, pos.y - 128, 68, 128);

	_p_character_set.img = _walk;
	_p_character_set.ani = _R_walk;


	return S_OK;
}

void player::release()
{
	delete _R_walk;
	delete _L_walk;
	delete _L_run;
	delete _R_run;
	delete _R_punch;
	delete _L_punch;
	delete _R_kick;
	delete _L_kick;
	delete _R_jump;
	delete _L_jump;
}

void player::update()
{
	if (!_moveKeyDisabled && !_isInShop)	// 씬 전환 직후가 아닐 때, 상점이 아닐 때만 조작 가능
	{
		if (_p_state != RUN && _p_state != JUMP)
		{
			if (KEY->press('D'))
			{
				if (left)
				{
					left = false;
					dash_cnt = 0;
				}
				deltaX = 6;
				_p_state = WALK;
			}

			if (KEY->press('A') && _p_state != JUMP)
			{
				if (!left)
				{
					left = true;
					dash_cnt = 0;
				}
				deltaX = -6;
				_p_state = WALK;
			}

		}

		if (dash_cnt == 0 && (KEY->down('D') || KEY->down('A')))
			++dash_cnt;

		else if (dash_cnt > 0 && dash_cnt < 40 && _p_state != JUMP)
		{
			if (KEY->down('A') && left && _p_state != RUN)
			{
				_p_state = RUN;
				_isRun = true;
			}
			if (KEY->down('D') && !left && _p_state != RUN)
			{
				_p_state = RUN;
				_isRun = true;
			}
			++dash_cnt;
		}

		else if (_p_state == RUN)
		{
			if (!left && (KEY->down('A')) || (KEY->down('J')) || (KEY->down('K')))
			{
				dash_cnt = 0;
				_p_state = IDLE;
			}

			else if (left && (KEY->down('D')) || (KEY->down('J')) || (KEY->down('K')))
			{
				dash_cnt = 0;
				_p_state = IDLE;
			}
		}

		if (_p_state == RUN && !left) deltaX = 12;
		else if (_p_state == RUN && left) deltaX = -12;

		deltaX *= 0.9;
		if (abs(deltaX) < 4) deltaX = 0;
		if (deltaX == 0 && _p_state != JUMP)
		{
			_p_state = IDLE;
		}
		pos.x += deltaX;
		//-------------------------------------------------------------------------
		//스위치 IDLE로 변경
		if (KEY->up('D') && _p_state == WALK) { _p_state = IDLE; }
		if (KEY->up('A') && _p_state == WALK) { _p_state = IDLE; }

		if (KEY->press('W') && _p_state != JUMP)
		{
			if (pos.z == 0) { pos.y -= 12; }
			else if (KEY->up('W') && _p_state == WALK)_p_state = IDLE;
			if (_isRun)_p_state = RUN;
			else if (!_isRun)_p_state = WALK;
		}
		else if (KEY->press('S') && _p_state != JUMP)
		{
			if (_isRun)_p_state = RUN;
			else if (!_isRun)_p_state = WALK;
			if (pos.z == 0) pos.y += 12;
			else if (pos.z != 0 && _p_state != JUMP)
			{
				_p_tagState.jump = true;
				_p_state = JUMP;
				_JP = 2.f;
				_G = 0.2f;
				pos.y += 10;
			}
			else if (KEY->up('S') && _p_state == WALK)_p_state = IDLE;
		}


			//점프
		//if (KEY->press('K') && KEY->press('J') && _p_state != JUMP)
		if (KEY->down(VK_SPACE) && _p_state != JUMP)
		{
			_p_tagState.jump = true;
			_p_state = JUMP;
		}
			//대쉬후 점프는 더높이 1번 맵에서 점프후 착지가 가능한 정도의 높이

		if (KEY->press('J'))
		{
			if (_p_state == IDLE || _p_state == RUN || _p_state == JUMP)
			{
				_p_state = PUNCH;

				if (left)
				{
					if (_L_punch->getCurrPlaylistIdx() == 2)
					{
						_attack_rc = MakeRct(pos.x - 25 - 40, pos.y - 95, 50, 20);
					}
				}

				else if (!left)
				{
					if (_R_punch->getCurrPlaylistIdx() == 2)
					{
						_attack_rc = MakeRct(pos.x + 25, pos.y - 95, 50, 20);
					}
				}
			}
		}

		if (KEY->press('K'))

			if (_p_state == IDLE || _p_state == RUN || _p_state == JUMP)
			{
				_p_state = KICK;
				{
					if (left)
					{
						if (_L_kick->getCurrPlaylistIdx() == 2)
						{
							_attack_rc = MakeRct(pos.x - 45 - 55, pos.y - 75, 55, 30);
						}
					}

					else if (!left)
					{
						if (_R_kick->getCurrPlaylistIdx() == 2)
						{
							_attack_rc = MakeRct(pos.x + 45, pos.y - 75, 55, 30);
						}
					}
				}
			}
		_p_character_set.ch = MakeRct(pos.x - 33, pos.y - 130 + pos.z, 66, 130);
		_p_character_set.ani->frameUpdate(TIME->getElapsedTime() * 10);
		jumpSwitch();
		_count++;
		frameUp();
		if (_count > 400) _count = 0;

	}
}

void player::render()
{
	//x중앙, y하단
	if (KEY->isToggledOn(VK_TAB)) { DrawRct(getMemDC(), _p_character_set.ch); }
	//이미지 -> 애니렌더(hdc , x씌울곳, y씌울곳, 애니메이션)을 입력합니다
	if (_isInShop == false)
	{
		_p_character_set.img->aniRender(getMemDC(), pos.x - 316 / 2, pos.y - 408 / 2 + pos.z, _p_character_set.ani);

	}
	DrawRct(getMemDC(), _attack_rc);

}

void player::playerSetStatus()
{
	_p_state = IDLE;

	_p_status.agility = 15;
	_p_status.endure = 15;
	_p_status.energy = 15;
	_p_status.guard = 15;
	_p_status.hp = 63;
	_p_status.maxHP = 63;
	_p_status.kick = 15;
	_p_status.power = 15;
	_p_status.punch = 15;
	_p_status.weapon = 15;
	_p_status.money = 2000;

	if (_playerChName != "") setPlayerChName(_playerChName);
	else
	{
		_playerChName = "ALEX";
		setPlayerChName(_playerChName);
	}

}

void player::frameUp()
{
	if (_count % 2 == 0)
	{
		switch (_p_state)
		{
		case IDLE:
			if (left) { _p_character_set.img = _walk; _p_character_set.ani = _L_walk; }
			else if (!left) { _p_character_set.img = _walk; _p_character_set.ani = _R_walk; }
			_p_character_set.ani->setCurrPlaylistIdx(1);
			_p_character_set.ani->pause();
			break;
		case WALK:
			if (left) { _p_character_set.img = _walk; _p_character_set.ani = _L_walk; }
			else if (!left) { _p_character_set.img = _walk; _p_character_set.ani = _R_walk; }
			_p_character_set.ani->resume();
			break;
		case RUN:
			if (left) { _p_character_set.img = _run; _p_character_set.ani = _L_run; }
			else if (!left) { _p_character_set.img = _run; _p_character_set.ani = _R_run; }
			_p_character_set.ani->resume();
			break;
		case PUNCH:
			if (left) { _p_character_set.img = _punch; _p_character_set.ani = _L_punch; }
			else if (!left) { _p_character_set.img = _punch; _p_character_set.ani = _R_punch; }
			_p_character_set.ani->resume();
			break;
		case KICK:
			if (left) { _p_character_set.img = _kick; _p_character_set.ani = _L_kick; }
			else if (!left) { _p_character_set.img = _kick; _p_character_set.ani = _R_kick; }
			_p_character_set.ani->resume();
			break;
		case JUMP:
			if (left) { _p_character_set.img = _jump; _p_character_set.ani = _L_jump; }
			else if (!left) { _p_character_set.img = _jump; _p_character_set.ani = _R_jump; }
			_p_character_set.ani->setCurrPlaylistIdx(0);
			break;
		case HIT:
			break;
		case KO:
			break;
		default:
			break;
		}
		_count = 0;
	}

}

void player::jumpSwitch()
{
	if(_p_state!=JUMP){ _p_tagState.jump = false; }
	
	switch (_p_state)
	{
	case IDLE:
		_MV = 0;
		_JP = 10.f;
		_G = 0.5f;
		_isRun = false;
	break;

	case WALK:
		if (_WD)
		{
			_p_tagState.jump = true;
			_p_state = JUMP;
			_JP = 2.f;
			_G = 0.3f;
			if (left && KEY->press('A'))_MV = -5;
			else if (!left && KEY->press('D'))_MV = 5;
		}
		else
		{
			_JP = 10.f;
			_G = 0.5f;
			if (left && KEY->press('A'))  _MV = -6; 
			else if (!left && KEY->press('D'))_MV = 6;
		}
	break;

	case RUN:
		if (_WD)
		{
			_p_tagState.jump = true;
			_p_state = JUMP;
			_JP = 3.f;
			_G = 0.3f;
			if (left)_MV = -6;
			else if (!left)_MV = 6;
		}
		else
		{
			_JP = 15.f;
			_G = 0.5f;
			if (left)_MV = -12;
			else if (!left)_MV = 12;
		}

	break;

	case JUMP:
		_deltaZ -= _JP;
		_JP -= _G;
		pos.z = _deltaZ;
		deltaX = _MV;
		if (pos.z + pos.y > pos.y)
		{
			pos.z = _deltaZ = _JP = _G = 0;
			_p_state = IDLE;
			_p_tagState.jump = false;
			_WD = false;
		}
		break;
	}

}

bool player::jumpDown()
{
	if (_JP < _G)return true;
	else return false;
}

void player::playerImgFind()
{
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
}

void player::playerSetAni()
{

	int _R_walkArr[] = { 0,1,2,1 };

	_R_walk = new animation;
	_R_walk->init(_walk->getWidth(),
		_walk->getHeight(),
		_walk->getFrameWidth(),
		_walk->getFrameHeight());
	_R_walk->setPlaylist(_R_walkArr, 4, true);
	_R_walk->setFPS(1);

	int _L_walkArr[] = { 5,4,3,4 };

	_L_walk = new animation;
	_L_walk->init(_walk->getWidth(),
		_walk->getHeight(),
		_walk->getFrameWidth(),
		_walk->getFrameHeight());
	_L_walk->setPlaylist(_L_walkArr, 4, true);
	_L_walk->setFPS(1);

	int _R_runArr[] = { 0,1 };

	_R_run = new animation;
	_R_run->init(_run->getWidth(),
		_run->getHeight(),
		_run->getFrameWidth(),
		_run->getFrameHeight());
	_R_run->setPlaylist(_R_runArr, 2, true);
	_R_run->setFPS(1);

	int _L_runArr[] = { 3,2 };

	_L_run = new animation;
	_L_run->init(_run->getWidth(),
		_run->getHeight(),
		_run->getFrameWidth(),
		_run->getFrameHeight());
	_L_run->setPlaylist(_L_runArr, 2, true);
	_L_run->setFPS(1);

	int _R_punchArr[] = { 0,1,2 };

	_R_punch = new animation;
	_R_punch->init(_punch->getWidth(),
		_punch->getHeight(),
		_punch->getFrameWidth(),
		_punch->getFrameHeight());
	_R_punch->setPlaylist(_R_punchArr, 3, true);
	_R_punch->setFPS(1);

	int _L_punchArr[] = { 5,4,3 };


	_L_punch = new animation;
	_L_punch->init(_punch->getWidth(),
		_punch->getHeight(),
		_punch->getFrameWidth(),
		_punch->getFrameHeight());
	_L_punch->setPlaylist(_L_punchArr, 3, true);
	_L_punch->setFPS(1);

	int _R_kickArr[] = { 0,1,2 };

	_R_kick = new animation;
	_R_kick->init(_kick->getWidth(),
		_kick->getHeight(),
		_kick->getFrameWidth(),
		_kick->getFrameHeight());
	_R_kick->setPlaylist(_R_kickArr, 3, true);
	_R_kick->setFPS(1);

	int _L_kickArr[] = { 5,4,3 };


	_L_kick = new animation;
	_L_kick->init(_kick->getWidth(),
		_kick->getHeight(),
		_kick->getFrameWidth(),
		_kick->getFrameHeight());
	_L_kick->setPlaylist(_L_kickArr, 3, true);
	_L_kick->setFPS(1);

	int _R_jumpArr[] = {0,1};

	_R_jump = new animation;
	_R_jump->init(_jump->getWidth(),
		_jump->getHeight(),
		_jump->getFrameWidth(),
		_jump->getFrameHeight());
	_R_jump->setPlaylist(_R_jumpArr, 2, false);
	_R_jump->setFPS(1);

	int _L_jumpArr[] = { 3,2 };

	_L_jump = new animation;
	_L_jump->init(_jump->getWidth(),
		_jump->getHeight(),
		_jump->getFrameWidth(),
		_jump->getFrameHeight());
	_L_jump->setPlaylist(_L_jumpArr, 2, false);
	_L_jump->setFPS(1);
}
