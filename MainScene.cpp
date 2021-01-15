#include "stdafx.h"
#include "MainScene.h"

MainScene::MainScene()
{

}

MainScene::~MainScene()
{

}

HRESULT MainScene::init()
{
	crtScene = cnt = xpos = ypos = pulse = _x = _y = other = 0;
	alpha = 255;
	pulser = false;

	char cList[] =
	{
		'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e', 'Z', 'z', ',',
		'F', 'f', 'G', 'g', 'H', 'h', 'I', 'i', 'J', 'j', '.', '-',
		'K', 'k', 'L', 'l', 'M', 'm', 'N', 'n', 'O', 'o',
		'P', 'p', 'Q', 'q', 'R', 'r', 'S', 's', 'T', 't',
		'U', 'u', 'V', 'v', 'W', 'w', 'X', 'x', 'Y', 'y',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
	};

	strcpy_s(nameSet, 384, cList);

	return S_OK;
}

void MainScene::release()
{

}

void MainScene::update()
{
	L->update();
#ifdef _DEBUG
	{
		if (KEY->down('1')) { SND->stopAll(); L->AllDeleteLine(); crtScene = 3; cnt = 280; }
	}
#endif
	if (crtScene == 0) Turn1();
	if (crtScene == 1) Turn2();
	if (crtScene == 100) setName();
	if (crtScene == 2) Turn3();
	if (crtScene == 3) Turn4();
}

void MainScene::render()
{
	SceneRender();
}

void MainScene::Turn1() //로고
{
	if (alpha > 0 && !cnt) alpha -= 5;
	if (alpha <= 0 && cnt < 120)
	{
		if (KEY->down(VK_RETURN))
		{
			cnt = 120;
		}
		else cnt++;
		alpha = 0;
	}
	if (cnt >= 120 && alpha < 255) alpha += 5;
	if (alpha >= 255 && cnt >= 120) { alpha = 255; cnt = 0; crtScene = 1; }
}

void MainScene::Turn2() //로고
{
	if (SND->isPlaying("5 - Menu.mp3"))
	{
		SND->stop("5 - Menu.mp3");
	}
	if (!SND->isPlaying("1 - Game Mode & Character Select.mp3"))
	{
		SND->play("1 - Game Mode & Character Select.mp3", _currMasterVolume * _currBGMVolume);
	}

	//cnt변수 재활용
	if (cnt == 0)
	{
		L->calmLine(MakePt(287, 160), "MESSAGE SPEED");
		L->calmLine(MakePt(448, 255), "SLOW");
		L->calmLine(MakePt(448, 319), "NORMAL");
		L->calmLine(MakePt(448, 383), "FAST");
		L->calmLine(MakePt(351, 544), "SKILL LEVEL");
		L->calmLine(MakePt(159, 640), "NOVICE");
		L->calmLine(MakePt(608, 640), "ADVANCED");
		cnt = 1;
	}

	if (cnt == 1)
	{
		if (alpha > 0) { alpha -= 5; }
		if (alpha <= 0)
		{
			L->CreateLine(MakePt(65, 768), "Select message speed & level.", "n", false);
			L->CreateLine(MakePt(384, 255+64), "▶", "화살표1", false);
			L->CreateLine(MakePt(94, 640), "▶", "화살표2", false);
			ypos = 1;
			cnt = 2;
		}
	}

	if (cnt == 2)
	{
		if (KEY->down('W') && ypos > 0)
		{
			ypos--;
			L->CorrectLine("화살표1", MakePt(0, -64));
		}
		else if (KEY->down('S') && ypos < 2)
		{
			ypos++;
			L->CorrectLine("화살표1", MakePt(0, 64));
		}
		if (KEY->down('A') && xpos > 0)
		{
			xpos--;
			L->CorrectLine("화살표2", MakePt(-449, 0));
		}
		else if (KEY->down('D') && xpos < 1)
		{
			xpos++;
			L->CorrectLine("화살표2", MakePt(449, 0));
		}
		if (KEY->down(VK_RSHIFT))
		{
			cnt = 100;
		}
		if (KEY->down(VK_RETURN))
		{
			if (ypos == 0) _lineSpd = 5;
			if (ypos == 1) _lineSpd = 3;
			if (ypos == 2) _lineSpd = 1;
			cnt = 3;
		}
	}
	if (cnt == 3 || cnt == 100)
	{
		alpha += 5;
		if (alpha > 255)
		{
			if (cnt == 3)
			{
				crtScene = 2;
				cnt = 0;
				L->AllDeleteLine();
			}
			if (cnt == 100)
			{
				crtScene = 100;
				cnt = 0;
				L->AllDeleteLine();
			}
		}
	}
}

