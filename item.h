#pragma once
#include "gameScene.h"

class item : public gameScene
{
private:
string _iName;
int _price;			//센트 단위 게임 내 표기는 달러 그러므로 100 센트면 1달러 200센트면 게임 내에서는 $ 2.00
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
	
	string getName() { return _iName; }
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