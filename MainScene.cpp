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
	crtScene = cnt = xpos = ypos = 0;
	alpha = 255;
	return S_OK;
}

void MainScene::release()
{

}

void MainScene::update()
{
	L->update();
	if (crtScene == 0) Turn1();
	if (crtScene == 1) Turn2();
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
		cnt++;
		alpha = 0;
	}
	if (cnt >= 120 && alpha < 255) alpha += 5;
	if (alpha >= 255 && cnt >= 120) { alpha = 255; cnt = 0; crtScene = 1; }
}

void MainScene::Turn2() //로고
{
	//cnt변수 재활용
	if (cnt == 0)
	{
		L->CreateLine(MakePt(287, 160), "MESSAGE SPEED", "n", false);
		L->CreateLine(MakePt(448, 255), "SLOW", "n", false);
		L->CreateLine(MakePt(448, 319), "NORMAL", "n", false);
		L->CreateLine(MakePt(448, 383), "FAST", "n", false);
		L->CreateLine(MakePt(351, 544), "SKILL LEVEL", "n", false);
		L->CreateLine(MakePt(159, 640), "NOVICE", "n", false);
		L->CreateLine(MakePt(608, 640), "ADVANCED", "n", false);
		cnt = 1;
	}

	if (cnt == 1)
	{
		if (alpha > 0) { alpha -= 5; }
		if (alpha <= 0)
		{
			L->CreateLine(MakePt(65, 768), "Select message speed & level.", "n", false);
			L->CreateLine(MakePt(390, 255), "▶", "화살표1", false);
			L->CreateLine(MakePt(100, 640), "▶", "화살표2", false);
			cnt = 2;
		}
	}

	if (cnt == 2)
	{
		if (KEY->down(VK_UP) && ypos > 0)
		{
			ypos--;
			L->CorrectLine("화살표1", MakePt(0, -64));
		}
		else if (KEY->down(VK_DOWN) && ypos < 2)
		{
			ypos++;
			L->CorrectLine("화살표1", MakePt(0, 64));
		}
		if (KEY->down(VK_LEFT) && xpos > 0)
		{
			xpos--;
			L->CorrectLine("화살표2", MakePt(-449, 0));
		}
		else if (KEY->down(VK_RIGHT) && xpos < 1)
		{
			xpos++;
			L->CorrectLine("화살표2", MakePt(449, 0));
		}
		if (KEY->down(VK_RETURN))
		{
			cnt = 3;
		}
	}
	if (cnt == 3)
	{
		alpha += 5;
		if (alpha > 255) { crtScene = 2; cnt = 0; L->AllDeleteLine(); }
	}
}

void MainScene::Turn3()	//줄거리
{
	if (cnt == 0)
	{
		L->CreateLine(MakePt(64, 159),
			" I hold your city captive &%"
			"Ryan's girlfriend hostage.%"
			"With my gangs of students &%"
			"evil bosses, nobody can stop%"
			"me now. Meet my demands - or%"
			"else!... P.S. Alex & Ryan if%"
			"you interfere, you'll be in%"
			"for the fight of your lives!%"
			"... SLICK"
			,
			"n", false);
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
	if (cnt == 0)
	{
		alpha -= 5;
		if (alpha < 0) { alpha = 0; cnt = 1; }
	}
	else if (cnt >= 1 && cnt < 300)
	{
		cnt++;
	}
	if (cnt == 300)
	{
		alpha += 5;
		if (alpha >= 255) { SC->changeScene("게임 장면"); }
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
	}
	if (crtScene == 2)
	{
		IMG->render("640파란 화면", getMemDC(), 0, 96);
	}
	if (crtScene == 3)//회사로고
	{
		IMG->render("제목", getMemDC(), 0, 96);
	}

	L->render();
	IMG->alphaRender("검은 화면", getMemDC(), 0, 0, alpha);
}