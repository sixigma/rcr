#pragma once
#include "gameScene.h"

//struct itemstate
//{
//	string name;
//	int _price1;		//그냥달러1~10자리
//	int _price2;		//소수점
//	int _pluspunch;		//펀치	
//	int _pluskick;		//킥		
//	int _plusweapon;	//무기	
//	int _pluspower;		//힘	    
//	int _plusagility;	//민첩	
//	int _plusguard;		//방어	
//	int _plusendure;	//맷집	
//	int _plusenergy;	//기력	
//	int _recoveryhp;	//체력	
//	int _plusmaxHP;		//최대체력
//	int cnt;			//아이템 갯수
//	bool _inventory;	// 인벤토리에 들어가는 탬인지 아닌지. 그냥 간단하게 불로 정의했어용 수정이 필요하시면 하시면됩니다아아아앙
//};

class item : public gameScene
{
private:
string name;
int _price;		//그냥달러1~10자리
int _plusPunch;		//펀치	
int _plusKick;		//킥		
int _plusWeapon;	//무기	
int _plusPower;		//힘	    
int _plusAgility;	//민첩	
int _plusGuard;		//방어	
int _plusEndure;	//맷집	
int _plusEnergy;	//기력	
int _recoveryHp;	//체력	
int _plusMaxHp;		//최대체력
public:
	

	HRESULT init(string _name);
	void release() override;
	void update() override;
	void render() override;
	void itemList(string _name);
	
	string getName() { return name; }
	int getPrice() { return _price; }
	int getPlusPunch() { return _plusPunch; }
	int getPlusKick(){ return _plusKick; }
	int getPlusWeapon() { return _plusWeapon; }
	int getPlusPower() { return _plusPower; }
	int getPlusAgility() { return _plusAgility; }
	int getPlusGuard() { return _plusGuard; }
	int getPlusEndure() { return _plusEndure; }
	int getPlusEnergy() { return _plusEnergy; }
	int getRecoveryHp() { return _recoveryHp; }
	int getPlusMaxHp() { return _plusMaxHp; }
	
};