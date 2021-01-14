#include "stdafx.h"
#include "item.h"
#include "character.h"

HRESULT item::init(string _name)
{
	_price1			= 0;	//±×³É´Þ·¯1~10ÀÚ¸®
	_price2			= 0;	//¼Ò¼öÁ¡
	_plusPunch		= 0;	//ÆÝÄ¡	
	_plusKick		= 0;	//Å±		
	_plusWeapon		= 0;	//¹«±â	
	_plusPower		= 0;	//Èû	    
	_plusAgility	= 0;	//¹ÎÃ¸	
	_plusGuard		= 0;	//¹æ¾î	
	_plusEndure		= 0;	//¸ËÁý	
	_plusEnergy		= 0;	//±â·Â	
	_recoveryHp		= 0;	//Ã¼·Â	
	_plusMaxHp		= 0;	//ÃÖ´ëÃ¼·Â


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
	//ÈÞ´ëºÒ°¡´É
	//shop1 Ä«Æä
	if(_name == "Coffee")
	{
		_plusEnergy = 2;
		_recoveryHp = 16;
		_plusMaxHp = 4;
		_price2 = 95;
	}
	if(_name == "Tea")
	{ 
		_plusEnergy = 4;
		_price2 = 95;
	}
	if (_name == "Hot Cocoa")
	{
		_plusGuard = 1;
		_recoveryHp = 24;
		_plusMaxHp = 6;
		_price1 = 1;
		_price2 = 25;
	}
	if (_name == "Pancakes")
	{
		_recoveryHp = 32;
		_plusMaxHp = 8;
		_price1 = 3;
		_price2 = 30;
	}
	
	if(_name == "Waffles")
	{
		_plusAgility = 1;
		_plusEndure = 1;
		_recoveryHp = 32;
		_plusMaxHp = 8;
		_price1 = 4;
		_price2 = 10;
	}
	//½ÑÃÊ¹ä
	if (_name =="Egg" )
	{
		_plusPunch = 1;
		_recoveryHp = 10;
		_plusMaxHp = 2;
		_price1 = 2;
		_price2 = 25;
	}

	if (_name == "Octopus")
	{
		_plusWeapon = 1;
		_recoveryHp = 8;
		_plusMaxHp = 2;
		_price1 = 2;
		_price2 = 25;
	}
	if (_name == "Squid")
	{
		_plusPower = 2;
		_recoveryHp = 4;
		_plusMaxHp = 1;
		_price1 = 2;
		_price2 = 25;
	}
	
	if (_name == "Conger Eel")
	{
		_plusGuard = 2;
		_recoveryHp = 16;
		_plusMaxHp = 4;
		_price1 = 3;
		_price2 = 75;
	}

	if (_name == "Prawn")
	{
		_plusEndure = 2;
		_recoveryHp = 32;
		_plusMaxHp = 8;
		_price1 = 6;
	}
	//ºñ½ÑÃÊ¹ä
	if (_name == "Salmon")
	{
		_plusPunch = 1;
		_plusEnergy = 2;
		_recoveryHp = 40;
		_plusMaxHp = 10;
		_price1 = 8;
		_price2 = 25;
	}
	
	if (_name == "Ark Shell")
	{
		_plusWeapon = 1;
		_plusEnergy = 2;
		_recoveryHp = 50;
		_plusMaxHp = 12;
		_price1 = 9;
	}
	if (_name == "Sea Urchin")
	{
		_plusPower = 2;
		_plusEnergy = 2;
		_recoveryHp = 64;
		_plusMaxHp = 16;
		_price1 = 11;
		_price2 = 50;
	}

	if (_name =="Halibut")
	{
		_plusGuard = 3;
		_plusEnergy = 7;
		_recoveryHp = 80;
		_plusMaxHp = 20;
		_price1 = 18;
		_price2 = 50;
	}

	if (_name == "SwordFish")
	{
		_plusPunch = 4;
		_plusPower = 4;
		_plusEndure = 4;
		_plusEnergy = 5;
		_recoveryHp = 80;
		_plusMaxHp = 20;
		_price1 = 28;
		_price2 = 75;
	}
	
	//·Ñ
	if (_name == "Salad Roll")
	{
		_recoveryHp = 20;
		_plusMaxHp = 5;
		_price1 = 2;
	}
	
	if (_name == "TunaRoll")
	{
		_recoveryHp = 32;
		_plusMaxHp = 8;
		_price1 = 3;
		_price2 = 75;
	}
	
	if (_name == "ShrimpRoll")
	{
		_recoveryHp = 50;
		_plusMaxHp = 12;
		_price1 = 6;
		_price2 = 25;
	}
	
	if (_name == "MixedRoll")
	{
		_recoveryHp = 80;
		_plusMaxHp = 20;
		_price1 = 10;
		_price2 = 50;
	}

	//»§Áý

	if (_name == "Donut")
	{
		_plusEnergy = 6;
		_price2 = 80;
		
	}

	if (_name == "Muffin")
	{
		_plusAgility = 1;
		_recoveryHp = 6;
		_plusMaxHp = 1;
		_price2 = 90;
	}
	
	if (_name == "Bagel")
	{
		_plusGuard = 1;
		_recoveryHp = 6;
		_plusMaxHp = 1;
		_price2 = 90;
	}

	if (_name == "HoneyBun")
	{
		_plusEndure = 1;
		_recoveryHp = 6;
		_plusMaxHp = 1;
		_price2 = 90;
	}

	if (_name == "Croissant")
	{
		_recoveryHp = 8;
		_plusMaxHp = 2;
		_price1 = 1;
	}

}
