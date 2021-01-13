#include "stdafx.h"
#include "item.h"
#include "character.h"

HRESULT item::init()
{
	for (int i = 0; i < IMAX; i++)
	{
		_item[i]._inventory = false;
	}
	itemlist();
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

void item::itemlist()
{
	//ÈÞ´ëºÒ°¡´É
	//shop1 Ä«Æä
	_item[0].name = "Coffe";
	_item[0]._plusenergy = 2;
	_item[0]._recoveryhp = 16;
	_item[0]._plusmaxHP = 4;
	_item[0]._price2 = 95;

	_item[1].name = "Tea";
	_item[1]._plusenergy = 4;
	_item[1]._price2 = 95;

	_item[2].name = "Hot Cocoa";
	_item[2]._plusguard = 1;
	_item[2]._recoveryhp = 24;
	_item[2]._plusmaxHP = 6;
	_item[2]._price1 = 1;
	_item[2]._price2 = 25;

	_item[3].name = "Pancakes";
	_item[3]._recoveryhp = 32;
	_item[3]._plusmaxHP = 8;
	_item[3]._price1 = 3;
	_item[3]._price2 = 30;

	_item[4].name = "Waffles";
	_item[4]._plusagility = 1;
	_item[4]._plusendure = 1;
	_item[4]._recoveryhp = 32;
	_item[4]._plusmaxHP = 8;
	_item[4]._price1 = 4;
	_item[4]._price2 = 10;

	//shop3 ½º½Ã
	//½Ñ½º½Ã
	_item[5].name = "Egg";
	_item[5]._pluspunch = 1;
	_item[5]._recoveryhp = 10;
	_item[5]._plusmaxHP = 2;
	_item[5]._price1 = 2;
	_item[5]._price2 = 25;

	_item[6].name = "octopus";
	_item[6]._plusweapon = 1;
	_item[6]._recoveryhp = 8;
	_item[6]._plusmaxHP = 2;
	_item[6]._price1 = 2;
	_item[6]._price2 = 25;

	_item[7].name = "squid";
	_item[7]._pluspower = 2;
	_item[7]._recoveryhp = 4;
	_item[7]._plusmaxHP = 1;
	_item[7]._price1 = 2;
	_item[7]._price2 = 25;

	_item[8].name = "conger Eel";
	_item[8]._plusguard = 2;
	_item[8]._recoveryhp = 16;
	_item[8]._plusmaxHP = 4;
	_item[8]._price1 = 3;
	_item[8]._price2 = 75;

	_item[9].name = "Prawn";
	_item[9]._plusendure = 2;
	_item[9]._recoveryhp = 32;
	_item[9]._plusmaxHP = 8;
	_item[9]._price1 = 6;

	//ºñ½ÑÃÊ¹ä

	_item[10].name = "Salmon";
	_item[10]._pluspunch = 1;
	_item[10]._plusenergy = 2;
	_item[10]._recoveryhp = 40;
	_item[10]._plusmaxHP = 10;
	_item[10]._price1 = 8;
	_item[10]._price2 = 25;

	_item[11].name = "Ark Shell";
	_item[11]._plusweapon = 1;
	_item[11]._plusenergy = 2;
	_item[11]._recoveryhp = 50;
	_item[11]._plusmaxHP = 12;
	_item[11]._price1 = 9;

	_item[12].name = "Sea Urchin";
	_item[12]._pluspower = 2;
	_item[12]._plusenergy = 2;
	_item[12]._recoveryhp = 64;
	_item[12]._plusmaxHP = 16;
	_item[12]._price1 = 11;
	_item[12]._price2 = 50;

	_item[13].name = "Halibut";
	_item[13]._plusguard = 3;
	_item[13]._plusenergy = 7;
	_item[13]._recoveryhp = 80;
	_item[13]._plusmaxHP = 20;
	_item[13]._price1 = 18;
	_item[13]._price2 = 50;

	_item[14].name = "SwordFish";
	_item[14]._pluspunch = 4;
	_item[14]._pluspower = 4;
	_item[14]._plusendure = 4;
	_item[14]._plusenergy = 5;
	_item[14]._recoveryhp = 80;
	_item[14]._plusmaxHP = 20;
	_item[14]._price1 = 28;
	_item[14]._price2 = 75;
	
	//ROLL

	_item[15].name = "salad Roll";
	_item[15]._recoveryhp = 20;
	_item[15]._plusmaxHP = 5;
	_item[15]._price1 = 2;

	_item[16].name = "TunaRoll";
	_item[16]._recoveryhp = 32;
	_item[16]._plusmaxHP = 8;
	_item[16]._price1 = 3;
	_item[16]._price2 = 75;

	_item[17].name = "ShrimpRoll";
	_item[17]._recoveryhp = 50;
	_item[17]._plusmaxHP = 12;
	_item[17]._price1 = 6;
	_item[17]._price2 = 25;

	_item[18].name = "MixedRoll";
	_item[18]._recoveryhp = 80;
	_item[18]._plusmaxHP = 20;
	_item[18]._price1 = 10;
	_item[18]._price2 = 50;


	//ÈÞ´ë°¡´É
	//shop2 »§Áý
	_item[19].name = "Donut";
	_item[19]._plusenergy = 6;
	_item[19]._price2 = 80;
	_item[19]._inventory = true;

	_item[20].name = "Muffin";
	_item[20]._plusagility = 1;
	_item[20]._recoveryhp = 6;
	_item[20]._plusmaxHP = 1;
	_item[20]._price2 = 90;
	_item[20]._inventory = true;

	_item[21].name = "Bagel";
	_item[21]._plusguard = 1;
	_item[21]._recoveryhp = 6;
	_item[21]._plusmaxHP = 1;
	_item[21]._price2 = 90;
	_item[21]._inventory = true;

	_item[22].name = "HoneyBun";
	_item[22]._plusendure = 1;
	_item[22]._recoveryhp = 6;
	_item[22]._plusmaxHP = 1;
	_item[22]._inventory = true;

	_item[23].name = "Croissant";
	_item[23]._recoveryhp = 8;
	_item[23]._plusmaxHP = 2;
	_item[23]._price1 = 1;
	_item[23]._inventory = true;

}
