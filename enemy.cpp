#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(POINT3D pt, int type, int color)
{
	_type = type;
	_color = color;
	_emSet.CH = pt;				//À§Ä¡

	ani1Set();
	ani2Set();
	ani3Set();
	ani4Set();
	ani6Set();
	ani7Set();

	//º¸½º
	if (_type == 0)
	{
		_walk = IMG->find("º¸½º-°È±â");
		_run = IMG->find("º¸½º-´Ş¸®±â");
		_punch = IMG->find("º¸½º-ÆİÄ¡");
		_kick = IMG->find("º¸½º-Å±");
		_uppercut = IMG->find("º¸½º-¾îÆÛÄÆ");
		_highkick = IMG->find("º¸½º-ÇÏÀÌÅ±");
		_run_punch = IMG->find("º¸½º-´Ş¸®±âÆİÄ¡");
		_jump = IMG->find("º¸½º-Á¡ÇÁ");
		_jumpkick = IMG->find("º¸½º-Á¡ÇÁÅ±");
		_defend = IMG->find("º¸½º-¹æ¾î");
		_beatup = IMG->find("º¸½º-ÇÇ°İ");
		_ko = IMG->find("º¸½º-KO");
		_stick_pipe = IMG->find("º¸½º-½ºÆ½");
		_chain = IMG->find("º¸½º-Ã¼ÀÎ");
		_knuckles = IMG->find("º¸½º-³ÊÅ¬");
		_rock = IMG->find("º¸½º-µ¹");
		_lift_trashcan = IMG->find("º¸½º-¾²·¹±â");
		_lift_crate = IMG->find("º¸½º-¹Ú½º");
		_lift_tire = IMG->find("º¸½º-Å¸ÀÌ¾î");
		_lift_human = IMG->find("º¸½º-»ç¶÷");
		_throw_stick_pipe = IMG->find("º¸½º-½ºÆ½´øÁö±â");
		_throw_chain = IMG->find("º¸½º-Ã¼ÀÎ´øÁö±â");
		_throw_knuckles = IMG->find("º¸½º-³ÊÅ¬´øÁö±â");
		_throw_rock = IMG->find("º¸½º-µ¹´øÁö±â");
		_throw_trashcan = IMG->find("º¸½º-¾²·¹±â´øÁö±â");
		_throw_crate = IMG->find("º¸½º-¹Ú½º´øÁö±â");
		_throw_tire = IMG->find("º¸½º-Å¸ÀÌ¾î´øÁö±â");
		_throw_human = IMG->find("º¸½º-»ç¶÷´øÁö±â");

		_emSet.img = _run;			//ÀÌ¹ÌÁö
		_emSet.ani = _2Rani;		//¾Ö´Ï
		_emSet.ani->stop();			//¾Ö´Ï ½ºÅ¾

		if (_color == 0)
		{
			_emSet.chName = "Moose";	//ÀÌ¸§

			_emStatus.punch = 26;	//ÆİÄ¡
			_emStatus.kick = 35;	//Å±
			_emStatus.weapon = 23;	//¹«±â
			_emStatus.power = 28;	//Èû
			_emStatus.agility = 25;	//¹ÎÃ¸
			_emStatus.guard = 25;	//°¡µå
			_emStatus.endure = 22;	//¸ËÁı
			_emStatus.energy = 24;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 52;	//Ã¼·Â
			_emStatus.money = 225;	//µ· µå¶ø
		}

		_emSet.ch = MakeRct(_emSet.CH.x - 33, _emSet.CH.y - 130, 66, 130);	//ÇÇ°İ¹üÀ§

		_emST = IDLE;	//»óÅÂ

		_emState.jump = false;	//Á¡ÇÁ¿©ºÎ
		_left = false;	//¿ŞÂÊ¿©ºÎ
		_emState.run = false;	//´Ş¸®±â ¿©ºÎ

	}
	//Å¸ÀÔ1
	if (_type == 1)
	{

		_walk = IMG->find("1-°È±â");
		_run = IMG->find("1-´Ş¸®±â");
		_punch = IMG->find("1-ÆİÄ¡");
		_kick = IMG->find("1-Å±");
		_uppercut = IMG->find("1-¾îÆÛÄÆ");
		_highkick = IMG->find("1-ÇÏÀÌÅ±");
		_run_punch = IMG->find("1-´Ş¸®±âÆİÄ¡");
		_jump = IMG->find("1-Á¡ÇÁ");
		_jumpkick = IMG->find("1-Á¡ÇÁÅ±");
		_defend = IMG->find("1-¹æ¾î");
		_beatup = IMG->find("1-ÇÇ°İ");
		_ko = IMG->find("1-KO");
		_stick_pipe = IMG->find("1-½ºÆ½");
		_chain = IMG->find("1-Ã¼ÀÎ");
		_knuckles = IMG->find("1-³ÊÅ¬");
		_rock = IMG->find("1-µ¹");
		_lift_trashcan = IMG->find("1-¾²·¹±â");
		_lift_crate = IMG->find("1-¹Ú½º");
		_lift_tire = IMG->find("1-Å¸ÀÌ¾î");
		_lift_human = IMG->find("1-»ç¶÷");
		_throw_stick_pipe = IMG->find("1-½ºÆ½´øÁö±â");
		_throw_chain = IMG->find("1-Ã¼ÀÎ´øÁö±â");
		_throw_knuckles = IMG->find("1-³ÊÅ¬´øÁö±â");
		_throw_rock = IMG->find("1-µ¹´øÁö±â");
		_throw_trashcan = IMG->find("1-¾²·¹±â´øÁö±â");
		_throw_crate = IMG->find("1-¹Ú½º´øÁö±â");
		_throw_tire = IMG->find("1-Å¸ÀÌ¾î´øÁö±â");
		_throw_human = IMG->find("1-»ç¶÷´øÁö±â");

		_emSet.img = _run;			//ÀÌ¹ÌÁö
		_emSet.ani = _2Rani;		//¾Ö´Ï
		_emSet.ani->stop();			//¾Ö´Ï ½ºÅ¾

		//Ã»·Ï(¼¾¸®´ÙÀÌ)
		if (_color == 0)
		{
			_emSet.chName = "Larry";	//ÀÌ¸§

			_emStatus.punch = 12;	//ÆİÄ¡
			_emStatus.kick = 4;	//Å±
			_emStatus.weapon = 6;	//¹«±â
			_emStatus.power = 1;	//Èû
			_emStatus.agility = 6;	//¹ÎÃ¸
			_emStatus.guard = 5;	//°¡µå
			_emStatus.endure = 5;	//¸ËÁı
			_emStatus.energy = 8;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 13;	//Ã¼·Â
			_emStatus.money = 50;	//µ· µå¶ø
		}
		//ºĞÈ«(»çÄ«½´Äí)
		if (_color == 1)
		{
			_emSet.chName = "Skip";		//ÀÌ¸§

			_emStatus.punch = 18;	//ÆİÄ¡
			_emStatus.kick = 4;	//Å±
			_emStatus.weapon = 7;	//¹«±â
			_emStatus.power = 8;	//Èû
			_emStatus.agility = 7;	//¹ÎÃ¸
			_emStatus.guard = 4;	//°¡µå
			_emStatus.endure = 11;	//¸ËÁı
			_emStatus.energy = 7;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 12;	//Ã¼·Â
			_emStatus.money = 55;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(252, 116, 180));//ºĞÈ« Ã¼ÀÎÁö
		}
		//¿¬µÎ(´©¸¶¿ÀÄ«)
		if (_color == 2)
		{
			_emSet.chName = "Rex";		//ÀÌ¸§

			_emStatus.punch = 15;	//ÆİÄ¡
			_emStatus.kick = 10;	//Å±
			_emStatus.weapon = 10;	//¹«±â
			_emStatus.power = 8;	//Èû
			_emStatus.agility = 7;	//¹ÎÃ¸
			_emStatus.guard = 12;	//°¡µå
			_emStatus.endure = 8;	//¸ËÁı
			_emStatus.energy = 10;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 60;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(128, 208, 16));//¿¬µÎ·Î Ã¼ÀÎÁö
		}
		//³ë¶û(È£½ÃÄí»ç)
		if (_color == 3)
		{
			_emSet.chName = "Robby";		//ÀÌ¸§

			_emStatus.punch = 22;	//ÆİÄ¡
			_emStatus.kick = 11;	//Å±
			_emStatus.weapon = 13;	//¹«±â
			_emStatus.power = 14;	//Èû
			_emStatus.agility = 10;	//¹ÎÃ¸
			_emStatus.guard = 11;	//°¡µå
			_emStatus.endure = 14;	//¸ËÁı
			_emStatus.energy = 14;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 75;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(240, 188, 60));//³ë¶ûÀ¸·Î Ã¼ÀÎÁö
		}
		//È¸»ö(ÇÏÄíÅ¸°¡)
		if (_color == 4)
		{
			_emSet.chName = "Lefty";		//ÀÌ¸§

			_emStatus.punch = 26;	//ÆİÄ¡
			_emStatus.kick = 15;	//Å±
			_emStatus.weapon = 14;	//¹«±â
			_emStatus.power = 17;	//Èû
			_emStatus.agility = 14;	//¹ÎÃ¸
			_emStatus.guard = 15;	//°¡µå
			_emStatus.endure = 13;	//¸ËÁı
			_emStatus.energy = 13;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 90;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(116, 116, 116));//È¸»öÀ¸·Î Ã¼ÀÎÁö
		}
		//»¡°­(¸¶Å¸°¡¿Í)
		if (_color == 5)
		{
			_emSet.chName = "Herb";		//ÀÌ¸§

			_emStatus.punch = 24;	//ÆİÄ¡
			_emStatus.kick = 19;	//Å±
			_emStatus.weapon = 19;	//¹«±â
			_emStatus.power = 14;	//Èû
			_emStatus.agility = 19;	//¹ÎÃ¸
			_emStatus.guard = 16;	//°¡µå
			_emStatus.endure = 20;	//¸ËÁı
			_emStatus.energy = 14;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 100;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//»¡°­À¸·Î Ã¼ÀÎÁö
		}
		//ÃÊ·Ï(È£·á)
		if (_color == 6)
		{
			_emSet.chName = "Boris";		//ÀÌ¸§

			_emStatus.punch = 31;	//ÆİÄ¡
			_emStatus.kick = 19;	//Å±
			_emStatus.weapon = 16;	//¹«±â
			_emStatus.power = 17;	//Èû
			_emStatus.agility = 19;	//¹ÎÃ¸
			_emStatus.guard = 21;	//°¡µå
			_emStatus.endure = 18;	//¸ËÁı
			_emStatus.energy = 21;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 120;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//ÃÊ·ÏÀ¸·Î Ã¼ÀÎÁö
		}
		//³²»ö(Å¸´Ï¹Ù³ª)
		if (_color == 7)
		{
			_emSet.chName = "Bubba";		//ÀÌ¸§

			_emStatus.punch = 30;	//ÆİÄ¡
			_emStatus.kick = 17;	//Å±
			_emStatus.weapon = 24;	//¹«±â
			_emStatus.power = 21;	//Èû
			_emStatus.agility = 20;	//¹ÎÃ¸
			_emStatus.guard = 20;	//°¡µå
			_emStatus.endure = 21;	//¸ËÁı
			_emStatus.energy = 21;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 125;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(24, 60, 92));//³²»öÀ¸·Î Ã¼ÀÎÁö
		}
		//ÁÖÈ²(·¹ÀÌÈ£)
		if (_color == 8)
		{
			_emSet.chName = "Slash";		//ÀÌ¸§

			_emStatus.punch = 34;	//ÆİÄ¡
			_emStatus.kick = 24;	//Å±
			_emStatus.weapon = 22;	//¹«±â
			_emStatus.power = 19;	//Èû
			_emStatus.agility = 24;	//¹ÎÃ¸
			_emStatus.guard = 25;	//°¡µå
			_emStatus.endure = 23;	//¸ËÁı
			_emStatus.energy = 21;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 150;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(216, 40, 0));//ÁÖÈ²À¸·Î Ã¼ÀÎÁö
		}

		_emST = IDLE;	//»óÅÂ

		_emState.jump = false;	//Á¡ÇÁ¿©ºÎ
		_left = false;	//¿ŞÂÊ¿©ºÎ
		_emState.run = false;	//´Ş¸®±â ¿©ºÎ

		_emSet.CH = pt;				//À§Ä¡
		_emSet.ch = MakeRct(_emSet.CH.x - 33, _emSet.CH.y - 130, 66, 130);	//ÇÇ°İ¹üÀ§
	}
	//Å¸ÀÔ2
	if (_type == 2)
	{
		_walk = IMG->find("2-°È±â");
		_run = IMG->find("2-´Ş¸®±â");
		_punch = IMG->find("2-ÆİÄ¡");
		_kick = IMG->find("2-Å±");
		_uppercut = IMG->find("2-¾îÆÛÄÆ");
		_highkick = IMG->find("2-ÇÏÀÌÅ±");
		_run_punch = IMG->find("2-´Ş¸®±âÆİÄ¡");
		_jump = IMG->find("2-Á¡ÇÁ");
		_jumpkick = IMG->find("2-Á¡ÇÁÅ±");
		_defend = IMG->find("2-¹æ¾î");
		_beatup = IMG->find("2-ÇÇ°İ");
		_ko = IMG->find("2-KO");
		_stick_pipe = IMG->find("2-½ºÆ½");
		_chain = IMG->find("2-Ã¼ÀÎ");
		_knuckles = IMG->find("2-³ÊÅ¬");
		_rock = IMG->find("2-µ¹");
		_lift_trashcan = IMG->find("2-¾²·¹±â");
		_lift_crate = IMG->find("2-¹Ú½º");
		_lift_tire = IMG->find("2-Å¸ÀÌ¾î");
		_lift_human = IMG->find("2-»ç¶÷");
		_throw_stick_pipe = IMG->find("2-½ºÆ½´øÁö±â");
		_throw_chain = IMG->find("2-Ã¼ÀÎ´øÁö±â");
		_throw_knuckles = IMG->find("2-³ÊÅ¬´øÁö±â");
		_throw_rock = IMG->find("2-µ¹´øÁö±â");
		_throw_trashcan = IMG->find("2-¾²·¹±â´øÁö±â");
		_throw_crate = IMG->find("2-¹Ú½º´øÁö±â");
		_throw_tire = IMG->find("2-Å¸ÀÌ¾î´øÁö±â");
		_throw_human = IMG->find("2-»ç¶÷´øÁö±â");

		_emSet.img = _run;			//ÀÌ¹ÌÁö
		_emSet.ani = _2Rani;		//¾Ö´Ï
		_emSet.ani->stop();			//¾Ö´Ï ½ºÅ¾

		//Ã»·Ï(¼¾¸®´ÙÀÌ)
		if (_color == 0)
		{
			_emSet.chName = "Barry";	//ÀÌ¸§

			_emStatus.punch = 2;	//ÆİÄ¡
			_emStatus.kick = 14;	//Å±
			_emStatus.weapon = 5;	//¹«±â
			_emStatus.power = 2;	//Èû
			_emStatus.agility = 7;	//¹ÎÃ¸
			_emStatus.guard = 5;	//°¡µå
			_emStatus.endure = 4;	//¸ËÁı
			_emStatus.energy = 9;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 11;	//Ã¼·Â
			_emStatus.money = 50;	//µ· µå¶ø

		}
		//ºĞÈ«(»çÄ«½´Äí)
		if (_color == 1)
		{
			_emSet.chName = "Trent";		//ÀÌ¸§

			_emStatus.punch = 8;	//ÆİÄ¡
			_emStatus.kick = 14;	//Å±
			_emStatus.weapon = 6;	//¹«±â
			_emStatus.power = 9;	//Èû
			_emStatus.agility = 8;	//¹ÎÃ¸
			_emStatus.guard = 4;	//°¡µå
			_emStatus.endure = 10;	//¸ËÁı
			_emStatus.energy = 8;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 10;	//Ã¼·Â
			_emStatus.money = 55;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(252, 116, 180));//ºĞÈ« Ã¼ÀÎÁö
		}
		//¿¬µÎ(´©¸¶¿ÀÄ«)
		if (_color == 2)
		{
			_emSet.chName = "Lance";		//ÀÌ¸§

			_emStatus.punch = 5;	//ÆİÄ¡
			_emStatus.kick = 20;	//Å±
			_emStatus.weapon = 9;	//¹«±â
			_emStatus.power = 9;	//Èû
			_emStatus.agility = 8;	//¹ÎÃ¸
			_emStatus.guard = 12;	//°¡µå
			_emStatus.endure = 7;	//¸ËÁı
			_emStatus.energy = 11;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 60;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(128, 208, 16));//¿¬µÎ·Î Ã¼ÀÎÁö
		}
		//³ë¶û(È£½ÃÄí»ç)
		if (_color == 3)
		{
			_emSet.chName = "Chip";		//ÀÌ¸§

			_emStatus.punch = 12;	//ÆİÄ¡
			_emStatus.kick = 21;	//Å±
			_emStatus.weapon = 12;	//¹«±â
			_emStatus.power = 15;	//Èû
			_emStatus.agility = 11;	//¹ÎÃ¸
			_emStatus.guard = 11;	//°¡µå
			_emStatus.endure = 13;	//¸ËÁı
			_emStatus.energy = 15;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 75;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(240, 188, 60));//³ë¶ûÀ¸·Î Ã¼ÀÎÁö
		}
		//È¸»ö(ÇÏÄíÅ¸°¡)
		if (_color == 4)
		{
			_emSet.chName = "Sid";		//ÀÌ¸§

			_emStatus.punch = 16;	//ÆİÄ¡
			_emStatus.kick = 25;	//Å±
			_emStatus.weapon = 13;	//¹«±â
			_emStatus.power = 18;	//Èû
			_emStatus.agility = 15;	//¹ÎÃ¸
			_emStatus.guard = 15;	//°¡µå
			_emStatus.endure = 12;	//¸ËÁı
			_emStatus.energy = 14;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 90;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(116, 116, 116));//È¸»öÀ¸·Î Ã¼ÀÎÁö
		}
		//»¡°­(¸¶Å¸°¡¿Í)
		if (_color == 5)
		{
			_emSet.chName = "Erwin";		//ÀÌ¸§

			_emStatus.punch = 14;	//ÆİÄ¡
			_emStatus.kick = 29;	//Å±
			_emStatus.weapon = 18;	//¹«±â
			_emStatus.power = 15;	//Èû
			_emStatus.agility = 20;	//¹ÎÃ¸
			_emStatus.guard = 16;	//°¡µå
			_emStatus.endure = 19;	//¸ËÁı
			_emStatus.energy = 15;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 100;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//»¡°­À¸·Î Ã¼ÀÎÁö
		}
		//ÃÊ·Ï(È£·á)
		if (_color == 6)
		{
			_emSet.chName = "Yemi";		//ÀÌ¸§

			_emStatus.punch = 21;	//ÆİÄ¡
			_emStatus.kick = 29;	//Å±
			_emStatus.weapon = 15;	//¹«±â
			_emStatus.power = 18;	//Èû
			_emStatus.agility = 20;	//¹ÎÃ¸
			_emStatus.guard = 21;	//°¡µå
			_emStatus.endure = 17;	//¸ËÁı
			_emStatus.energy = 22;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 120;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//ÃÊ·ÏÀ¸·Î Ã¼ÀÎÁö
		}
		//³²»ö(Å¸´Ï¹Ù³ª)
		if (_color == 7)
		{
			_emSet.chName = "Shane";		//ÀÌ¸§

			_emStatus.punch = 20;	//ÆİÄ¡
			_emStatus.kick = 27;	//Å±
			_emStatus.weapon = 23;	//¹«±â
			_emStatus.power = 22;	//Èû
			_emStatus.agility = 21;	//¹ÎÃ¸
			_emStatus.guard = 20;	//°¡µå
			_emStatus.endure = 20;	//¸ËÁı
			_emStatus.energy = 22;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 125;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(24, 60, 92));//³²»öÀ¸·Î Ã¼ÀÎÁö
		}
		//ÁÖÈ²(·¹ÀÌÈ£)
		if (_color == 8)
		{
			_emSet.chName = "Edge";		//ÀÌ¸§

			_emStatus.punch = 24;	//ÆİÄ¡
			_emStatus.kick = 34;	//Å±
			_emStatus.weapon = 21;	//¹«±â
			_emStatus.power = 20;	//Èû
			_emStatus.agility = 25;	//¹ÎÃ¸
			_emStatus.guard = 25;	//°¡µå
			_emStatus.endure = 22;	//¸ËÁı
			_emStatus.energy = 22;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 150;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(216, 40, 0));//ÁÖÈ²À¸·Î Ã¼ÀÎÁö
		}

		_emST = IDLE;	//»óÅÂ

		_emState.jump = false;	//Á¡ÇÁ¿©ºÎ
		_left = false;	//¿ŞÂÊ¿©ºÎ
		_emState.run = false;	//´Ş¸®±â ¿©ºÎ

		_emSet.CH = pt;				//À§Ä¡
		_emSet.ch = MakeRct(_emSet.CH.x - 33, _emSet.CH.y - 130, 66, 130);	//ÇÇ°İ¹üÀ§

	}
	//Å¸ÀÔ3
	if (_type == 3)
	{

		_walk = IMG->find("3-°È±â");
		_run = IMG->find("3-´Ş¸®±â");
		_punch = IMG->find("3-ÆİÄ¡");
		_kick = IMG->find("3-Å±");
		_uppercut = IMG->find("3-¾îÆÛÄÆ");
		_highkick = IMG->find("3-ÇÏÀÌÅ±");
		_run_punch = IMG->find("3-´Ş¸®±âÆİÄ¡");
		_jump = IMG->find("3-Á¡ÇÁ");
		_jumpkick = IMG->find("3-Á¡ÇÁÅ±");
		_defend = IMG->find("3-¹æ¾î");
		_beatup = IMG->find("3-ÇÇ°İ");
		_ko = IMG->find("3-KO");
		_stick_pipe = IMG->find("3-½ºÆ½");
		_chain = IMG->find("3-Ã¼ÀÎ");
		_knuckles = IMG->find("3-³ÊÅ¬");
		_rock = IMG->find("3-µ¹");
		_lift_trashcan = IMG->find("3-¾²·¹±â");
		_lift_crate = IMG->find("3-¹Ú½º");
		_lift_tire = IMG->find("3-Å¸ÀÌ¾î");
		_lift_human = IMG->find("3-»ç¶÷");
		_throw_stick_pipe = IMG->find("3-½ºÆ½´øÁö±â");
		_throw_chain = IMG->find("3-Ã¼ÀÎ´øÁö±â");
		_throw_knuckles = IMG->find("3-³ÊÅ¬´øÁö±â");
		_throw_rock = IMG->find("3-µ¹´øÁö±â");
		_throw_trashcan = IMG->find("3-¾²·¹±â´øÁö±â");
		_throw_crate = IMG->find("3-¹Ú½º´øÁö±â");
		_throw_tire = IMG->find("3-Å¸ÀÌ¾î´øÁö±â");
		_throw_human = IMG->find("3-»ç¶÷´øÁö±â");

		_emSet.img = _run;			//ÀÌ¹ÌÁö
		_emSet.ani = _2Rani;		//¾Ö´Ï
		_emSet.ani->stop();			//¾Ö´Ï ½ºÅ¾

		//Ã»·Ï(¼¾¸®´ÙÀÌ)
		if (_color == 0)
		{
			_emSet.chName = "Terry";	//ÀÌ¸§

			_emStatus.punch = 3;	//ÆİÄ¡
			_emStatus.kick = 4;	//Å±
			_emStatus.weapon = 15;	//¹«±â
			_emStatus.power = 1;	//Èû
			_emStatus.agility = 7;	//¹ÎÃ¸
			_emStatus.guard = 5;	//°¡µå
			_emStatus.endure = 4;	//¸ËÁı
			_emStatus.energy = 9;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 11;	//Ã¼·Â
			_emStatus.money = 50;	//µ· µå¶ø

		}
		//ºĞÈ«(»çÄ«½´Äí)
		if (_color == 1)
		{
			_emSet.chName = "Logan";		//ÀÌ¸§

			_emStatus.punch = 9;	//ÆİÄ¡
			_emStatus.kick = 4;	//Å±
			_emStatus.weapon = 16;	//¹«±â
			_emStatus.power = 8;	//Èû
			_emStatus.agility = 8;	//¹ÎÃ¸
			_emStatus.guard = 4;	//°¡µå
			_emStatus.endure = 10;	//¸ËÁı
			_emStatus.energy = 8;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 10;	//Ã¼·Â
			_emStatus.money = 55;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(252, 116, 180));//ºĞÈ« Ã¼ÀÎÁö
		}
		//¿¬µÎ(´©¸¶¿ÀÄ«)
		if (_color == 2)
		{
			_emSet.chName = "Dirk";		//ÀÌ¸§

			_emStatus.punch = 6;	//ÆİÄ¡
			_emStatus.kick = 10;	//Å±
			_emStatus.weapon = 19;	//¹«±â
			_emStatus.power = 8;	//Èû
			_emStatus.agility = 8;	//¹ÎÃ¸
			_emStatus.guard = 12;	//°¡µå
			_emStatus.endure = 7;	//¸ËÁı
			_emStatus.energy = 11;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 60;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(128, 208, 16));//¿¬µÎ·Î Ã¼ÀÎÁö
		}
		//³ë¶û(È£½ÃÄí»ç)
		if (_color == 3)
		{
			_emSet.chName = "Ernie";		//ÀÌ¸§

			_emStatus.punch = 13;	//ÆİÄ¡
			_emStatus.kick = 11;	//Å±
			_emStatus.weapon = 22;	//¹«±â
			_emStatus.power = 14;	//Èû
			_emStatus.agility = 11;	//¹ÎÃ¸
			_emStatus.guard = 11;	//°¡µå
			_emStatus.endure = 13;	//¸ËÁı
			_emStatus.energy = 15;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 75;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(240, 188, 60));//³ë¶ûÀ¸·Î Ã¼ÀÎÁö
		}
		//È¸»ö(ÇÏÄíÅ¸°¡)
		if (_color == 4)
		{
			_emSet.chName = "Tony";		//ÀÌ¸§

			_emStatus.punch = 17;	//ÆİÄ¡
			_emStatus.kick = 15;	//Å±
			_emStatus.weapon = 23;	//¹«±â
			_emStatus.power = 17;	//Èû
			_emStatus.agility = 15;	//¹ÎÃ¸
			_emStatus.guard = 15;	//°¡µå
			_emStatus.endure = 12;	//¸ËÁı
			_emStatus.energy = 14;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 90;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(116, 116, 116));//È¸»öÀ¸·Î Ã¼ÀÎÁö
		}
		//»¡°­(¸¶Å¸°¡¿Í)
		if (_color == 5)
		{
			_emSet.chName = "Felix";		//ÀÌ¸§

			_emStatus.punch = 15;	//ÆİÄ¡
			_emStatus.kick = 19;	//Å±
			_emStatus.weapon = 28;	//¹«±â
			_emStatus.power = 14;	//Èû
			_emStatus.agility = 20;	//¹ÎÃ¸
			_emStatus.guard = 16;	//°¡µå
			_emStatus.endure = 19;	//¸ËÁı
			_emStatus.energy = 15;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 100;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//»¡°­À¸·Î Ã¼ÀÎÁö
		}
		//ÃÊ·Ï(È£·á)
		if (_color == 6)
		{
			_emSet.chName = "Fuji";		//ÀÌ¸§

			_emStatus.punch = 22;	//ÆİÄ¡
			_emStatus.kick = 19;	//Å±
			_emStatus.weapon = 25;	//¹«±â
			_emStatus.power = 17;	//Èû
			_emStatus.agility = 20;	//¹ÎÃ¸
			_emStatus.guard = 21;	//°¡µå
			_emStatus.endure = 17;	//¸ËÁı
			_emStatus.energy = 22;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 120;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//ÃÊ·ÏÀ¸·Î Ã¼ÀÎÁö
		}
		//³²»ö(Å¸´Ï¹Ù³ª)
		if (_color == 7)
		{
			_emSet.chName = "Bart";		//ÀÌ¸§

			_emStatus.punch = 21;	//ÆİÄ¡
			_emStatus.kick = 17;	//Å±
			_emStatus.weapon = 33;	//¹«±â
			_emStatus.power = 21;	//Èû
			_emStatus.agility = 21;	//¹ÎÃ¸
			_emStatus.guard = 20;	//°¡µå
			_emStatus.endure = 20;	//¸ËÁı
			_emStatus.energy = 22;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 125;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(24, 60, 92));//³²»öÀ¸·Î Ã¼ÀÎÁö
		}
		//ÁÖÈ²(·¹ÀÌÈ£)
		if (_color == 8)
		{
			_emSet.chName = "Blaze";		//ÀÌ¸§

			_emStatus.punch = 25;	//ÆİÄ¡
			_emStatus.kick = 24;	//Å±
			_emStatus.weapon = 31;	//¹«±â
			_emStatus.power = 19;	//Èû
			_emStatus.agility = 25;	//¹ÎÃ¸
			_emStatus.guard = 25;	//°¡µå
			_emStatus.endure = 22;	//¸ËÁı
			_emStatus.energy = 22;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 150;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(216, 40, 0));//ÁÖÈ²À¸·Î Ã¼ÀÎÁö
		}

		_emST = IDLE;	//»óÅÂ

		_emState.jump = false;	//Á¡ÇÁ¿©ºÎ
		_left = false;	//¿ŞÂÊ¿©ºÎ
		_emState.run = false;	//´Ş¸®±â ¿©ºÎ

		_emSet.CH = pt;				//À§Ä¡
		_emSet.ch = MakeRct(_emSet.CH.x - 33, _emSet.CH.y - 130, 66, 130);	//ÇÇ°İ¹üÀ§
	}
	//Å¸ÀÔ4
	if (_type == 4)
	{

		_walk = IMG->find("4-°È±â");
		_run = IMG->find("4-´Ş¸®±â");
		_punch = IMG->find("4-ÆİÄ¡");
		_kick = IMG->find("4-Å±");
		_uppercut = IMG->find("4-¾îÆÛÄÆ");
		_highkick = IMG->find("4-ÇÏÀÌÅ±");
		_run_punch = IMG->find("4-´Ş¸®±âÆİÄ¡");
		_jump = IMG->find("4-Á¡ÇÁ");
		_jumpkick = IMG->find("4-Á¡ÇÁÅ±");
		_defend = IMG->find("4-¹æ¾î");
		_beatup = IMG->find("4-ÇÇ°İ");
		_ko = IMG->find("4-KO");
		_stick_pipe = IMG->find("4-½ºÆ½");
		_chain = IMG->find("4-Ã¼ÀÎ");
		_knuckles = IMG->find("4-³ÊÅ¬");
		_rock = IMG->find("4-µ¹");
		_lift_trashcan = IMG->find("4-¾²·¹±â");
		_lift_crate = IMG->find("4-¹Ú½º");
		_lift_tire = IMG->find("4-Å¸ÀÌ¾î");
		_lift_human = IMG->find("4-»ç¶÷");
		_throw_stick_pipe = IMG->find("4-½ºÆ½´øÁö±â");
		_throw_chain = IMG->find("4-Ã¼ÀÎ´øÁö±â");
		_throw_knuckles = IMG->find("4-³ÊÅ¬´øÁö±â");
		_throw_rock = IMG->find("4-µ¹´øÁö±â");
		_throw_trashcan = IMG->find("4-¾²·¹±â´øÁö±â");
		_throw_crate = IMG->find("4-¹Ú½º´øÁö±â");
		_throw_tire = IMG->find("4-Å¸ÀÌ¾î´øÁö±â");
		_throw_human = IMG->find("4-»ç¶÷´øÁö±â");

		_emSet.img = _run;			//ÀÌ¹ÌÁö
		_emSet.ani = _2Rani;		//¾Ö´Ï
		_emSet.ani->stop();			//¾Ö´Ï ½ºÅ¾

		//Ã»·Ï(¼¾¸®´ÙÀÌ)
		if (_color == 0)
		{
			_emSet.chName = "Jerry";	//ÀÌ¸§

			_emStatus.punch = 2;	//ÆİÄ¡
			_emStatus.kick = 5;	//Å±
			_emStatus.weapon = 5;	//¹«±â
			_emStatus.power = 11;	//Èû
			_emStatus.agility = 6;	//¹ÎÃ¸
			_emStatus.guard = 5;	//°¡µå
			_emStatus.endure = 5;	//¸ËÁı
			_emStatus.energy = 8;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 13;	//Ã¼·Â
			_emStatus.money = 50;	//µ· µå¶ø

		}
		//ºĞÈ«(»çÄ«½´Äí)
		if (_color == 1)
		{
			_emSet.chName = "Biff";		//ÀÌ¸§

			_emStatus.punch = 8;	//ÆİÄ¡
			_emStatus.kick = 5;	//Å±
			_emStatus.weapon = 6;	//¹«±â
			_emStatus.power = 18;	//Èû
			_emStatus.agility = 7;	//¹ÎÃ¸
			_emStatus.guard = 4;	//°¡µå
			_emStatus.endure = 11;	//¸ËÁı
			_emStatus.energy = 7;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 12;	//Ã¼·Â
			_emStatus.money = 55;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(252, 116, 180));//ºĞÈ« Ã¼ÀÎÁö
		}
		//¿¬µÎ(´©¸¶¿ÀÄ«)
		if (_color == 2)
		{
			_emSet.chName = "Nick";		//ÀÌ¸§

			_emStatus.punch = 5;	//ÆİÄ¡
			_emStatus.kick = 11;	//Å±
			_emStatus.weapon = 9;	//¹«±â
			_emStatus.power = 18;	//Èû
			_emStatus.agility = 7;	//¹ÎÃ¸
			_emStatus.guard = 12;	//°¡µå
			_emStatus.endure = 8;	//¸ËÁı
			_emStatus.energy = 10;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 60;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(128, 208, 16));//¿¬µÎ·Î Ã¼ÀÎÁö
		}
		//³ë¶û(È£½ÃÄí»ç)
		if (_color == 3)
		{
			_emSet.chName = "Steve";		//ÀÌ¸§

			_emStatus.punch = 12;	//ÆİÄ¡
			_emStatus.kick = 12;	//Å±
			_emStatus.weapon = 12;	//¹«±â
			_emStatus.power = 24;	//Èû
			_emStatus.agility = 10;	//¹ÎÃ¸
			_emStatus.guard = 11;	//°¡µå
			_emStatus.endure = 14;	//¸ËÁı
			_emStatus.energy = 14;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 75;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(240, 188, 60));//³ë¶ûÀ¸·Î Ã¼ÀÎÁö
		}
		//È¸»ö(ÇÏÄíÅ¸°¡)
		if (_color == 4)
		{
			_emSet.chName = "Marco";		//ÀÌ¸§

			_emStatus.punch = 16;	//ÆİÄ¡
			_emStatus.kick = 16;	//Å±
			_emStatus.weapon = 13;	//¹«±â
			_emStatus.power = 27;	//Èû
			_emStatus.agility = 14;	//¹ÎÃ¸
			_emStatus.guard = 15;	//°¡µå
			_emStatus.endure = 13;	//¸ËÁı
			_emStatus.energy = 13;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 90;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(116, 116, 116));//È¸»öÀ¸·Î Ã¼ÀÎÁö
		}
		//»¡°­(¸¶Å¸°¡¿Í)
		if (_color == 5)
		{
			_emSet.chName = "Morty";		//ÀÌ¸§

			_emStatus.punch = 14;	//ÆİÄ¡
			_emStatus.kick = 20;	//Å±
			_emStatus.weapon = 18;	//¹«±â
			_emStatus.power = 24;	//Èû
			_emStatus.agility = 19;	//¹ÎÃ¸
			_emStatus.guard = 16;	//°¡µå
			_emStatus.endure = 20;	//¸ËÁı
			_emStatus.energy = 14;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 100;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//»¡°­À¸·Î Ã¼ÀÎÁö
		}
		//ÃÊ·Ï(È£·á)
		if (_color == 6)
		{
			_emSet.chName = "Wang";		//ÀÌ¸§

			_emStatus.punch = 21;	//ÆİÄ¡
			_emStatus.kick = 20;	//Å±
			_emStatus.weapon = 15;	//¹«±â
			_emStatus.power = 27;	//Èû
			_emStatus.agility = 19;	//¹ÎÃ¸
			_emStatus.guard = 21;	//°¡µå
			_emStatus.endure = 18;	//¸ËÁı
			_emStatus.energy = 21;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 120;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//ÃÊ·ÏÀ¸·Î Ã¼ÀÎÁö
		}
		//³²»ö(Å¸´Ï¹Ù³ª)
		if (_color == 7)
		{
			_emSet.chName = "Luke";		//ÀÌ¸§

			_emStatus.punch = 20;	//ÆİÄ¡
			_emStatus.kick = 18;	//Å±
			_emStatus.weapon = 23;	//¹«±â
			_emStatus.power = 31;	//Èû
			_emStatus.agility = 20;	//¹ÎÃ¸
			_emStatus.guard = 20;	//°¡µå
			_emStatus.endure = 21;	//¸ËÁı
			_emStatus.energy = 21;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 125;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(24, 60, 92));//³²»öÀ¸·Î Ã¼ÀÎÁö
		}
		//ÁÖÈ²(·¹ÀÌÈ£)
		if (_color == 8)
		{
			_emSet.chName = "Tonto";		//ÀÌ¸§

			_emStatus.punch = 24;	//ÆİÄ¡
			_emStatus.kick = 25;	//Å±
			_emStatus.weapon = 21;	//¹«±â
			_emStatus.power = 29;	//Èû
			_emStatus.agility = 24;	//¹ÎÃ¸
			_emStatus.guard = 25;	//°¡µå
			_emStatus.endure = 23;	//¸ËÁı
			_emStatus.energy = 21;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 150;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(216, 40, 0));//ÁÖÈ²À¸·Î Ã¼ÀÎÁö
		}

		_emST = IDLE;	//»óÅÂ

		_emState.jump = false;	//Á¡ÇÁ¿©ºÎ
		_left = false;	//¿ŞÂÊ¿©ºÎ
		_emState.run = false;	//´Ş¸®±â ¿©ºÎ

		_emSet.CH = pt;				//À§Ä¡
		_emSet.ch = MakeRct(_emSet.CH.x - 33, _emSet.CH.y - 130, 66, 130);	//ÇÇ°İ¹üÀ§

	}
	//Å¸ÀÔ5
	if (_type == 5)
	{

		_walk = IMG->find("5-°È±â");
		_run = IMG->find("5-´Ş¸®±â");
		_punch = IMG->find("5-ÆİÄ¡");
		_kick = IMG->find("5-Å±");
		_uppercut = IMG->find("5-¾îÆÛÄÆ");
		_highkick = IMG->find("5-ÇÏÀÌÅ±");
		_run_punch = IMG->find("5-´Ş¸®±âÆİÄ¡");
		_jump = IMG->find("5-Á¡ÇÁ");
		_jumpkick = IMG->find("5-Á¡ÇÁÅ±");
		_defend = IMG->find("5-¹æ¾î");
		_beatup = IMG->find("5-ÇÇ°İ");
		_ko = IMG->find("5-KO");
		_stick_pipe = IMG->find("5-½ºÆ½");
		_chain = IMG->find("5-Ã¼ÀÎ");
		_knuckles = IMG->find("5-³ÊÅ¬");
		_rock = IMG->find("5-µ¹");
		_lift_trashcan = IMG->find("5-¾²·¹±â");
		_lift_crate = IMG->find("5-¹Ú½º");
		_lift_tire = IMG->find("5-Å¸ÀÌ¾î");
		_lift_human = IMG->find("5-»ç¶÷");
		_throw_stick_pipe = IMG->find("5-½ºÆ½´øÁö±â");
		_throw_chain = IMG->find("5-Ã¼ÀÎ´øÁö±â");
		_throw_knuckles = IMG->find("5-³ÊÅ¬´øÁö±â");
		_throw_rock = IMG->find("5-µ¹´øÁö±â");
		_throw_trashcan = IMG->find("5-¾²·¹±â´øÁö±â");
		_throw_crate = IMG->find("5-¹Ú½º´øÁö±â");
		_throw_tire = IMG->find("5-Å¸ÀÌ¾î´øÁö±â");
		_throw_human = IMG->find("5-»ç¶÷´øÁö±â");

		_emSet.img = _run;			//ÀÌ¹ÌÁö
		_emSet.ani = _2Rani;		//¾Ö´Ï
		_emSet.ani->stop();			//¾Ö´Ï ½ºÅ¾

		//Ã»·Ï(¼¾¸®´ÙÀÌ)
		if (_color == 0)
		{
			_emSet.chName = "Cary";	//ÀÌ¸§

			_emStatus.punch = 4;	//ÆİÄ¡
			_emStatus.kick = 5;	//Å±
			_emStatus.weapon = 6;	//¹«±â
			_emStatus.power = 2;	//Èû
			_emStatus.agility = 15;	//¹ÎÃ¸
			_emStatus.guard = 6;	//°¡µå
			_emStatus.endure = 3;	//¸ËÁı
			_emStatus.energy = 8;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 9;	//Ã¼·Â
			_emStatus.money = 50;	//µ· µå¶ø

		}
		//ºĞÈ«(»çÄ«½´Äí)
		if (_color == 1)
		{
			_emSet.chName = "Drake";		//ÀÌ¸§

			_emStatus.punch = 10;	//ÆİÄ¡
			_emStatus.kick = 5;	//Å±
			_emStatus.weapon = 7;	//¹«±â
			_emStatus.power = 9;	//Èû
			_emStatus.agility = 16;	//¹ÎÃ¸
			_emStatus.guard = 5;	//°¡µå
			_emStatus.endure = 9;	//¸ËÁı
			_emStatus.energy = 7;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 8;	//Ã¼·Â
			_emStatus.money = 55;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(252, 116, 180));//ºĞÈ« Ã¼ÀÎÁö
		}
		//¿¬µÎ(´©¸¶¿ÀÄ«)
		if (_color == 2)
		{
			_emSet.chName = "Brad";		//ÀÌ¸§

			_emStatus.punch = 7;	//ÆİÄ¡
			_emStatus.kick = 11;	//Å±
			_emStatus.weapon = 10;	//¹«±â
			_emStatus.power = 9;	//Èû
			_emStatus.agility = 16;	//¹ÎÃ¸
			_emStatus.guard = 13;	//°¡µå
			_emStatus.endure = 6;	//¸ËÁı
			_emStatus.energy = 10;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 12;	//Ã¼·Â
			_emStatus.money = 60;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(128, 208, 16));//¿¬µÎ·Î Ã¼ÀÎÁö
		}
		//³ë¶û(È£½ÃÄí»ç)
		if (_color == 3)
		{
			_emSet.chName = "Doug";		//ÀÌ¸§

			_emStatus.punch = 14;	//ÆİÄ¡
			_emStatus.kick = 12;	//Å±
			_emStatus.weapon = 13;	//¹«±â
			_emStatus.power = 15;	//Èû
			_emStatus.agility = 19;	//¹ÎÃ¸
			_emStatus.guard = 12;	//°¡µå
			_emStatus.endure = 12;	//¸ËÁı
			_emStatus.energy = 14;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 75;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(240, 188, 60));//³ë¶ûÀ¸·Î Ã¼ÀÎÁö
		}
		//È¸»ö(ÇÏÄíÅ¸°¡)
		if (_color == 4)
		{
			_emSet.chName = "Vinny";		//ÀÌ¸§

			_emStatus.punch = 18;	//ÆİÄ¡
			_emStatus.kick = 16;	//Å±
			_emStatus.weapon = 14;	//¹«±â
			_emStatus.power = 18;	//Èû
			_emStatus.agility = 23;	//¹ÎÃ¸
			_emStatus.guard = 16;	//°¡µå
			_emStatus.endure = 11;	//¸ËÁı
			_emStatus.energy = 13;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 90;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(116, 116, 116));//È¸»öÀ¸·Î Ã¼ÀÎÁö
		}
		//»¡°­(¸¶Å¸°¡¿Í)
		if (_color == 5)
		{
			_emSet.chName = "Berni";		//ÀÌ¸§

			_emStatus.punch = 16;	//ÆİÄ¡
			_emStatus.kick = 20;	//Å±
			_emStatus.weapon = 19;	//¹«±â
			_emStatus.power = 15;	//Èû
			_emStatus.agility = 28;	//¹ÎÃ¸
			_emStatus.guard = 17;	//°¡µå
			_emStatus.endure = 18;	//¸ËÁı
			_emStatus.energy = 14;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 100;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//»¡°­À¸·Î Ã¼ÀÎÁö
		}
		//ÃÊ·Ï(È£·á)
		if (_color == 6)
		{
			_emSet.chName = "Akbar";		//ÀÌ¸§

			_emStatus.punch = 23;	//ÆİÄ¡
			_emStatus.kick = 20;	//Å±
			_emStatus.weapon = 16;	//¹«±â
			_emStatus.power = 18;	//Èû
			_emStatus.agility = 28;	//¹ÎÃ¸
			_emStatus.guard = 22;	//°¡µå
			_emStatus.endure = 16;	//¸ËÁı
			_emStatus.energy = 21;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 120;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//ÃÊ·ÏÀ¸·Î Ã¼ÀÎÁö
		}
		//³²»ö(Å¸´Ï¹Ù³ª)
		if (_color == 7)
		{
			_emSet.chName = "Duke";		//ÀÌ¸§

			_emStatus.punch = 22;	//ÆİÄ¡
			_emStatus.kick = 18;	//Å±
			_emStatus.weapon = 24;	//¹«±â
			_emStatus.power = 22;	//Èû
			_emStatus.agility = 29;	//¹ÎÃ¸
			_emStatus.guard = 21;	//°¡µå
			_emStatus.endure = 19;	//¸ËÁı
			_emStatus.energy = 21;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 125;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(24, 60, 92));//³²»öÀ¸·Î Ã¼ÀÎÁö
		}
		//ÁÖÈ²(·¹ÀÌÈ£)
		if (_color == 8)
		{
			_emSet.chName = "Stick";		//ÀÌ¸§

			_emStatus.punch = 26;	//ÆİÄ¡
			_emStatus.kick = 25;	//Å±
			_emStatus.weapon = 22;	//¹«±â
			_emStatus.power = 20;	//Èû
			_emStatus.agility = 33;	//¹ÎÃ¸
			_emStatus.guard = 26;	//°¡µå
			_emStatus.endure = 21;	//¸ËÁı
			_emStatus.energy = 21;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 150;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(216, 40, 0));//ÁÖÈ²À¸·Î Ã¼ÀÎÁö
		}

		_emST = IDLE;	//»óÅÂ

		_emState.jump = false;	//Á¡ÇÁ¿©ºÎ
		_left = false;	//¿ŞÂÊ¿©ºÎ
		_emState.run = false;	//´Ş¸®±â ¿©ºÎ

		_emSet.CH = pt;				//À§Ä¡
		_emSet.ch = MakeRct(_emSet.CH.x - 33, _emSet.CH.y - 130, 66, 130);	//ÇÇ°İ¹üÀ§

	}
	//Å¸ÀÔ6
	if (_type == 6)
	{

		_walk = IMG->find("6-°È±â");
		_run = IMG->find("6-´Ş¸®±â");
		_punch = IMG->find("6-ÆİÄ¡");
		_kick = IMG->find("6-Å±");
		_uppercut = IMG->find("6-¾îÆÛÄÆ");
		_highkick = IMG->find("6-ÇÏÀÌÅ±");
		_run_punch = IMG->find("6-´Ş¸®±âÆİÄ¡");
		_jump = IMG->find("6-Á¡ÇÁ");
		_jumpkick = IMG->find("6-Á¡ÇÁÅ±");
		_defend = IMG->find("6-¹æ¾î");
		_beatup = IMG->find("6-ÇÇ°İ");
		_ko = IMG->find("6-KO");
		_stick_pipe = IMG->find("6-½ºÆ½");
		_chain = IMG->find("6-Ã¼ÀÎ");
		_knuckles = IMG->find("6-³ÊÅ¬");
		_rock = IMG->find("6-µ¹");
		_lift_trashcan = IMG->find("6-¾²·¹±â");
		_lift_crate = IMG->find("6-¹Ú½º");
		_lift_tire = IMG->find("6-Å¸ÀÌ¾î");
		_lift_human = IMG->find("6-»ç¶÷");
		_throw_stick_pipe = IMG->find("6-½ºÆ½´øÁö±â");
		_throw_chain = IMG->find("6-Ã¼ÀÎ´øÁö±â");
		_throw_knuckles = IMG->find("6-³ÊÅ¬´øÁö±â");
		_throw_rock = IMG->find("6-µ¹´øÁö±â");
		_throw_trashcan = IMG->find("6-¾²·¹±â´øÁö±â");
		_throw_crate = IMG->find("6-¹Ú½º´øÁö±â");
		_throw_tire = IMG->find("6-Å¸ÀÌ¾î´øÁö±â");
		_throw_human = IMG->find("6-»ç¶÷´øÁö±â");

		_emSet.img = _run;			//ÀÌ¹ÌÁö
		_emSet.ani = _2Rani;		//¾Ö´Ï
		_emSet.ani->stop();			//¾Ö´Ï ½ºÅ¾

		//Ã»·Ï(¼¾¸®´ÙÀÌ)
		if (_color == 0)
		{
			_emSet.chName = "Gary";	//ÀÌ¸§

			_emStatus.punch = 4;	//ÆİÄ¡
			_emStatus.kick = 5;	//Å±
			_emStatus.weapon = 6;	//¹«±â
			_emStatus.power = 3;	//Èû
			_emStatus.agility = 6;	//¹ÎÃ¸
			_emStatus.guard = 14;	//°¡µå
			_emStatus.endure = 3;	//¸ËÁı
			_emStatus.energy = 7;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 11;	//Ã¼·Â
			_emStatus.money = 50;	//µ· µå¶ø

		}
		//ºĞÈ«(»çÄ«½´Äí)
		if (_color == 1)
		{
			_emSet.chName = "Trip";		//ÀÌ¸§

			_emStatus.punch = 10;	//ÆİÄ¡
			_emStatus.kick = 5;	//Å±
			_emStatus.weapon = 7;	//¹«±â
			_emStatus.power = 10;	//Èû
			_emStatus.agility = 7;	//¹ÎÃ¸
			_emStatus.guard = 13;	//°¡µå
			_emStatus.endure = 9;	//¸ËÁı
			_emStatus.energy = 6;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 10;	//Ã¼·Â
			_emStatus.money = 55;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(252, 116, 180));//ºĞÈ« Ã¼ÀÎÁö
		}
		//¿¬µÎ(´©¸¶¿ÀÄ«)
		if (_color == 2)
		{
			_emSet.chName = "Matt";		//ÀÌ¸§

			_emStatus.punch = 7;	//ÆİÄ¡
			_emStatus.kick = 11;	//Å±
			_emStatus.weapon = 10;	//¹«±â
			_emStatus.power = 10;	//Èû
			_emStatus.agility = 7;	//¹ÎÃ¸
			_emStatus.guard = 21;	//°¡µå
			_emStatus.endure = 6;	//¸ËÁı
			_emStatus.energy = 9;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 60;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(128, 208, 16));//¿¬µÎ·Î Ã¼ÀÎÁö
		}
		//³ë¶û(È£½ÃÄí»ç)
		if (_color == 3)
		{
			_emSet.chName = "Greg";		//ÀÌ¸§

			_emStatus.punch = 14;	//ÆİÄ¡
			_emStatus.kick = 12;	//Å±
			_emStatus.weapon = 13;	//¹«±â
			_emStatus.power = 16;	//Èû
			_emStatus.agility = 10;	//¹ÎÃ¸
			_emStatus.guard = 20;	//°¡µå
			_emStatus.endure = 12;	//¸ËÁı
			_emStatus.energy = 13;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 75;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(240, 188, 60));//³ë¶ûÀ¸·Î Ã¼ÀÎÁö
		}
		//È¸»ö(ÇÏÄíÅ¸°¡)
		if (_color == 4)
		{
			_emSet.chName = "Mouse";		//ÀÌ¸§

			_emStatus.punch = 18;	//ÆİÄ¡
			_emStatus.kick = 16;	//Å±
			_emStatus.weapon = 14;	//¹«±â
			_emStatus.power = 19;	//Èû
			_emStatus.agility = 14;	//¹ÎÃ¸
			_emStatus.guard = 24;	//°¡µå
			_emStatus.endure = 11;	//¸ËÁı
			_emStatus.energy = 12;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 90;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(116, 116, 116));//È¸»öÀ¸·Î Ã¼ÀÎÁö
		}
		//»¡°­(¸¶Å¸°¡¿Í)
		if (_color == 5)
		{
			_emSet.chName = "Byron";		//ÀÌ¸§

			_emStatus.punch = 16;	//ÆİÄ¡
			_emStatus.kick = 20;	//Å±
			_emStatus.weapon = 19;	//¹«±â
			_emStatus.power = 16;	//Èû
			_emStatus.agility = 19;	//¹ÎÃ¸
			_emStatus.guard = 25;	//°¡µå
			_emStatus.endure = 18;	//¸ËÁı
			_emStatus.energy = 13;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 100;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//»¡°­À¸·Î Ã¼ÀÎÁö
		}
		//ÃÊ·Ï(È£·á)
		if (_color == 6)
		{
			_emSet.chName = "Juan";		//ÀÌ¸§

			_emStatus.punch = 23;	//ÆİÄ¡
			_emStatus.kick = 20;	//Å±
			_emStatus.weapon = 16;	//¹«±â
			_emStatus.power = 19;	//Èû
			_emStatus.agility = 19;	//¹ÎÃ¸
			_emStatus.guard = 30;	//°¡µå
			_emStatus.endure = 16;	//¸ËÁı
			_emStatus.energy = 20;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 120;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//ÃÊ·ÏÀ¸·Î Ã¼ÀÎÁö
		}
		//³²»ö(Å¸´Ï¹Ù³ª)
		if (_color == 7)
		{
			_emSet.chName = "Slim";		//ÀÌ¸§

			_emStatus.punch = 22;	//ÆİÄ¡
			_emStatus.kick = 18;	//Å±
			_emStatus.weapon = 24;	//¹«±â
			_emStatus.power = 23;	//Èû
			_emStatus.agility = 20;	//¹ÎÃ¸
			_emStatus.guard = 29;	//°¡µå
			_emStatus.endure = 19;	//¸ËÁı
			_emStatus.energy = 20;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 125;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(24, 60, 92));//³²»öÀ¸·Î Ã¼ÀÎÁö
		}
		//ÁÖÈ²(·¹ÀÌÈ£)
		if (_color == 8)
		{
			_emSet.chName = "Mooky";		//ÀÌ¸§

			_emStatus.punch = 26;	//ÆİÄ¡
			_emStatus.kick = 25;	//Å±
			_emStatus.weapon = 22;	//¹«±â
			_emStatus.power = 21;	//Èû
			_emStatus.agility = 24;	//¹ÎÃ¸
			_emStatus.guard = 34;	//°¡µå
			_emStatus.endure = 21;	//¸ËÁı
			_emStatus.energy = 20;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 150;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(216, 40, 0));//ÁÖÈ²À¸·Î Ã¼ÀÎÁö
		}

		_emST = IDLE;	//»óÅÂ

		_emState.jump = false;	//Á¡ÇÁ¿©ºÎ
		_left = false;	//¿ŞÂÊ¿©ºÎ
		_emState.run = false;	//´Ş¸®±â ¿©ºÎ

		_emSet.CH = pt;				//À§Ä¡
		_emSet.ch = MakeRct(_emSet.CH.x - 33, _emSet.CH.y - 130, 66, 130);	//ÇÇ°İ¹üÀ§

	}
	//Å¸ÀÔ7
	if (_type == 7)
	{

		_walk = IMG->find("7-°È±â");
		_run = IMG->find("7-´Ş¸®±â");
		_punch = IMG->find("7-ÆİÄ¡");
		_kick = IMG->find("7-Å±");
		_uppercut = IMG->find("7-¾îÆÛÄÆ");
		_highkick = IMG->find("7-ÇÏÀÌÅ±");
		_run_punch = IMG->find("7-´Ş¸®±âÆİÄ¡");
		_jump = IMG->find("7-Á¡ÇÁ");
		_jumpkick = IMG->find("7-Á¡ÇÁÅ±");
		_defend = IMG->find("7-¹æ¾î");
		_beatup = IMG->find("7-ÇÇ°İ");
		_ko = IMG->find("7-KO");
		_stick_pipe = IMG->find("7-½ºÆ½");
		_chain = IMG->find("7-Ã¼ÀÎ");
		_knuckles = IMG->find("7-³ÊÅ¬");
		_rock = IMG->find("7-µ¹");
		_lift_trashcan = IMG->find("7-¾²·¹±â");
		_lift_crate = IMG->find("7-¹Ú½º");
		_lift_tire = IMG->find("7-Å¸ÀÌ¾î");
		_lift_human = IMG->find("7-»ç¶÷");
		_throw_stick_pipe = IMG->find("7-½ºÆ½´øÁö±â");
		_throw_chain = IMG->find("7-Ã¼ÀÎ´øÁö±â");
		_throw_knuckles = IMG->find("7-³ÊÅ¬´øÁö±â");
		_throw_rock = IMG->find("7-µ¹´øÁö±â");
		_throw_trashcan = IMG->find("7-¾²·¹±â´øÁö±â");
		_throw_crate = IMG->find("7-¹Ú½º´øÁö±â");
		_throw_tire = IMG->find("7-Å¸ÀÌ¾î´øÁö±â");
		_throw_human = IMG->find("7-»ç¶÷´øÁö±â");

		_emSet.img = _run;			//ÀÌ¹ÌÁö
		_emSet.ani = _2Rani;		//¾Ö´Ï
		_emSet.ani->stop();			//¾Ö´Ï ½ºÅ¾

		//Ã»·Ï(¼¾¸®´ÙÀÌ)
		if (_color == 0)
		{
			_emSet.chName = "Harry";	//ÀÌ¸§

			_emStatus.punch = 3;	//ÆİÄ¡
			_emStatus.kick = 5;	//Å±
			_emStatus.weapon = 7;	//¹«±â
			_emStatus.power = 3;	//Èû
			_emStatus.agility = 6;	//¹ÎÃ¸
			_emStatus.guard = 5;	//°¡µå
			_emStatus.endure = 13;	//¸ËÁı
			_emStatus.energy = 7;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 9;	//Ã¼·Â
			_emStatus.money = 50;	//µ· µå¶ø

		}
		//ºĞÈ«(»çÄ«½´Äí)
		if (_color == 1)
		{
			_emSet.chName = "Tyler";		//ÀÌ¸§

			_emStatus.punch = 9;	//ÆİÄ¡
			_emStatus.kick = 5;	//Å±
			_emStatus.weapon = 8;	//¹«±â
			_emStatus.power = 10;	//Èû
			_emStatus.agility = 7;	//¹ÎÃ¸
			_emStatus.guard = 4;	//°¡µå
			_emStatus.endure = 19;	//¸ËÁı
			_emStatus.energy = 6;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 8;	//Ã¼·Â
			_emStatus.money = 55;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(252, 116, 180));//ºĞÈ« Ã¼ÀÎÁö
		}
		//¿¬µÎ(´©¸¶¿ÀÄ«)
		if (_color == 2)
		{
			_emSet.chName = "Curt";		//ÀÌ¸§

			_emStatus.punch = 6;	//ÆİÄ¡
			_emStatus.kick = 11;	//Å±
			_emStatus.weapon = 11;	//¹«±â
			_emStatus.power = 10;	//Èû
			_emStatus.agility = 7;	//¹ÎÃ¸
			_emStatus.guard = 12;	//°¡µå
			_emStatus.endure = 16;	//¸ËÁı
			_emStatus.energy = 9;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 12;	//Ã¼·Â
			_emStatus.money = 60;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(128, 208, 16));//¿¬µÎ·Î Ã¼ÀÎÁö
		}
		//³ë¶û(È£½ÃÄí»ç)
		if (_color == 3)
		{
			_emSet.chName = "Peter";		//ÀÌ¸§

			_emStatus.punch = 13;	//ÆİÄ¡
			_emStatus.kick = 12;	//Å±
			_emStatus.weapon = 14;	//¹«±â
			_emStatus.power = 16;	//Èû
			_emStatus.agility = 10;	//¹ÎÃ¸
			_emStatus.guard = 11;	//°¡µå
			_emStatus.endure = 22;	//¸ËÁı
			_emStatus.energy = 13;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 75;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(240, 188, 60));//³ë¶ûÀ¸·Î Ã¼ÀÎÁö
		}
		//È¸»ö(ÇÏÄíÅ¸°¡)
		if (_color == 4)
		{
			_emSet.chName = "Max";		//ÀÌ¸§

			_emStatus.punch = 17;	//ÆİÄ¡
			_emStatus.kick = 16;	//Å±
			_emStatus.weapon = 15;	//¹«±â
			_emStatus.power = 19;	//Èû
			_emStatus.agility = 14;	//¹ÎÃ¸
			_emStatus.guard = 15;	//°¡µå
			_emStatus.endure = 21;	//¸ËÁı
			_emStatus.energy = 12;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 90;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(116, 116, 116));//È¸»öÀ¸·Î Ã¼ÀÎÁö
		}
		//»¡°­(¸¶Å¸°¡¿Í)
		if (_color == 5)
		{
			_emSet.chName = "Howie";		//ÀÌ¸§

			_emStatus.punch = 15;	//ÆİÄ¡
			_emStatus.kick = 20;	//Å±
			_emStatus.weapon = 20;	//¹«±â
			_emStatus.power = 16;	//Èû
			_emStatus.agility = 19;	//¹ÎÃ¸
			_emStatus.guard = 16;	//°¡µå
			_emStatus.endure = 28;	//¸ËÁı
			_emStatus.energy = 13;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 100;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//»¡°­À¸·Î Ã¼ÀÎÁö
		}
		//ÃÊ·Ï(È£·á)
		if (_color == 6)
		{
			_emSet.chName = "Andre";		//ÀÌ¸§

			_emStatus.punch = 22;	//ÆİÄ¡
			_emStatus.kick = 20;	//Å±
			_emStatus.weapon = 17;	//¹«±â
			_emStatus.power = 19;	//Èû
			_emStatus.agility = 19;	//¹ÎÃ¸
			_emStatus.guard = 21;	//°¡µå
			_emStatus.endure = 26;	//¸ËÁı
			_emStatus.energy = 20;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 120;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//ÃÊ·ÏÀ¸·Î Ã¼ÀÎÁö
		}
		//³²»ö(Å¸´Ï¹Ù³ª)
		if (_color == 7)
		{
			_emSet.chName = "Jed";		//ÀÌ¸§

			_emStatus.punch = 21;	//ÆİÄ¡
			_emStatus.kick = 18;	//Å±
			_emStatus.weapon = 25;	//¹«±â
			_emStatus.power = 23;	//Èû
			_emStatus.agility = 20;	//¹ÎÃ¸
			_emStatus.guard = 20;	//°¡µå
			_emStatus.endure = 29;	//¸ËÁı
			_emStatus.energy = 20;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 125;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(24, 60, 92));//³²»öÀ¸·Î Ã¼ÀÎÁö
		}
		//ÁÖÈ²(·¹ÀÌÈ£)
		if (_color == 8)
		{
			_emSet.chName = "Snake";		//ÀÌ¸§

			_emStatus.punch = 25;	//ÆİÄ¡
			_emStatus.kick = 25;	//Å±
			_emStatus.weapon = 23;	//¹«±â
			_emStatus.power = 21;	//Èû
			_emStatus.agility = 24;	//¹ÎÃ¸
			_emStatus.guard = 25;	//°¡µå
			_emStatus.endure = 31;	//¸ËÁı
			_emStatus.energy = 20;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 150;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(216, 40, 0));//ÁÖÈ²À¸·Î Ã¼ÀÎÁö
		}

		_emST = IDLE;	//»óÅÂ

		_emState.jump = false;	//Á¡ÇÁ¿©ºÎ
		_left = false;	//¿ŞÂÊ¿©ºÎ
		_emState.run = false;	//´Ş¸®±â ¿©ºÎ

		_emSet.CH = pt;				//À§Ä¡
		_emSet.ch = MakeRct(_emSet.CH.x - 33, _emSet.CH.y - 130, 66, 130);	//ÇÇ°İ¹üÀ§

	}
	//Å¸ÀÔ8
	if (_type == 8)
	{

		_walk = IMG->find("8-°È±â");
		_run = IMG->find("8-´Ş¸®±â");
		_punch = IMG->find("8-ÆİÄ¡");
		_kick = IMG->find("8-Å±");
		_uppercut = IMG->find("8-¾îÆÛÄÆ");
		_highkick = IMG->find("8-ÇÏÀÌÅ±");
		_run_punch = IMG->find("8-´Ş¸®±âÆİÄ¡");
		_jump = IMG->find("8-Á¡ÇÁ");
		_jumpkick = IMG->find("8-Á¡ÇÁÅ±");
		_defend = IMG->find("8-¹æ¾î");
		_beatup = IMG->find("8-ÇÇ°İ");
		_ko = IMG->find("8-KO");
		_stick_pipe = IMG->find("8-½ºÆ½");
		_chain = IMG->find("8-Ã¼ÀÎ");
		_knuckles = IMG->find("8-³ÊÅ¬");
		_rock = IMG->find("8-µ¹");
		_lift_trashcan = IMG->find("8-¾²·¹±â");
		_lift_crate = IMG->find("8-¹Ú½º");
		_lift_tire = IMG->find("8-Å¸ÀÌ¾î");
		_lift_human = IMG->find("8-»ç¶÷");
		_throw_stick_pipe = IMG->find("8-½ºÆ½´øÁö±â");
		_throw_chain = IMG->find("8-Ã¼ÀÎ´øÁö±â");
		_throw_knuckles = IMG->find("8-³ÊÅ¬´øÁö±â");
		_throw_rock = IMG->find("8-µ¹´øÁö±â");
		_throw_trashcan = IMG->find("8-¾²·¹±â´øÁö±â");
		_throw_crate = IMG->find("8-¹Ú½º´øÁö±â");
		_throw_tire = IMG->find("8-Å¸ÀÌ¾î´øÁö±â");
		_throw_human = IMG->find("8-»ç¶÷´øÁö±â");

		_emSet.img = _run;			//ÀÌ¹ÌÁö
		_emSet.ani = _2Rani;		//¾Ö´Ï
		_emSet.ani->stop();			//¾Ö´Ï ½ºÅ¾

		//Ã»·Ï(¼¾¸®´ÙÀÌ)
		if (_color == 0)
		{
			_emSet.chName = "Perry";	//ÀÌ¸§

			_emStatus.punch = 3;	//ÆİÄ¡
			_emStatus.kick = 6;	//Å±
			_emStatus.weapon = 7;	//¹«±â
			_emStatus.power = 2;	//Èû
			_emStatus.agility = 5;	//¹ÎÃ¸
			_emStatus.guard = 4;	//°¡µå
			_emStatus.endure = 4;	//¸ËÁı
			_emStatus.energy = 17;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 11;	//Ã¼·Â
			_emStatus.money = 50;	//µ· µå¶ø

		}
		//ºĞÈ«(»çÄ«½´Äí)
		if (_color == 1)
		{
			_emSet.chName = "Grant";		//ÀÌ¸§

			_emStatus.punch = 9;	//ÆİÄ¡
			_emStatus.kick = 6;	//Å±
			_emStatus.weapon = 8;	//¹«±â
			_emStatus.power = 9;	//Èû
			_emStatus.agility = 6;	//¹ÎÃ¸
			_emStatus.guard = 3;	//°¡µå
			_emStatus.endure = 10;	//¸ËÁı
			_emStatus.energy = 16;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 10;	//Ã¼·Â
			_emStatus.money = 55;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(252, 116, 180));//ºĞÈ« Ã¼ÀÎÁö
		}
		//¿¬µÎ(´©¸¶¿ÀÄ«)
		if (_color == 2)
		{
			_emSet.chName = "Mike";		//ÀÌ¸§

			_emStatus.punch = 6;	//ÆİÄ¡
			_emStatus.kick = 12;	//Å±
			_emStatus.weapon = 11;	//¹«±â
			_emStatus.power = 9;	//Èû
			_emStatus.agility = 6;	//¹ÎÃ¸
			_emStatus.guard = 11;	//°¡µå
			_emStatus.endure = 7;	//¸ËÁı
			_emStatus.energy = 19;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 60;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(128, 208, 16));//¿¬µÎ·Î Ã¼ÀÎÁö
		}
		//³ë¶û(È£½ÃÄí»ç)
		if (_color == 3)
		{
			_emSet.chName = "Bobby";		//ÀÌ¸§

			_emStatus.punch = 13;	//ÆİÄ¡
			_emStatus.kick = 13;	//Å±
			_emStatus.weapon = 14;	//¹«±â
			_emStatus.power = 15;	//Èû
			_emStatus.agility = 9;	//¹ÎÃ¸
			_emStatus.guard = 10;	//°¡µå
			_emStatus.endure = 13;	//¸ËÁı
			_emStatus.energy = 23;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 75;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(240, 188, 60));//³ë¶ûÀ¸·Î Ã¼ÀÎÁö
		}
		//È¸»ö(ÇÏÄíÅ¸°¡)
		if (_color == 4)
		{
			_emSet.chName = "Manny";		//ÀÌ¸§

			_emStatus.punch = 17;	//ÆİÄ¡
			_emStatus.kick = 17;	//Å±
			_emStatus.weapon = 15;	//¹«±â
			_emStatus.power = 18;	//Èû
			_emStatus.agility = 13;	//¹ÎÃ¸
			_emStatus.guard = 14;	//°¡µå
			_emStatus.endure = 12;	//¸ËÁı
			_emStatus.energy = 22;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 90;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(116, 116, 116));//È¸»öÀ¸·Î Ã¼ÀÎÁö
		}
		//»¡°­(¸¶Å¸°¡¿Í)
		if (_color == 5)
		{
			_emSet.chName = "Waldo";		//ÀÌ¸§

			_emStatus.punch = 15;	//ÆİÄ¡
			_emStatus.kick = 21;	//Å±
			_emStatus.weapon = 20;	//¹«±â
			_emStatus.power = 15;	//Èû
			_emStatus.agility = 18;	//¹ÎÃ¸
			_emStatus.guard = 15;	//°¡µå
			_emStatus.endure = 19;	//¸ËÁı
			_emStatus.energy = 23;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 100;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//»¡°­À¸·Î Ã¼ÀÎÁö
		}
		//ÃÊ·Ï(È£·á)
		if (_color == 6)
		{
			_emSet.chName = "Hans";		//ÀÌ¸§

			_emStatus.punch = 22;	//ÆİÄ¡
			_emStatus.kick = 21;	//Å±
			_emStatus.weapon = 17;	//¹«±â
			_emStatus.power = 18;	//Èû
			_emStatus.agility = 18;	//¹ÎÃ¸
			_emStatus.guard = 20;	//°¡µå
			_emStatus.endure = 17;	//¸ËÁı
			_emStatus.energy = 30;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 120;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//ÃÊ·ÏÀ¸·Î Ã¼ÀÎÁö
		}
		//³²»ö(Å¸´Ï¹Ù³ª)
		if (_color == 7)
		{
			_emSet.chName = "Dusty";		//ÀÌ¸§

			_emStatus.punch = 21;	//ÆİÄ¡
			_emStatus.kick = 19;	//Å±
			_emStatus.weapon = 25;	//¹«±â
			_emStatus.power = 22;	//Èû
			_emStatus.agility = 19;	//¹ÎÃ¸
			_emStatus.guard = 19;	//°¡µå
			_emStatus.endure = 20;	//¸ËÁı
			_emStatus.energy = 30;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 125;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(24, 60, 92));//³²»öÀ¸·Î Ã¼ÀÎÁö
		}
		//ÁÖÈ²(·¹ÀÌÈ£)
		if (_color == 8)
		{
			_emSet.chName = "Sting";		//ÀÌ¸§

			_emStatus.punch = 25;	//ÆİÄ¡
			_emStatus.kick = 26;	//Å±
			_emStatus.weapon = 23;	//¹«±â
			_emStatus.power = 20;	//Èû
			_emStatus.agility = 23;	//¹ÎÃ¸
			_emStatus.guard = 24;	//°¡µå
			_emStatus.endure = 22;	//¸ËÁı
			_emStatus.energy = 30;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 150;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(216, 40, 0));//ÁÖÈ²À¸·Î Ã¼ÀÎÁö
		}

		_emST = IDLE;	//»óÅÂ

		_emState.jump = false;	//Á¡ÇÁ¿©ºÎ
		_left = false;	//¿ŞÂÊ¿©ºÎ
		_emState.run = false;	//´Ş¸®±â ¿©ºÎ

		_emSet.CH = pt;				//À§Ä¡
		_emSet.ch = MakeRct(_emSet.CH.x - 33, _emSet.CH.y - 130, 66, 130);	//ÇÇ°İ¹üÀ§

	}
	//Å¸ÀÔ9
	if (_type == 9)
	{

		_walk = IMG->find("9-°È±â");
		_run = IMG->find("9-´Ş¸®±â");
		_punch = IMG->find("9-ÆİÄ¡");
		_kick = IMG->find("9-Å±");
		_uppercut = IMG->find("9-¾îÆÛÄÆ");
		_highkick = IMG->find("9-ÇÏÀÌÅ±");
		_run_punch = IMG->find("9-´Ş¸®±âÆİÄ¡");
		_jump = IMG->find("9-Á¡ÇÁ");
		_jumpkick = IMG->find("9-Á¡ÇÁÅ±");
		_defend = IMG->find("9-¹æ¾î");
		_beatup = IMG->find("9-ÇÇ°İ");
		_ko = IMG->find("9-KO");
		_stick_pipe = IMG->find("9-½ºÆ½");
		_chain = IMG->find("9-Ã¼ÀÎ");
		_knuckles = IMG->find("9-³ÊÅ¬");
		_rock = IMG->find("9-µ¹");
		_lift_trashcan = IMG->find("9-¾²·¹±â");
		_lift_crate = IMG->find("9-¹Ú½º");
		_lift_tire = IMG->find("9-Å¸ÀÌ¾î");
		_lift_human = IMG->find("9-»ç¶÷");
		_throw_stick_pipe = IMG->find("9-½ºÆ½´øÁö±â");
		_throw_chain = IMG->find("9-Ã¼ÀÎ´øÁö±â");
		_throw_knuckles = IMG->find("9-³ÊÅ¬´øÁö±â");
		_throw_rock = IMG->find("9-µ¹´øÁö±â");
		_throw_trashcan = IMG->find("9-¾²·¹±â´øÁö±â");
		_throw_crate = IMG->find("9-¹Ú½º´øÁö±â");
		_throw_tire = IMG->find("9-Å¸ÀÌ¾î´øÁö±â");
		_throw_human = IMG->find("9-»ç¶÷´øÁö±â");

		_emSet.img = _run;			//ÀÌ¹ÌÁö
		_emSet.ani = _2Rani;		//¾Ö´Ï
		_emSet.ani->stop();			//¾Ö´Ï ½ºÅ¾

		//Ã»·Ï(¼¾¸®´ÙÀÌ)
		if (_color == 0)
		{
			_emSet.chName = "Ralph";	//ÀÌ¸§

			_emStatus.punch = 3;	//ÆİÄ¡
			_emStatus.kick = 6;	//Å±
			_emStatus.weapon = 6;	//¹«±â
			_emStatus.power = 2;	//Èû
			_emStatus.agility = 5;	//¹ÎÃ¸
			_emStatus.guard = 4;	//°¡µå
			_emStatus.endure = 4;	//¸ËÁı
			_emStatus.energy = 9;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 50;	//µ· µå¶ø

		}
		//ºĞÈ«(»çÄ«½´Äí)
		if (_color == 1)
		{
			_emSet.chName = "Clark";		//ÀÌ¸§

			_emStatus.punch = 9;	//ÆİÄ¡
			_emStatus.kick = 6;	//Å±
			_emStatus.weapon = 7;	//¹«±â
			_emStatus.power = 9;	//Èû
			_emStatus.agility = 6;	//¹ÎÃ¸
			_emStatus.guard = 3;	//°¡µå
			_emStatus.endure = 10;	//¸ËÁı
			_emStatus.energy = 8;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 55;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(252, 116, 180));//ºĞÈ« Ã¼ÀÎÁö
		}
		//¿¬µÎ(´©¸¶¿ÀÄ«)
		if (_color == 2)
		{
			_emSet.chName = "Jake";		//ÀÌ¸§

			_emStatus.punch = 6;	//ÆİÄ¡
			_emStatus.kick = 12;	//Å±
			_emStatus.weapon = 10;	//¹«±â
			_emStatus.power = 9;	//Èû
			_emStatus.agility = 6;	//¹ÎÃ¸
			_emStatus.guard = 11;	//°¡µå
			_emStatus.endure = 7;	//¸ËÁı
			_emStatus.energy = 11;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 60;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(128, 208, 16));//¿¬µÎ·Î Ã¼ÀÎÁö
		}
		//³ë¶û(È£½ÃÄí»ç)
		if (_color == 3)
		{
			_emSet.chName = "Brady";		//ÀÌ¸§

			_emStatus.punch = 13;	//ÆİÄ¡
			_emStatus.kick = 13;	//Å±
			_emStatus.weapon = 13;	//¹«±â
			_emStatus.power = 15;	//Èû
			_emStatus.agility = 9;	//¹ÎÃ¸
			_emStatus.guard = 10;	//°¡µå
			_emStatus.endure = 13;	//¸ËÁı
			_emStatus.energy = 15;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 75;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(240, 188, 60));//³ë¶ûÀ¸·Î Ã¼ÀÎÁö
		}
		//È¸»ö(ÇÏÄíÅ¸°¡)
		if (_color == 4)
		{
			_emSet.chName = "Louie";		//ÀÌ¸§

			_emStatus.punch = 17;	//ÆİÄ¡
			_emStatus.kick = 17;	//Å±
			_emStatus.weapon = 14;	//¹«±â
			_emStatus.power = 18;	//Èû
			_emStatus.agility = 13;	//¹ÎÃ¸
			_emStatus.guard = 14;	//°¡µå
			_emStatus.endure = 12;	//¸ËÁı
			_emStatus.energy = 14;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 90;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(116, 116, 116));//È¸»öÀ¸·Î Ã¼ÀÎÁö
		}
		//»¡°­(¸¶Å¸°¡¿Í)
		if (_color == 5)
		{
			_emSet.chName = "Linus";		//ÀÌ¸§

			_emStatus.punch = 15;	//ÆİÄ¡
			_emStatus.kick = 21;	//Å±
			_emStatus.weapon = 19;	//¹«±â
			_emStatus.power = 15;	//Èû
			_emStatus.agility = 18;	//¹ÎÃ¸
			_emStatus.guard = 15;	//°¡µå
			_emStatus.endure = 19;	//¸ËÁı
			_emStatus.energy = 15;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 100;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//»¡°­À¸·Î Ã¼ÀÎÁö
		}
		//ÃÊ·Ï(È£·á)
		if (_color == 6)
		{
			_emSet.chName = "Lars";		//ÀÌ¸§

			_emStatus.punch = 22;	//ÆİÄ¡
			_emStatus.kick = 21;	//Å±
			_emStatus.weapon = 16;	//¹«±â
			_emStatus.power = 18;	//Èû
			_emStatus.agility = 18;	//¹ÎÃ¸
			_emStatus.guard = 20;	//°¡µå
			_emStatus.endure = 17;	//¸ËÁı
			_emStatus.energy = 22;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 120;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//ÃÊ·ÏÀ¸·Î Ã¼ÀÎÁö
		}
		//³²»ö(Å¸´Ï¹Ù³ª)
		if (_color == 7)
		{
			_emSet.chName = "Merle";		//ÀÌ¸§

			_emStatus.punch = 21;	//ÆİÄ¡
			_emStatus.kick = 19;	//Å±
			_emStatus.weapon = 24;	//¹«±â
			_emStatus.power = 22;	//Èû
			_emStatus.agility = 19;	//¹ÎÃ¸
			_emStatus.guard = 19;	//°¡µå
			_emStatus.endure = 20;	//¸ËÁı
			_emStatus.energy = 22;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 125;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(24, 60, 92));//³²»öÀ¸·Î Ã¼ÀÎÁö
		}
		//ÁÖÈ²(·¹ÀÌÈ£)
		if (_color == 8)
		{
			_emSet.chName = "Ziggy";		//ÀÌ¸§

			_emStatus.punch = 25;	//ÆİÄ¡
			_emStatus.kick = 26;	//Å±
			_emStatus.weapon = 22;	//¹«±â
			_emStatus.power = 20;	//Èû
			_emStatus.agility = 23;	//¹ÎÃ¸
			_emStatus.guard = 24;	//°¡µå
			_emStatus.endure = 22;	//¸ËÁı
			_emStatus.energy = 22;	//±â·Â
			_emStatus.hp = _emStatus.maxHP = 14;	//Ã¼·Â
			_emStatus.money = 150;	//µ· µå¶ø

			//_emSet.img->setTransColor(RGB(0, 232, 216), RGB(216, 40, 0));//ÁÖÈ²À¸·Î Ã¼ÀÎÁö
		}

		_emST = IDLE;	//»óÅÂ

		_emState.jump = false;	//Á¡ÇÁ¿©ºÎ
		_left = false;	//¿ŞÂÊ¿©ºÎ
		_emState.run = false;	//´Ş¸®±â ¿©ºÎ

		_emSet.CH = pt;				//À§Ä¡
		_emSet.ch = MakeRct(_emSet.CH.x - 33, _emSet.CH.y - 130, 66, 130);	//ÇÇ°İ¹üÀ§

	}
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
}

