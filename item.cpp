#include "stdafx.h"
#include "item.h"
#include "character.h"

HRESULT item::init(string _name)
{
	_iName			= _name;  //이름
	_price			= 0;	//센트 단위 게임 내 표기는 달러 그러므로 100 센트면 1달러 200센트면 게임 내에서는 $ 2.00
	_plusPunch		= 0;	//펀치	
	_plusKick		= 0;	//킥		
	_plusWeapon		= 0;	//무기	
	_plusPower		= 0;	//힘	    
	_plusAgility	= 0;	//민첩	
	_plusGuard		= 0;	//방어	
	_plusEndure		= 0;	//맷집	
	_plusEnergy		= 0;	//기력	
	_recoveryHp		= 0;	//체력	
	_plusMaxHp		= 0;	//최대체력

	itemList(_name);
	return S_OK;
}

void item::release()
{

}

void item::update()
{
	
}

void item::render()
{

}

void item::itemList(string _name)
{
	//휴대불가능
	//shop1 카페
	if(_name == "Coffee")
	{
		_plusEnergy = 2;
		_recoveryHp = 16;
		_plusMaxHp = 4;
		_price = 95;
	}
	if(_name == "Tea")
	{ 
		_plusEnergy = 4;
		_price = 95;
	}
	if (_name == "HotCocoa")
	{
		_plusGuard = 1;
		_recoveryHp = 24;
		_plusMaxHp = 6;
		_price = 125;
	}
	if (_name == "Pancakes")
	{
		_recoveryHp = 32;
		_plusMaxHp = 8;
		_price = 330;
	}
	
	if(_name == "Waffles")
	{
		_plusAgility = 1;
		_plusEndure = 1;
		_recoveryHp = 32;
		_plusMaxHp = 8;
		_price = 410;
	}
	//싼초밥
	if (_name =="Egg" )
	{
		_plusPunch = 1;
		_recoveryHp = 10;
		_plusMaxHp = 2;
		_price = 225;
	}

	if (_name == "Octopus")
	{
		_plusWeapon = 1;
		_recoveryHp = 8;
		_plusMaxHp = 2;
		_price = 225;
	}
	if (_name == "Squid")
	{
		_plusPower = 2;
		_recoveryHp = 4;
		_plusMaxHp = 1;
		_price = 225;
	}
	
	if (_name == "CongerEel")
	{
		_plusGuard = 2;
		_recoveryHp = 16;
		_plusMaxHp = 4;
		_price = 375;
	}

	if (_name == "Prawn")
	{
		_plusEndure = 2;
		_recoveryHp = 32;
		_plusMaxHp = 8;
		_price = 600;
	}
	//비싼초밥
	if (_name == "Salmon")
	{
		_plusPunch = 1;
		_plusEnergy = 2;
		_recoveryHp = 40;
		_plusMaxHp = 10;
		_price = 825;
	}
	
	if (_name == "ArkShell")
	{
		_plusWeapon = 1;
		_plusEnergy = 2;
		_recoveryHp = 50;
		_plusMaxHp = 12;
		_price = 900;
	}
	if (_name == "SeaUrchin")
	{
		_plusPower = 2;
		_plusEnergy = 2;
		_recoveryHp = 64;
		_plusMaxHp = 16;
		_price = 1150;
		
	}

	if (_name =="Halibut")
	{
		_plusGuard = 3;
		_plusEnergy = 7;
		_recoveryHp = 80;
		_plusMaxHp = 20;
		_price = 1850;
		
	}

	if (_name == "SwordFish")
	{
		_plusPunch = 4;
		_plusPower = 4;
		_plusEndure = 4;
		_plusEnergy = 5;
		_recoveryHp = 80;
		_plusMaxHp = 20;
		_price = 2875;
	}
	
	//롤
	if (_name == "SaladRoll")
	{
		_recoveryHp = 20;
		_plusMaxHp = 5;
		_price = 200;
	}
	
	if (_name == "TunaRoll")
	{
		_recoveryHp = 32;
		_plusMaxHp = 8;
		_price = 375;
		
	}
	
	if (_name == "ShrimpRoll")
	{
		_recoveryHp = 50;
		_plusMaxHp = 12;
		_price = 625;
	}
	
	if (_name == "MixedRoll")
	{
		_recoveryHp = 80;
		_plusMaxHp = 20;
		_price = 1050;
		
	}

	//빵집======휴대가능

	if (_name == "Donut")
	{
		_plusEnergy = 6;
		_price = 80;
		
	}

	if (_name == "Muffin")
	{
		_plusAgility = 1;
		_recoveryHp = 6;
		_plusMaxHp = 1;
		_price = 90;
	}
	
	if (_name == "Bagel")
	{
		_plusGuard = 1;
		_recoveryHp = 6;
		_plusMaxHp = 1;
		_price = 90;
	}

	if (_name == "HoneyBun")
	{
		_plusEndure = 1;
		_recoveryHp = 6;
		_plusMaxHp = 1;
		_price = 90;
	}

	if (_name == "Croissant")
	{
		_recoveryHp = 8;
		_plusMaxHp = 2;
		_price = 100;
	}

}