void MainScene::Turn3()	//줄거리
{
	
	if (SND->isPlaying("1 - Game Mode & Character Select.mp3"))
	{
		SND->stop("1 - Game Mode & Character Select.mp3");
	}
	if (!SND->isPlaying("2 - Prologue & Epilogue.mp3"))
	{
		SND->play("2 - Prologue & Epilogue.mp3", _currMasterVolume * _currBGMVolume);
		SND->findChannel("2 - Prologue & Epilogue.mp3")->setLoopPoints(0, FMOD_TIMEUNIT_MS, 109027, FMOD_TIMEUNIT_MS);
		SND->findChannel("2 - Prologue & Epilogue.mp3")->setPosition(0, FMOD_TIMEUNIT_MS);
		SND->findChannel("2 - Prologue & Epilogue.mp3")->setLoopCount(-1);
		
	}
	if (cnt == 0)
	{
		L->calmLine(MakePt(64, 159),
			" I hold your city captive &%"
			"Ryan's girlfriend hostage.%"
			"With my gangs of students &%"
			"evil bosses, nobody can stop%"
			"me now. Meet my demands - or%"
			"else!... P.S. Alex & Ryan if%"
			"you interfere, you'll be in%"
			"for the fight of your lives!%"
			"... SLICK");

		cnt = 1;
	}
	if (cnt == 1)
	{
		alpha -= 5;
		if (alpha < 0) { alpha = 0; cnt = 2; }
	}
	if (cnt == 2)
	{
		if (KEY->down(VK_RETURN))
		{
			cnt = 3;
		}
	}
	if (cnt == 3)
	{
		alpha += 5;
		if (alpha > 255) { crtScene = 3; cnt = 0; L->AllDeleteLine(); }
	}
}

void MainScene::Turn4()	//회사로고
{
	if (SND->isPlaying("2 - Prologue & Epilogue.mp3"))
	{
		SND->stop("2 - Prologue & Epilogue.mp3");
	}
	if (!SND->isPlaying("3 - Title Screen.mp3") && cnt < 280)
	{
		SND->play("3 - Title Screen.mp3", _currMasterVolume * _currBGMVolume);
	}
	if (cnt == 0)
	{
		alpha -= 5;
		if (alpha < 0) { alpha = 0; cnt = 1; }
	}
	else if (cnt >= 1 && cnt < 280)
	{
		if (KEY->down(VK_RETURN))
		{
			cnt = 280;
		}
		else cnt++;
	}
	
	if (cnt == 280)
	{
		alpha += 5;
		if (SND->isPlaying("3 - Title Screen.mp3"))
		{
			SND->stop("3 - Title Screen.mp3");
		}
		if (alpha >= 255) { SC->changeScene("게임 장면"); }
	}
	
}