void enemy::render()
{
	//·»´õ ¶§ »ö»óº¯°æ½ÃÅ°µµ·Ï ÇÕ½Ã´Ù
	//¾Ö´Ï·»´õZ
	_emSet.img->aniRender(getMemDC(), pos.x - 316 / 2, pos.y - 408 / 2, _emSet.ani);
	if (_color != 0)
	{
		if (_color == 1) _emSet.img->setTransColor(RGB(0, 232, 216), RGB(252, 116, 180));//ºĞÈ« Ã¼ÀÎÁö
		else if (_color == 2) _emSet.img->setTransColor(RGB(0, 232, 216), RGB(128, 208, 16));//¿¬µÎ·Î Ã¼ÀÎÁö
		else if (_color == 3) _emSet.img->setTransColor(RGB(0, 232, 216), RGB(240, 188, 60));//³ë¶ûÀ¸·Î Ã¼ÀÎÁö
		else if (_color == 4) _emSet.img->setTransColor(RGB(0, 232, 216), RGB(116, 116, 116));//È¸»öÀ¸·Î Ã¼ÀÎÁö
		else if (_color == 5) _emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//»¡°­À¸·Î Ã¼ÀÎÁö
		else if (_color == 6) _emSet.img->setTransColor(RGB(0, 232, 216), RGB(124, 8, 0));//ÃÊ·ÏÀ¸·Î Ã¼ÀÎÁö
		else if (_color == 7) _emSet.img->setTransColor(RGB(0, 232, 216), RGB(24, 60, 92));//³²»öÀ¸·Î Ã¼ÀÎÁö
		else if (_color == 8) _emSet.img->setTransColor(RGB(0, 232, 216), RGB(216, 40, 0));//ÁÖÈ²À¸·Î Ã¼ÀÎÁö
	}
}


