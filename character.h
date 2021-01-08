#pragma once
#include "gameNode.h"

enum STATE
{
	IDLE,			//평상시
	ATTACK,			//공격
	RUN, 			//달리기
	RUN_ATTACK,		//달리기 공격
	RUN_BACK,		//달리다 반대방향 보기
	JUMP, 			//점프
	JUMP_ATTACK,		//점프 공격
	RUN_JUMP,		//달리기 점프
	RUN_JUMP_ATTACK	//달리기 점프 공격
};

struct tagCharacterSetting
{
	POINT CH;	//캐릭터 렉트 그려질 포인트
	RECT ch;		//캐릭터 렉트
	RECT atk;	//캐릭터 공격렉트
	image* img;	//이미지
};

//펀치		- 펀치 계열 기술 공격력
//킥		- 발차기 계열 기술 공격력
//무기		- 무기 공격력
//힘		- 던지기 공격력
//민첩		- 전체적 동작 민첩성 증가
//방어	- 가드에 대한 영향, 높을수록 가드시 데미지 줄어듬
//맷집		- 피격시 데미지 줄임
//기력	- 체력이 다 떨어졌을 때 부활확률 증가, 기상속도, 피격모션 지속시간 감소 / 기력으로 부활시 기력 15를 소모해 15의 체력으로 부활
//체력(최대체력)		- 체력
struct tagStatus
{
	int punch;	//펀치	
	int kick;		//킥		
	int weapon;	//무기	
	int power;	//힘	    
	int agility;	//민첩	
	int guard;	//방어	
	int endure;	//맷집	
	int energy;	//기력	
	int hp;		//체력	
};

struct tagState
{
	bool run;		//달리기
	bool jump;		//점프
	bool W1, W2, W3, W4;	//무기
};

class character : public gameNode
{
protected:
	POINT pos;

public:
	character() {};
	~character() override {};

	POINT& getPos() { return pos; }

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

