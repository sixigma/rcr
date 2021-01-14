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
int _price1;		//그냥달러1~10자리
int _price2;		//소수점
int _pluspunch;		//펀치	
int _pluskick;		//킥		
int _plusweapon;	//무기	
int _pluspower;		//힘	    
int _plusagility;	//민첩	
int _plusguard;		//방어	
int _plusendure;	//맷집	
int _plusenergy;	//기력	
int _recoveryhp;	//체력	
int _plusmaxHP;		//최대체력
int cnt;			//아이템 갯수
public:
	

	HRESULT init(string _name);
	void release() override;
	void update() override;
	void render() override;
	void itemlist(string _name);
	
	string getname() { return name; }
	int getprice() { return _price1; }
	int getprice2() { return _price2; }
	int getpluspunch() { return _pluspunch; }
	int getpluskick(){ return _pluskick; }
	int getplusweapon() { return _plusweapon; }
	int getpluspower() { return _pluspower; }
	int getplusagility() { return _plusagility; }
	int getplusguard() { return _plusguard; }
	int getplusendure() { return _plusendure; }
	int getplusenergy() { return _plusenergy; }
	int getrecoveryhp() { return _recoveryhp; }
	int getplusmaxHP() { return _plusmaxHP; }
	
};