void MainScene::setName()
{
	if (SND->isPlaying("1 - Game Mode & Character Select.mp3"))
	{
		SND->stop("1 - Game Mode & Character Select.mp3");
	}
	if (!SND->isPlaying("5 - Menu.mp3"))
	{
		SND->play("5 - Menu.mp3", _currMasterVolume * _currBGMVolume);
		SND->findChannel("5 - Menu.mp3")->setLoopPoints(66137, FMOD_TIMEUNIT_MS, 133153, FMOD_TIMEUNIT_MS);
		SND->findChannel("5 - Menu.mp3")->setPosition(66137, FMOD_TIMEUNIT_MS);
		SND->findChannel("5 - Menu.mp3")->setLoopCount(-1);
	}
	if (cnt == 0)
	{
		string word[] = {
		"A", "a" , "B" , "b" , "C" , "c" , "D" , "d" , "E" , "e",
		"F", "f", "G", "g", "H", "h", "I", "i", "J", "j",
		"K", "k", "L", "l", "M", "m", "N", "n", "O", "o",
		"P", "p", "Q", "q", "R", "r", "S", "s", "T", "t",
		"U", "u", "V", "v", "W", "w", "X", "x", "Y", "y",
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
		};

		for (int i = 0; i < 6; i++)
		{
			for (int e = 0; e < 10; e++)
			{
				L->calmLine(MakePt(96 + (67 * e), 351 + (65 * i)), word[e + (i * 10)]);
			}
		}
		L->calmLine(MakePt(768, 351), "Z"); L->calmLine(MakePt(768 + 67, 351), "z"); L->calmLine(MakePt(768 + 134, 351), ",");
		L->calmLine(MakePt(768, 351 + 65), "."); L->calmLine(MakePt(768 + 67, 351 + 65), "-");
		L->calmLine(MakePt(768, 351 + 130), "AHEAD");
		L->calmLine(MakePt(768, 351 + 195), "BACK");
		L->calmLine(MakePt(768, 351 + 260), "ERASE");
		L->calmLine(MakePt(768, 351 + 325), "E N D");
		L->CreateLine(MakePt(65, 768), "Name your Character.", "n", false);
		cnt = 1;
	}
	if (cnt == 1)
	{
		if (alpha > 0) { alpha -= 5; }
		if (alpha <= 0)
		{
			other = 0;
			for (int i = 0; i < 5; i++)
			{
				myName[i] = ' ';
			}

			xpos = ypos = 0;
			_x = 65;
			_y = 351;

			L->CreateLine(MakePt(64, 351), "`", "이름화살표", false);

			for (int i = 0; i < 5; i++)
			{
				char str[32];
				char omyName[16];

				sprintf_s(omyName, "%c", myName[i]);

				sprintf_s(str, "이름%d", i);
				L->CreateLine(MakePt(420 + (i * 32), 227), "￣", str, false);
				sprintf_s(str, "네임%d", i);
				L->CreateLine(MakePt(452 + (i * 32), 227 - 32), omyName, str, false);
			}
			cnt = 2;
		}
	}
	if (cnt == 2)
	{
		pulse = pulse % 8;

		if (KEY->down('A') && xpos > 0) { _x -= 67; xpos--; }
		if (KEY->down('D'))
		{
			if (xpos < 12 && ypos == 0)
			{
				_x += 67;
				xpos++;
			}
			if (xpos < 11 && ypos == 1)
			{
				_x += 67;
				xpos++;
			}
			if (xpos < 10 && ypos > 1 && ypos < 6)
			{
				_x += 67;
				xpos++;
			}
		}
		if (KEY->down('W') && ypos > 0) { _y -= 65; ypos--; }
		if (KEY->down('S'))
		{
			if (xpos <= 10 && ypos < 5)
			{
				_y += 65;
				ypos++;
			}
			if (xpos == 11 && ypos == 0)
			{
				_y += 65;
				ypos++;
			}
		}

		char oname[64];

		if (KEY->down('K'))
		{
			bool otherOK = false;

			if (xpos <= 10 && ypos <= 5)
			{
				myName[other] = nameSet
					[
						(
							(ypos == 0) * 0 +
							(ypos == 1) * 13 +
							(ypos == 2) * 25 +
							(ypos == 3) * 35 +
							(ypos == 4) * 45 +
							(ypos == 5) * 55
							) + xpos
					];
			}

			if (xpos == 11 && ypos == 0) myName[other] = nameSet[11];
			if (xpos == 12 && ypos == 0) myName[other] = nameSet[12];
			if (xpos == 11 && ypos == 1) myName[other] = nameSet[24];

			if (xpos == 10 && ypos == 2)	//AHEAD
			{
				otherOK = true;
				other++;
			}
			else if (xpos == 10 && ypos == 3)	//BACK
			{
				otherOK = true;
				other--;
			}
			else if (xpos == 10 && ypos == 4)	//ERASE
			{
				otherOK = true;
				for (int i = 0; i < 5; i++)
				{
					myName[i] = ' ';
					sprintf_s(oname, "네임%d", i);
					L->selectChangeLine(oname, 0, myName[i]);
				}
				other = 0;
			}
			else if (xpos == 10 && ypos == 5)
			{
				char playerName[128] = { 0 };
				int voidNameCheck = 0;

				for (int i = 0; i < 5; i++)
				{
					char N[64];
					sprintf_s(N, "네임%d", i);
					sprintf_s(oname, "%c", L->getArrWord(N, 0));
					strcat_s(playerName, sizeof(playerName), oname);
					if (L->getArrWord(N, 0) == ' ') voidNameCheck++;
				//	voidNameCheck += ((L->getArrWord(N, 0) == ' ')==true);
				}
				if(voidNameCheck != 5) _playerChName = playerName;
			
				cnt = 3;
			}
			else
			{
				sprintf_s(oname, "네임%d", other);
				L->selectChangeLine(oname, 0, myName[other]);
			}

			if (cnt != 3)
			{
				if (other < 5 && !otherOK) other++;
				if (other >= 5) other = 4;
				if (other <= 0) other = 0;

				for (int i = 0; i < 5; i++)
				{
					if (other != i)
					{
						sprintf_s(oname, "이름%d", i);
						L->setPosLine(oname, MakePt(452 + (i * 32), 227));
					}
				}
			}
		}
		if (cnt != 3)
		{
			//
			sprintf_s(oname, "이름%d", other);

			if (!pulse)
			{
				pulser = !pulser;
				L->CorrectLine(oname, MakePt(
					(2000 * ((pulser)+((!pulser)*(-1)))),
					(2000 * ((pulser)+((!pulser)*(-1))))
				));
			}

			L->setPosLine("이름화살표", MakePt(
				_x + (2000 * ((pulser)+((!pulser)*(0)))),
				_y + (2000 * ((pulser)+((!pulser)*(0))))
			));

			pulse++;
		}
	}
	if (cnt == 3)
	{
		alpha += 5;
		if (alpha >= 255) { L->AllDeleteLine(); alpha = 255; cnt = xpos = ypos = 0; crtScene = 1; }
	}
}

void MainScene::SceneRender()
{
	if (crtScene == 0)
	{
		IMG->render("검은 화면", getMemDC());
		IMG->render("제작사 로고",
			getMemDC(), WINW / 2 - (IMG->find("제작사 로고")->getWidth() / 2),
			WINH / 2 - (IMG->find("제작사 로고")->getHeight() / 2));
	}
	if (crtScene == 1)
	{	
		IMG->render("640파란 화면", getMemDC(), 0, 96);
		//이름이 잘저장돼나 확인용
		char str[256];
		sprintf_s(str, "%s", _playerChName.c_str());
		TextOut(getMemDC(), 300, 300, str, strlen(str));
	}
	if (crtScene == 2)
	{
		IMG->render("640파란 화면", getMemDC(), 0, 96);
	}
	if (crtScene == 3)//회사로고
	{
		IMG->render("제목", getMemDC(), 0, 96);
	}
	if (crtScene == 100)//회사로고
	{
		IMG->render("이름설정파란화면", getMemDC(), 0, 96);

	}

	L->render();
	IMG->alphaRender("검은 화면", getMemDC(), 0, 0, alpha);
}