void enemy::ani1Set()
{
	_1Rani = new animation;
	_1Rani->init(316, 408, 316, 204);
	int _1Right[] = { 0 };
	_1Rani->setPlaylist(_1Right, 1, false);
	_1Rani->setFPS(1);

	_1Lani = new animation;
	_1Lani->init(316, 408, 316, 204);
	int _1Left[] = { 1 };
	_1Lani->setPlaylist(_1Left, 1, false);
	_1Lani->setFPS(1);

}

void enemy::ani2Set()
{
	int _2Right[] = { 0,1 };
	int _2Left[] = { 3,2 };

	_2Rani = new animation;
	_2Rani->init(632, 408, 316, 204);
	_2Rani->setPlaylist(_2Right, 2, false);
	_2Rani->setFPS(1);

	_2Lani = new animation;
	_2Lani->init(632, 408, 316, 204);
	_2Lani->setPlaylist(_2Left, 2, false);
	_2Lani->setFPS(1);

	_2RaniL = new animation;
	_2RaniL->init(632, 408, 316, 204);
	_2RaniL->setPlaylist(_2Right, 2, true);
	_2RaniL->setFPS(1);

	_2LaniL = new animation;
	_2LaniL->init(632, 408, 316, 204);
	_2LaniL->setPlaylist(_2Left, 2, true);
	_2LaniL->setFPS(1);

	int _2_1Right[] = { 0 };
	int _2_1Left[] = { 3 };
	_2_1Rani = new animation;
	_2_1Rani->init(632, 408, 316, 204);
	_2_1Rani->setPlaylist(_2_1Right, 1, false);
	_2_1Rani->setFPS(1);

	_2_1Lani = new animation;
	_2_1Lani->init(632, 408, 316, 204);
	_2_1Lani->setPlaylist(_2_1Left, 1, false);
	_2_1Lani->setFPS(1);

	int _2_2Right[] = { 1 };
	int _2_2Left[] = { 2 };
	_2_2Rani = new animation;
	_2_2Rani->init(632, 408, 316, 204);
	_2_2Rani->setPlaylist(_2_2Right, 1, false);
	_2_2Rani->setFPS(1);

	_2_2Lani = new animation;
	_2_2Lani->init(632, 408, 316, 204);
	_2_2Lani->setPlaylist(_2_2Left, 1, false);
	_2_2Lani->setFPS(1);
}

