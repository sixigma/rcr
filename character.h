#pragma once
#include "gameNode.h"

enum STATE
{
	IDLE,			//평상시
	WALK,
	RUN, 			//달리기
	PUNCH,			//펀치(run상태일 때 run+punch가 될 수 있다)
	KICK,			//킥(run + jump 상태일 때 jump+kick이 될 수 있다)
	ITEM_PICK,		//아이템 줍기
	ITEM_ATTACK,	//아이템 공격
	ITEM_THROW,		//아이템 던지기
	DEFEND,		//방어
	HIT,			//피격
	JUMP, 			//점프
	FALL,			//벽 등에 부딪힐 때 / 공격받아서 솟아오를 때 / 아이템처럼 던져질 때 떨어짐
	DOWN,			//HP가 0이 아닐 때 / 기력으로 부활할 때 쓰러짐
	KO			//쓰러짐
};

struct tagCharacterSetting
{
	POINT3D CH;	//캐릭터 렉트 그려질 포인트
	RECT ch;		//캐릭터 렉트
	RECT atk;	//캐릭터 공격렉트
	image* img;	//이미지
	animation* ani;
	string chName;	//캐릭터 이름
	
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
//소지금			- 돈
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
	int maxHP;	//최대체력
	int money;	//소지금 / 떨구는 돈
};

struct tagState
{
	bool run;		//달리기
	bool jump;		//점프
	int W;			//무기(0은 보통, 1~8은 사진 순서대로)
};



class character : public gameNode
{
protected:
	POINT3D pos;

public:
	character() {};
	~character() override {};

	POINT3D& getPos() { return pos; }

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

