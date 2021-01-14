#include "stdafx.h"
#include "item.h"
#include "character.h"

HRESULT item::init(string _name)
{
	itemlist(_name);
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

void item::itemlist(string _name)
{
	//ÈÞ´ëºÒ°¡´É
	//shop1 Ä«Æä
	if(_name == "Coffee")
	{
		_plusenergy = 2;
		_recoveryhp = 16;
		_plusmaxHP = 4;
		_price2 = 95;
	}
	if(_name == "Tea")
	{ 
		_plusenergy = 4;
		_price2 = 95;
	}
	if (_name == "Hot Cocoa")
	{
		_plusguard = 1;
		_recoveryhp = 24;
		_plusmaxHP = 6;
		_price1 = 1;
		_price2 = 25;
	}
	if (_name == "Pancakes")
	{
		_recoveryhp = 32;
		_plusmaxHP = 8;
		_price1 = 3;
		_price2 = 30;
	}
	
	if(_name == "Waffles")
	{
		_plusagility = 1;
		_plusendure = 1;
		_recoveryhp = 32;
		_plusmaxHP = 8;
		_price1 = 4;
		_price2 = 10;
	}
	//½ÑÃÊ¹ä
	if (_name =="EGG" )
	{
		_pluspunch = 1;
		_recoveryhp = 10;
		_plusmaxHP = 2;
		_price1 = 2;
		_price2 = 25;
	}

	if (_name == "octopus")
	{
		_plusweapon = 1;
		_recoveryhp = 8;
		_plusmaxHP = 2;
		_price1 = 2;
		_price2 = 25;
	}
	if (_name == "squid")
	{
		_pluspower = 2;
		_recoveryhp = 4;
		_plusmaxHP = 1;
		_price1 = 2;
		_price2 = 25;
	}
	
	if (_name == "conger Eel")
	{
		_plusguard = 2;
		_recoveryhp = 16;
		_plusmaxHP = 4;
		_price1 = 3;
		_price2 = 75;
	}

	if (_name == "Prawn")
	{
		_plusendure = 2;
		_recoveryhp = 32;
		_plusmaxHP = 8;
		_price1 = 6;
	}
	//ºñ½ÑÃÊ¹ä
	if (_name == "Salmon")
	{
		_pluspunch = 1;
		_plusenergy = 2;
		_recoveryhp = 40;
		_plusmaxHP = 10;
		_price1 = 8;
		_price2 = 25;
	}
	
	if (_name == "Ark Shell")
	{
		_plusweapon = 1;
		_plusenergy = 2;
		_recoveryhp = 50;
		_plusmaxHP = 12;
		_price1 = 9;
	}
	if (_name == "Sea Urchin")
	{
		_pluspower = 2;
		_plusenergy = 2;
		_recoveryhp = 64;
		_plusmaxHP = 16;
		_price1 = 11;
		_price2 = 50;
	}

	if (_name =="Halibut")
	{
		_plusguard = 3;
		_plusenergy = 7;
		_recoveryhp = 80;
		_plusmaxHP = 20;
		_price1 = 18;
		_price2 = 50;
	}

	if (_name == "SwordFish")
	{
		_pluspunch = 4;
		_pluspower = 4;
		_plusendure = 4;
		_plusenergy = 5;
		_recoveryhp = 80;
		_plusmaxHP = 20;
		_price1 = 28;
		_price2 = 75;
	}
	
	//·Ñ
	if (_name == "salad Roll")
	{
		_recoveryhp = 20;
		_plusmaxHP = 5;
		_price1 = 2;
	}
	
	if (_name == "TunaRoll")
	{
		_recoveryhp = 32;
		_plusmaxHP = 8;
		_price1 = 3;
		_price2 = 75;
	}
	
	if (_name == "ShrimpRoll")
	{
		_recoveryhp = 50;
		_plusmaxHP = 12;
		_price1 = 6;
		_price2 = 25;
	}
	
	if (_name == "MixedRoll")
	{
		_recoveryhp = 80;
		_plusmaxHP = 20;
		_price1 = 10;
		_price2 = 50;
	}

	//»§Áý

	if (_name == "Donut")
	{
		_plusenergy = 6;
		_price2 = 80;
		
	}

	if (_name == "Muffin")
	{
		_plusagility = 1;
		_recoveryhp = 6;
		_plusmaxHP = 1;
		_price2 = 90;
	}
	
	if (_name == "Bagel")
	{
		_plusguard = 1;
		_recoveryhp = 6;
		_plusmaxHP = 1;
		_price2 = 90;
	}

	if (_name == "HoneyBun")
	{
		_plusendure = 1;
		_recoveryhp = 6;
		_plusmaxHP = 1;
		_price2 = 90;
	}

	if (_name == "Croissant")
	{
		_recoveryhp = 8;
		_plusmaxHP = 2;
		_price1 = 1;
	}

}