void enemy::ani3Set()
{
	int _3Right[] = { 0,1,2 };
	int _3Left[] = { 5,4,3 };

	_3Rani = new animation;
	_3Rani->init(948, 408, 316, 204);
	_3Rani->setPlaylist(_3Right, 3, false);
	_3Rani->setFPS(1);

	_3Lani = new animation;
	_3Lani->init(948, 408, 316, 204);
	_3Lani->setPlaylist(_3Left, 3, false);
	_3Lani->setFPS(1);

	_3RaniL = new animation;
	_3RaniL->init(948, 408, 316, 204);
	_3RaniL->setPlaylist(_3Right, 3, true);
	_3RaniL->setFPS(1);

	_3LaniL = new animation;
	_3LaniL->init(948, 408, 316, 204);
	_3LaniL->setPlaylist(_3Left, 3, true);
	_3LaniL->setFPS(1);
}

void enemy::ani4Set()
{
	int _4Right[] = { 0,1,2,3 };
	int _4Left[] = { 7,6,5,4 };

	_4Rani = new animation;
	_4Rani->init(1264, 408, 316, 204);
	_4Rani->setPlaylist(_4Right, 4, false);
	_4Rani->setFPS(1);

	_4Lani = new animation;
	_4Lani->init(1264, 408, 316, 204);
	_4Lani->setPlaylist(_4Left, 4, false);
	_4Lani->setFPS(1);
}

