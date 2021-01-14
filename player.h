#pragma once
#include "character.h"

class item;
class player: public character
{
	STATE _p_state;
	tagCharacterSetting _p_character_set;
	tagStatus _p_status;
	tagState _p_tagState;

	protected:
		image* _run, *_walk, *_punch, *_kick, *_uppercut, *_highkick,
			*_run_punch, *_jump, *_jumpkick, *_defend, *_beatup, *_ko,
			*_stick_pipe, *_chain, *_knuckles, *_rock, *_lift_trashcan,
			*_lift_create, *_lift_tire, *_lift_human, *_throw_stick_pipe,
			*_throw_chain, *_throw_knuckles, *_throw_rock, *_throw_trashcan,
			*_throw_crate, *_throw_tire, *_throw_human, *_roll, *_shop_stand_order,
			*_shop_stand_eat, *_shop_sit_order, *_shop_sit_eat;

		animation* _L_run, *_L_walk, *_L_punch, *_L_kick, *_L_uppercut, *_L_highkick,
			*_L_run_punch, *_L_jump, *_L_jumpkick, *_L_defend, *_L_beatup, *_L_ko,
			*_L_stick_pipe, *_L_chain, *_L_knuckles, *_L_rock, *_L_lift_trashcan,
			*_L_lift_create, *_L_lift_tire, *_L_lift_human, *_L_throw_stick_pipe,
			*_L_throw_chain, *_L_throw_knuckles, *_L_throw_rock, *_L_throw_trashcan,
			*_L_throw_crate, *_L_throw_tire, *_L_throw_human, *_L_roll, *_L_shop_stand_order,
			*_L_shop_stand_eat, *_L_shop_sit_order, *_L_shop_sit_eat;

		animation* _R_run, *_R_walk, *_R_punch, *_R_kick, *_R_uppercut, *_R_highkick,
			*_R_run_punch, *_R_jump, *_R_jumpkick, *_R_defend, *_R_beatup, *_R_ko,
			*_R_stick_pipe, *_R_chain, *_R_knuckles, *_R_rock, *_R_lift_trashcan,
			*_R_lift_create, *_R_lift_tire, *_R_lift_human, *_R_throw_stick_pipe,
			*_R_throw_chain, *_R_throw_knuckles, *_R_throw_rock, *_R_throw_trashcan,
			*_R_throw_crate, *_R_throw_tire, *_R_throw_human, _R_roll;

		RECT _attack_rc; // 공격용 렉트
		int dash_cnt; // 대쉬 카운트
		int _count; // 프레임 카운트
		int _FrameI; // 프레임 인덱스
		float deltaX; //미끄러짐 효과를 위한 player 위치 변수

		bool left; // 애니메이션 방향용 bool값
		bool _isJump; // 점프용 bool 값
		bool _isRun; // 대쉬용 bool 값

		vector<item*> _vItem;

	public:
	player() {};
    ~player() override {};

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void hitDamage(int damage) { _p_status.hp -= damage; }			//데미지
	void recoveryHp(int hpUp) { _p_status.hp += hpUp; }				//체력 회복
	void maxHpUp(int MaxHpUp) { _p_status.maxHP += MaxHpUp; }		//최대체력 증가
	void recoveryEng(int engUp) { _p_status.energy += engUp; }		//기력 회복
	void endureUp(int endUp) { _p_status.endure += endUp; }			//맷집 상승
	void guardUp(int defUp) { _p_status.guard += defUp; }			//방어력 상승
	void agilityUp(int agiUp) { _p_status.agility += agiUp; }		//민첩 상승
	void powerUp(int powUp) { _p_status.power += powUp; }			//힘 상승
	void weaponUp(int wepUp) { _p_status.weapon += wepUp; }			//무기 공격력 상승
	void kickUp(int kAtkUp) { _p_status.kick += kAtkUp; }			//발차기 공격력 상승
	void punchUp(int pAtkUp) { _p_status.punch += pAtkUp; }			//주먹 공격력 상승

	int currentHP() { return _p_status.hp; }
	int currentMaxHP() { return _p_status.maxHP; }
	int currentEnergy() { return _p_status.energy; }
	int currentPunch() { return _p_status.punch; }
	int currentkick() { return _p_status.kick; }
	int currentWeapon() { return _p_status.weapon; }
	int currentPower() { return _p_status.power; }
	int currentAgility() { return _p_status.agility; }
	int currentGuard() { return _p_status.guard; }
	int currentEndure() { return _p_status.endure; }

	void playerSetStatus();		//플레이어 스탯 초기값 설정 함수
	void playerImgFind();		//플레이어 이미지 관련 함수
	void playerSetAni();		//플레이어 애니메이션 등록 함수
	void frameUp();				//애니메이션 재생 함수

	vector<item*> &getVItem() { return _vItem; }
};