void enemy::ani6Set()
{
	int _6Right[] = { 0,1,2,3,4,5 };
	int _6Left[] = { 11,10,9,8,7,6 };

	_6Rani = new animation;
	_6Rani->init(1896, 408, 316, 204);
	_6Rani->setPlaylist(_6Right, 6, false);
	_6Rani->setFPS(1);

	_6Lani = new animation;
	_6Lani->init(1896, 408, 316, 204);
	_6Lani->setPlaylist(_6Left, 6, false);
	_6Lani->setFPS(1);
}

void enemy::ani7Set()
{
	int _7Right[] = { 0,1,2,3,4,5,6 };
	int _7Left[] = { 13,12,11,10,9,8,7 };

	_7Rani = new animation;
	_7Rani->init(2212, 408, 316, 204);
	_7Rani->setPlaylist(_7Right, 7, false);
	_7Rani->setFPS(1);

	_7Lani = new animation;
	_7Lani->init(2212, 408, 316, 204);
	_7Lani->setPlaylist(_7Left, 7, false);
	_7Lani->setFPS(1);

	int _7_3L_Right[] = { 3,0 };
	int _7_3R_Left[] = { 10,13 };
	//¿À¸¥ÂÊ º¼ ¶§ ¿ŞÂÊ ¸ÂÀ» ¶§
	_7_2L_Rani = new animation;
	_7_2L_Rani->init(2212, 408, 316, 204);
	_7_2L_Rani->setPlaylist(_7_3L_Right, 2, false);
	_7_2L_Rani->setFPS(1);
	//¿ŞÂÊ º¼ ¶§ ¿À¸¥ÂÊ ¸ÂÀ» ¶§
	_7_2R_Lani = new animation;
	_7_2R_Lani->init(2212, 408, 316, 204);
	_7_2R_Lani->setPlaylist(_7_3R_Left, 2, false);
	_7_2R_Lani->setFPS(1);


	int _7_3R_Right[] = { 2,1,0 };
	int _7_3L_Left[] = { 11,12,13 };

	_7_3L_Lani = new animation;
	_7_3L_Lani->init(2212, 408, 316, 204);
	_7_3L_Lani->setPlaylist(_7_3L_Left, 3, false);
	_7_3L_Lani->setFPS(1);

	_7_3R_Rani = new animation;
	_7_3R_Rani->init(2212, 408, 316, 204);
	_7_3R_Rani->setPlaylist(_7_3R_Right, 3, false);
	_7_3R_Rani->setFPS(1);

	int _7_1Right[] = { 2 };
	int _7_1Left[] = { 11 };

	_7_1Lani = new animation;
	_7_1Lani->init(2212, 408, 316, 204);
	_7_1Lani->setPlaylist(_7_1Left, 1, false);
	_7_1Lani->setFPS(1);

	_7_1Rani = new animation;
	_7_1Rani->init(2212, 408, 316, 204);
	_7_1Rani->setPlaylist(_7_1Right, 1, false);
	_7_1Rani->setFPS(1);

}

void enemy::aniSwitch()
{
	switch (_emST)
	{
	case IDLE:
		if (_emState.W == 0)
		{
			_emSet.img = _run;
			if (_left)_emSet.ani = _2_1Lani;
			else if (!_left)_emSet.ani = _2_1Rani;
			_emSet.ani->stop();
		}

		break;
	case WALK:
		_emSet.img = _walk;
		if (_left)_emSet.ani = _3LaniL;
		else if (!_left)_emSet.ani = _3RaniL;
		_emSet.ani->resume();
		break;
	case RUN:
		_emSet.img = _run;
		if (_left)_emSet.ani = _2LaniL;
		else if (!_left)_emSet.ani = _2RaniL;
		_emSet.ani->resume();
		break;
	case PUNCH:
		_emSet.img = _punch;
		if (_left)_emSet.ani = _3Lani;
		else if (!_left)_emSet.ani = _3Rani;
		_emSet.ani->resume();
		//°ø°İ¸ğ¼Ç ³¡³ª°í ¹Ù·Îµç Á¶±İÀÖ´Ù°¡µç ÈÄ¿¡ IDLE·Î º¯È¯
		break;
	case KICK:
		_emSet.img = _kick;
		if (_left)_emSet.ani = _3Lani;
		else if (!_left)_emSet.ani = _3Rani;
		_emSet.ani->resume();
		//°ø°İ¸ğ¼Ç ³¡³ª°í ¹Ù·Îµç Á¶±İÀÖ´Ù°¡µç ÈÄ¿¡ IDLE·Î º¯È¯
		break;
	case ITEM_PICK:
		_emSet.img = _jump;
		if (_left)_emSet.ani = _2_2Lani;
		else if (!_left)_emSet.ani = _2_2Rani;
		_emSet.ani->stop();
		break;
	case ITEM_ATTACK:
		if (_emState.W == 1)_emSet.img = _stick_pipe;
		else if (_emState.W == 2)_emSet.img = _chain;
		else if (_emState.W == 3)_emSet.img = _knuckles;
		else if (_emState.W == 4)_emSet.img = _rock;
		else if (_emState.W == 5)_emSet.img = _lift_trashcan;
		else if (_emState.W == 6)_emSet.img = _lift_crate;
		else if (_emState.W == 7)_emSet.img = _lift_tire;
		else if (_emState.W == 8)_emSet.img = _lift_human;
		if (_left)_emSet.ani = _4Lani;
		else if (!_left)_emSet.ani = _4Rani;
		_emSet.ani->resume();
		break;
	case ITEM_THROW:
		if (_emState.W == 1)_emSet.img = _throw_stick_pipe;
		else if (_emState.W == 2)_emSet.img = _throw_chain;
		else if (_emState.W == 3)_emSet.img = _throw_knuckles;
		else if (_emState.W == 4)_emSet.img = _throw_rock;
		else if (_emState.W == 5)_emSet.img = _throw_trashcan;
		else if (_emState.W == 6)_emSet.img = _throw_crate;
		else if (_emState.W == 7)_emSet.img = _throw_tire;
		else if (_emState.W == 8)_emSet.img = _throw_human;
		if (_left)_emSet.ani = _6Lani;
		else if (!_left)_emSet.ani = _6Rani;
		_emSet.ani->resume();
		break;
	case DEFEND:
		_emSet.img = _defend;
		if (_left)_emSet.ani = _1Lani;
		else if (!_left)_emSet.ani = _1Rani;
		_emSet.ani->stop();
		break;
	case HIT:
		_emSet.img = _beatup;
		if (_left)
		{
			//¸¶ÁÖº¸°í ¸ÂÀ» ¶§
			_emSet.ani = _7_3L_Lani;
			//µîµÚ¸¦ ¸ÂÀ» ¶§
			_emSet.ani = _7_2R_Lani;
		}
		else if (!_left)
		{
			//¸¶ÁÖº¸°í ¸ÂÀ» ¶§
			_emSet.ani = _7_3R_Rani;
			//µîµÚ¸¦ ¸ÂÀ» ¶§
			_emSet.ani = _7_2L_Rani;
		}
		_emSet.ani->resume();
		break;
	case FALL:
		_emSet.img = _beatup;
		if (_left)_emSet.ani = _7_1Lani;
		if (!_left)_emSet.ani = _7_1Rani;
		_emSet.ani->stop();
		break;
	case JUMP:
		_emSet.img = _jump;
		if (_left)_emSet.ani = _7_1Lani;
		if (!_left)_emSet.ani = _7_1Rani;
		_emSet.ani->stop();
		//Á¡ÇÁ ÇØÁ¦½Ã
		{
			_emSet.ani->resume();
		}
		break;
	case KO:
		_emSet.img = _ko;
		if (_left)_emSet.ani = _2Lani;
		if (!_left)_emSet.ani = _2Rani;

		_emSet.ani->resume();
		break;
	default:
		break;
	}
}

