#include "stdafx.h"
#include "loadingScene.h"
#include "gameScene.h"
#include "MainScene.h"
#include "progressBar.h"
#include <process.h> // _beginthreadex

loadingScene::loadingScene(): _background(nullptr), _loadingBar(nullptr), _currentCount(0) {}

loadingScene::~loadingScene() {}

HRESULT loadingScene::init()
{
	_loadingBar = new progressBar;
	_loadingBar->init(0, WINH - 30, WINW, 30);
	_loadingBar->updateGauge(0, 0);

	hThread = (HANDLE)_beginthreadex(NULL, 0, threadFunc, this, CREATE_SUSPENDED, NULL);
	if (!hThread)
	{
		return E_FAIL;
	}
	ResumeThread(hThread);

	return S_OK;
}

void loadingScene::release()
{
	SAFE_DEL(_loadingBar);
}

void loadingScene::update()
{
	_loadingBar->update();
	_loadingBar->updateGauge(static_cast<float>(_currentCount), MAX_SLEEP_CALLS);
}

void loadingScene::render()
{
	_loadingBar->render();

	// 로딩 완료 시
	if (_currentCount == MAX_SLEEP_CALLS)
	{
		CloseHandle(hThread);
		SC->changeScene("메인화면");
	}
}

unsigned CALLBACK loadingScene::threadFunc(LPVOID params)
{
	loadingScene* loadingParams = (loadingScene*)params;

	SC->addScene("메인화면", new MainScene);
	++loadingParams->_currentCount;

	SC->addScene("게임 장면", new gameScene);
	++loadingParams->_currentCount;

	// 시작 화면 이미지
	IMG->add("제작사 로고", "images/preGame/logo.bmp", 714, 128, false, RGB(255, 0, 255));
	IMG->add("제목", "images/preGame/title.bmp", 1024, 640, false, RGB(255, 0, 255));
	++loadingParams->_currentCount;

	// 맵 이미지
	IMG->add("맵 1", "images/maps/1.bmp", 3036, 640, false, RGB(255, 0, 255));
	IMG->add("맵 2", "images/maps/2.bmp", 2012, 640, false, RGB(255, 0, 255));
	IMG->add("맵 3", "images/maps/3.bmp", 2012, 640, false, RGB(255, 0, 255));
	IMG->add("맵 4", "images/maps/4.bmp", 3040, 640, false, RGB(255, 0, 255));
	IMG->add("맵 4-2", "images/maps/4-2.bmp", 1884, 640, false, RGB(255, 0, 255));
	IMG->add("맵 5", "images/maps/5.bmp", 2012, 640, false, RGB(255, 0, 255));
	IMG->add("상점맵", "images/maps/shopbasic.bmp", 1024, 640, false, RGB(255, 0, 255));
	++loadingParams->_currentCount;

	// 캐릭터 이미지
	loadingParams->playerImg(); ++loadingParams->_currentCount;
	loadingParams->enemyImgOne(); ++loadingParams->_currentCount;
	loadingParams->enemyImgTwo(); ++loadingParams->_currentCount;
	loadingParams->enemyImgThree(); ++loadingParams->_currentCount;
	loadingParams->enemyImgFour(); ++loadingParams->_currentCount;
	loadingParams->enemyImgFive(); ++loadingParams->_currentCount;
	loadingParams->enemyImgSix(); ++loadingParams->_currentCount;
	loadingParams->enemyImgSeven(); ++loadingParams->_currentCount;
	loadingParams->enemyImgEight(); ++loadingParams->_currentCount;
	loadingParams->enemyImgNine(); ++loadingParams->_currentCount;
	loadingParams->enemyImgBoss(); ++loadingParams->_currentCount;

	// 무기 이미지
	loadingParams->wpImg();	++loadingParams->_currentCount;

	// 동전 이미지
	IMG->addF("동전", "images/coin.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	++loadingParams->_currentCount;

	// 화면 배경 이미지
	IMG->add("이름설정파란화면", "images/NAMEblueScreen.bmp", WINW, 640, false, RGB(0, 0, 0));
	IMG->add("검은 화면", "images/blackScreen.bmp", WINW, WINH, false, RGB(0, 0, 0));
	IMG->add("파란 화면", "images/blueScreen.bmp", WINW, WINH, false, RGB(0, 0, 0));
	IMG->add("640파란 화면", "images/640blueScreen.bmp", WINW, 640, false, RGB(0, 0, 0));
	++loadingParams->_currentCount;

	//상점 이미지
	IMG->add("포인터", "images/maps/pointer.bmp", 40, 40, true, RGB(255, 0, 255));
	IMG->add("빵집", "images/maps/bakery.bmp", 265, 265, false, RGB(0, 0, 0));
	IMG->add("카페", "images/maps/cafe.bmp", 265, 265, false, RGB(0, 0, 0));
	IMG->add("초밥집", "images/maps/sushishop.bmp", 265, 265, false, RGB(0, 0, 0));
	IMG->add("서점", "images/maps/bookstore.bmp", 265, 265, false, RGB(0, 0, 0));



	ifstream file;
	string line;
	// 배경음
	file.open("sounds/bgm/fileList.txt");
	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (line == "3 - Title Screen.mp3")
			{
				SND->addSound(line, "sounds/bgm/3 - Title Screen.mp3", true, false);
			}
			else
			{
				SND->addSound(line, "sounds/bgm/" + line, true, true);
			}
		}
	}
	file.close();
	++loadingParams->_currentCount;

	// 효과음
	file.open("sounds/fx/fileList.txt");
	if (file.is_open())
	{
		while (getline(file, line))
		{
			SND->addSound(line, "sounds/fx/" + line, false, false);
		}
	}
	file.close();
	++loadingParams->_currentCount;

	while (loadingParams->_currentCount != MAX_SLEEP_CALLS)
	{
		Sleep(1);
		++loadingParams->_currentCount;
	}
	return 0;
}

void loadingScene::playerImg()
{
	IMG->addF("p-달리기", "images/player/p-1_run.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("p-걷기", "images/player/p-2_walk.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("p-펀치", "images/player/p-3_punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("p-킥", "images/player/p-4_kick.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("p-어퍼컷", "images/player/p-5_upperCut.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("p-하이킥", "images/player/p-6_highKick.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("p-달리기펀치", "images/player/p-7_run+punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("p-점프", "images/player/p-8_jump.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("p-점프킥", "images/player/p-9_jump+kick.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("p-방어", "images/player/p-10_defend.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("p-피격", "images/player/p-11_beatUp.bmp", 2212, 408, 7, 2, true, RGB(255, 0, 255));
	IMG->addF("p-KO", "images/player/p-12_ko.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("p-스틱", "images/player/p-13_stick.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("p-체인", "images/player/p-14_chain.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("p-너클", "images/player/p-15_knuckle.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("p-돌", "images/player/p-16_rock.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("p-쓰레기", "images/player/p-17_trash.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("p-박스", "images/player/p-18_box.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("p-타이어", "images/player/p-19_tire.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("p-사람", "images/player/p-20_human.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("p-스틱던지기", "images/player/p-21_throw-stick.bmp", 2212, 408, 8, 2, true, RGB(255, 0, 255));
	IMG->addF("p-체인던지기", "images/player/p-22_throw-chain.bmp", 2212, 408, 8, 2, true, RGB(255, 0, 255));
	IMG->addF("p-너클던지기", "images/player/p-23_throw-knucle.bmp", 2212, 408, 8, 2, true, RGB(255, 0, 255));
	IMG->addF("p-돌던지기", "images/player/p-24_throw-rock.bmp", 2212, 408, 8, 2, true, RGB(255, 0, 255));
	IMG->addF("p-쓰레기던지기", "images/player/p-25_throw-trash.bmp", 2212, 408, 8, 2, true, RGB(255, 0, 255));
	IMG->addF("p-박스던지기", "images/player/p-26_throw-box.bmp", 2212, 408, 8, 2, true, RGB(255, 0, 255));
	IMG->addF("p-타이어던지기", "images/player/p-27_throw-tire.bmp", 2212, 408, 8, 2, true, RGB(255, 0, 255));
	IMG->addF("p-사람던지기", "images/player/p-28_throw-human.bmp", 2212, 408, 8, 2, true, RGB(255, 0, 255));
	IMG->addF("p-구르기", "images/player/p-29_roll.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("p-상점주문1", "images/player/p-30_shop_stand_orderl.bmp", 676, 144, 8, 1, true, RGB(255, 0, 255));
	IMG->addF("p-상점취식1", "images/player/p-31_shop_sit_order.bmp", 648, 136, 8, 1, true, RGB(255, 0, 255));
	IMG->addF("p-상점주문2", "images/player/p-32_shop_stand_eat.bmp", 576, 160, 7, 1, true, RGB(255, 0, 255));
	IMG->addF("p-상점취식2", "images/player/p-33_shop_sit_eat.bmp", 548, 152, 7, 1, true, RGB(255, 0, 255));
}

void loadingScene::enemyImgOne()
{
	IMG->addF("1-달리기", "image/enemy/type1/02walk.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("1-걷기", "image/enemy/type1/02walk.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("1-펀치", "image/enemy/type1/03punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("1-킥", "image/enemy/type1/04kick.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("1-어퍼컷", "image/enemy/type1/05uppercut.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("1-하이킥", "image/enemy/type1/06highkick.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("1-달리기펀치", "image/enemy/type1/07run+punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("1-점프", "image/enemy/type1/08jump.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("1-점프킥", "image/enemy/type1/09jumpkick.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("1-방어", "image/enemy/type1/10defend.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("1-피격", "image/enemy/type1/11beatup.bmp", 2212, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("1-KO", "image/enemy/type1/12ko.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("1-스틱", "image/enemy/type1/13stick+pipe.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("1-체인", "image/enemy/type1/14chain.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("1-너클", "image/enemy/type1/15knuckles.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("1-돌", "image/enemy/type1/16rock.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("1-쓰레기", "image/enemy/type1/17throwtrashcan.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("1-박스", "image/enemy/type1/18throwcrate.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("1-타이어", "image/enemy/type1/19throwtire.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("1-사람", "image/enemy/type1/20throwhuman.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("1-스틱던지기", "image/enemy/type1/21throw+stick+pipe.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("1-체인던지기", "image/enemy/type1/22throw+chain.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("1-너클던지기", "image/enemy/type1/23throw+knuckles.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("1-돌던지기", "image/enemy/type1/24throw+rock.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("1-쓰레기던지기", "image/enemy/type1/25throw+trashcan.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("1-박스던지기", "image/enemy/type1/26throw+crate.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("1-타이어던지기", "image/enemy/type1/27throw+tire.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("1-사람던지기 ", "image/enemy/type1/28throw+human.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
}

void loadingScene::enemyImgTwo()
{
	IMG->addF("2-달리기", "image/enemy/type2/02walk.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("2-걷기", "image/enemy/type2/02walk.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("2-펀치", "image/enemy/type2/03punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("2-킥", "image/enemy/type2/04kick.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("2-어퍼컷", "image/enemy/type2/05uppercut.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("2-하이킥", "image/enemy/type2/06highkick.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("2-달리기펀치", "image/enemy/type2/07run+punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("2-점프", "image/enemy/type2/08jump.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("2-점프킥", "image/enemy/type2/09jumpkick.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("2-방어", "image/enemy/type2/10defend.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("2-피격", "image/enemy/type2/11beatup.bmp", 2212, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("2-KO", "image/enemy/type2/12ko.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("2-스틱", "image/enemy/type2/13stick+pipe.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("2-체인", "image/enemy/type2/14chain.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("2-너클", "image/enemy/type2/15knuckles.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("2-돌", "image/enemy/type2/16rock.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("2-쓰레기", "image/enemy/type2/17throwtrashcan.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("2-박스", "image/enemy/type2/18throwcrate.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("2-타이어", "image/enemy/type2/19throwtire.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("2-사람", "image/enemy/type2/20throwhuman.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("2-스틱던지기", "image/enemy/type2/21throw+stick+pipe.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("2-체인던지기", "image/enemy/type2/22throw+chain.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("2-너클던지기", "image/enemy/type2/23throw+knuckles.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("2-돌던지기", "image/enemy/type2/24throw+rock.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("2-쓰레기던지기", "image/enemy/type2/25throw+trashcan.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("2-박스던지기", "image/enemy/type2/26throw+crate.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("2-타이어던지기", "image/enemy/type2/27throw+tire.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("2-사람던지기 ", "image/enemy/type2/28throw+human.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
}

void loadingScene::enemyImgThree()
{
	IMG->addF("3-달리기", "image/enemy/type3/02walk.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("3-걷기", "image/enemy/type3/02walk.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("3-펀치", "image/enemy/type3/03punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("3-킥", "image/enemy/type3/04kick.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("3-어퍼컷", "image/enemy/type3/05uppercut.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("3-하이킥", "image/enemy/type3/06highkick.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("3-달리기펀치", "image/enemy/type3/07run+punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("3-점프", "image/enemy/type3/08jump.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("3-점프킥", "image/enemy/type3/09jumpkick.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("3-방어", "image/enemy/type3/10defend.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("3-피격", "image/enemy/type3/11beatup.bmp", 2212, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("3-KO", "image/enemy/type3/12ko.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("3-스틱", "image/enemy/type3/13stick+pipe.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("3-체인", "image/enemy/type3/14chain.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("3-너클", "image/enemy/type3/15knuckles.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("3-돌", "image/enemy/type3/16rock.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("3-쓰레기", "image/enemy/type3/17throwtrashcan.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("3-박스", "image/enemy/type3/18throwcrate.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("3-타이어", "image/enemy/type3/19throwtire.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("3-사람", "image/enemy/type3/20throwhuman.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("3-스틱던지기", "image/enemy/type3/21throw+stick+pipe.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("3-체인던지기", "image/enemy/type3/22throw+chain.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("3-너클던지기", "image/enemy/type3/23throw+knuckles.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("3-돌던지기", "image/enemy/type3/24throw+rock.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("3-쓰레기던지기", "image/enemy/type3/25throw+trashcan.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("3-박스던지기", "image/enemy/type3/26throw+crate.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("3-타이어던지기", "image/enemy/type3/27throw+tire.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("3-사람던지기 ", "image/enemy/type3/28throw+human.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
}

void loadingScene::enemyImgFour()
{
	IMG->addF("4-달리기", "image/enemy/type4/02walk.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("4-걷기", "image/enemy/type4/02walk.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("4-펀치", "image/enemy/type4/03punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("4-킥", "image/enemy/type4/04kick.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("4-어퍼컷", "image/enemy/type4/05uppercut.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("4-하이킥", "image/enemy/type4/06highkick.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("4-달리기펀치", "image/enemy/type4/07run+punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("4-점프", "image/enemy/type4/08jump.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("4-점프킥", "image/enemy/type4/09jumpkick.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("4-방어", "image/enemy/type4/10defend.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("4-피격", "image/enemy/type4/11beatup.bmp", 2212, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("4-KO", "image/enemy/type4/12ko.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("4-스틱", "image/enemy/type4/13stick+pipe.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("4-체인", "image/enemy/type4/14chain.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("4-너클", "image/enemy/type4/15knuckles.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("4-돌", "image/enemy/type4/16rock.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("4-쓰레기", "image/enemy/type4/17throwtrashcan.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("4-박스", "image/enemy/type4/18throwcrate.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("4-타이어", "image/enemy/type4/19throwtire.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("4-사람", "image/enemy/type4/20throwhuman.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("4-스틱던지기", "image/enemy/type4/21throw+stick+pipe.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("4-체인던지기", "image/enemy/type4/22throw+chain.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("4-너클던지기", "image/enemy/type4/23throw+knuckles.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("4-돌던지기", "image/enemy/type4/24throw+rock.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("4-쓰레기던지기", "image/enemy/type4/25throw+trashcan.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("4-박스던지기", "image/enemy/type4/26throw+crate.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("4-타이어던지기", "image/enemy/type4/27throw+tire.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("4-사람던지기 ", "image/enemy/type4/28throw+human.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
}

void loadingScene::enemyImgFive()
{
	IMG->addF("5-달리기", "image/enemy/type5/02walk.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("5-걷기", "image/enemy/type5/02walk.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("5-펀치", "image/enemy/type5/03punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("5-킥", "image/enemy/type5/04kick.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("5-어퍼컷", "image/enemy/type5/05uppercut.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("5-하이킥", "image/enemy/type5/06highkick.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("5-달리기펀치", "image/enemy/type5/07run+punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("5-점프", "image/enemy/type5/08jump.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("5-점프킥", "image/enemy/type5/09jumpkick.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("5-방어", "image/enemy/type5/10defend.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("5-피격", "image/enemy/type5/11beatup.bmp", 2212, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("5-KO", "image/enemy/type5/12ko.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("5-스틱", "image/enemy/type5/13stick+pipe.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("5-체인", "image/enemy/type5/14chain.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("5-너클", "image/enemy/type5/15knuckles.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("5-돌", "image/enemy/type5/16rock.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("5-쓰레기", "image/enemy/type5/17throwtrashcan.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("5-박스", "image/enemy/type5/18throwcrate.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("5-타이어", "image/enemy/type5/19throwtire.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("5-사람", "image/enemy/type5/20throwhuman.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("5-스틱던지기", "image/enemy/type5/21throw+stick+pipe.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("5-체인던지기", "image/enemy/type5/22throw+chain.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("5-너클던지기", "image/enemy/type5/23throw+knuckles.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("5-돌던지기", "image/enemy/type5/24throw+rock.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("5-쓰레기던지기", "image/enemy/type5/25throw+trashcan.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("5-박스던지기", "image/enemy/type5/26throw+crate.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("5-타이어던지기", "image/enemy/type5/27throw+tire.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("5-사람던지기 ", "image/enemy/type5/28throw+human.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
}

void loadingScene::enemyImgSix()
{
	IMG->addF("6-달리기", "images/enemy/type_6/type6-1_run.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("6-걷기", "images/enemy/type_6/type6-2_walk.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("6-펀치", "images/enemy/type_6/type6-3_punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("6-킥", "images/enemy/type_6/type6-4_kick.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("6-어퍼컷", "images/enemy/type_6/type6-5_upperCut.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("6-하이킥", "images/enemy/type_6/type6-6_highKick.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("6-달리기펀치", "images/enemy/type_6/type6-7_run+punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("6-점프", "images/enemy/type_6/type6-8_jump.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("6-점프킥", "images/enemy/type_6/type6-9_jump+kick.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("6-방어", "images/enemy/type_6/type6-10_defend.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("6-피격", "images/enemy/type_6/type6-11_beatUp.bmp", 2212, 408, 7, 2, true, RGB(255, 0, 255));
	IMG->addF("6-KO", "images/enemy/type_6/type6-12_ko.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("6-스틱", "images/enemy/type_6/type6-13_stick.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("6-체인", "images/enemy/type_6/type6-14_chain.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("6-너클", "images/enemy/type_6/type6-15_knuckle.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("6-돌", "images/enemy/type_6/type6-16_rock.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("6-쓰레기", "images/enemy/type_6/type6-17_trash.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("6-박스", "images/enemy/type_6/type6-18_box.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("6-타이어", "images/enemy/type_6/type6-19_tire.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("6-사람", "images/enemy/type_6/type6-20_human.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("6-스틱던지기", "images/enemy/type_6/type6-21_throw-knuckle.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("6-체인던지기", "images/enemy/type_6/type6-21_throw-stick.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("6-너클던지기", "images/enemy/type_6/type6-22_throw-chain.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("6-돌던지기", "images/enemy/type_6/type6-24_throw-rock.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("6-쓰레기던지기", "images/enemy/type_6/type6-25_throw-trash.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("6-박스던지기", "images/enemy/type_6/type6-26_throw-box.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("6-타이어던지기", "images/enemy/type_6/type6-27_throw-tire.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("6-사람던지기", "images/enemy/type_6/type6-28_throw-human.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));

}

void loadingScene::enemyImgSeven()
{

	{IMG->addF("7-달리기", "images/enemy/type_7/type7-1_run.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("7-걷기", "images/enemy/type_7/type7-2_walk.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("7-펀치", "images/enemy/type_7/type7-3_punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("7-킥", "images/enemy/type_7/type7-4_kick.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("7-어퍼컷", "images/enemy/type_7/type7-5_upperCut.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("7-하이킥", "images/enemy/type_7/type7-6_highKick.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("7-달리기펀치", "images/enemy/type_7/type7-7_run+punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("7-점프", "images/enemy/type_7/type7-8_jump.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("7-점프킥", "images/enemy/type_7/type7-9_jump+kick.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("7-방어", "images/enemy/type_7/type7-10_defend.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("7-피격", "images/enemy/type_7/type7-11_beatUp.bmp", 2212, 408, 7, 2, true, RGB(255, 0, 255));
	IMG->addF("7-KO", "images/enemy/type_7/type7-12_ko.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("7-스틱", "images/enemy/type_7/type7-13_stick.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("7-체인", "images/enemy/type_7/type7-14_chain.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("7-너클", "images/enemy/type_7/type7-15_knuckle.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("7-돌", "images/enemy/type_7/type7-16_rock.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("7-쓰레기", "images/enemy/type_7/type7-17_trash.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("7-박스", "images/enemy/type_7/type7-18_box.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("7-타이어", "images/enemy/type_7/type7-19_tire.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("7-사람", "images/enemy/type_7/type7-20_human.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("7-스틱던지기", "images/enemy/type_7/type7-21_throw-stick.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("7-체인던지기", "images/enemy/type_7/type7-22_throw-chain.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("7-너클던지기", "images/enemy/type_7/type7-23_throw-knucle.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("7-돌던지기", "images/enemy/type_7/type7-24_throw-rock.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("7-쓰레기던지기", "images/enemy/type_7/type7-25_throw-trash.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("7-박스던지기", "images/enemy/type_7/type7-26_throw-box.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("7-타이어던지기", "images/enemy/type_7/type7-27_throw-tire.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("7-사람던지기", "images/enemy/type_7/type7-28_throw-human.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255)); }
}

void loadingScene::enemyImgEight()
{

	IMG->addF("8-달리기", "images/enemy/type_8/type8-1_run.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("8-걷기", "images/enemy/type_8/type8-2_walk.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("8-펀치", "images/enemy/type_8/type8-3_punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("8-킥", "images/enemy/type_8/type8-4_kick.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("8-어퍼컷", "images/enemy/type_8/type8-5_upperCut.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("8-하이킥", "images/enemy/type_8/type8-6_highKick.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("8-달리기펀치", "images/enemy/type_8/type8-7_run+punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("8-점프", "images/enemy/type_8/type8-8_jump.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("8-점프킥", "images/enemy/type_8/type8-9_jump+kick.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("8-방어", "images/enemy/type_8/type8-10_defend.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("8-피격", "images/enemy/type_8/type8-11_beatUp.bmp", 2212, 408, 7, 2, true, RGB(255, 0, 255));
	IMG->addF("8-KO", "images/enemy/type_8/type8-12_ko.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("8-스틱", "images/enemy/type_8/type8-13_stick.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("8-체인", "images/enemy/type_8/type8-14_chain.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("8-너클", "images/enemy/type_8/type8-15_knuckle.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("8-돌", "images/enemy/type_8/type8-16_rock.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("8-쓰레기", "images/enemy/type_8/type8-17_trash.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("8-박스", "images/enemy/type_8/type8-18_box.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("8-타이어", "images/enemy/type_8/type8-19_tire.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("8-사람", "images/enemy/type_8/type8-20_human.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("8-스틱던지기", "images/enemy/type_8/type8-21_throw-knuckle.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("8-체인던지기", "images/enemy/type_8/type8-21_throw-stick.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("8-너클던지기", "images/enemy/type_8/type8-22_throw-chain.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("8-돌던지기", "images/enemy/type_8/type8-24_throw-rock.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("8-쓰레기던지기", "images/enemy/type_8/type8-25_throw-trash.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("8-박스던지기", "images/enemy/type_8/type8-26_throw-box.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("8-타이어던지기", "images/enemy/type_8/type8-27_throw-tire.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("8-사람던지기", "images/enemy/type_8/type8-28_throw-human.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
}

void loadingScene::enemyImgNine()
{
	IMG->addF("9-달리기", "images/enemy/type_9/type9-1_run.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("9-걷기", "images/enemy/type_9/type9-2_walk.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("9-펀치", "images/enemy/type_9/type9-3_punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("9-킥", "images/enemy/type_9/type9-4_kick.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("9-어퍼컷", "images/enemy/type_9/type9-5_upperCut.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("9-하이킥", "images/enemy/type_9/type9-6_highKick.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("9-달리기펀치", "images/enemy/type_9/type9-7_run+punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("9-점프", "images/enemy/type_9/type9-8_jump.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("9-점프킥", "images/enemy/type_9/type9-9_jump+kick.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("9-방어", "images/enemy/type_9/type9-10_defend.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("9-피격", "images/enemy/type_9/type9-11_beatUp.bmp", 2212, 408, 7, 2, true, RGB(255, 0, 255));
	IMG->addF("9-KO", "images/enemy/type_9/type9-12_ko.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("9-스틱", "images/enemy/type_9/type9-13_stick.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("9-체인", "images/enemy/type_9/type9-14_chain.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("9-너클", "images/enemy/type_9/type9-15_knuckle.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("9-돌", "images/enemy/type_9/type9-16_rock.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("9-쓰레기", "images/enemy/type_9/type9-17_trash.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("9-박스", "images/enemy/type_9/type9-18_box.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("9-타이어", "images/enemy/type_9/type9-19_tire.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("9-사람", "images/enemy/type_9/type9-20_human.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("9-스틱던지기", "images/enemy/type_9/type9-21_throw-stick.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("9-체인던지기", "images/enemy/type_9/type9-22_throw-chain.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("9-너클던지기", "images/enemy/type_9/type9-23_throw-knucle.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("9-돌던지기", "images/enemy/type_9/type9-24_throw-rock.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("9-쓰레기던지기", "images/enemy/type_9/type9-25_throw-trash.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("9-박스던지기", "images/enemy/type_9/type9-26_throw-box.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("9-타이어던지기", "images/enemy/type_9/type9-27_throw-tire.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("9-사람던지기", "images/enemy/type_9/type9-28_throw-human.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
}

void loadingScene::enemyImgBoss()
{
	IMG->addF("보스-달리기", "images/enemy/type_boss/boss-1_run.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-걷기", "images/enemy/type_boss/boss-2_walk.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-펀치", "images/enemy/type_boss/boss-3_punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-킥", "images/enemy/type_boss/boss-4_kick.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-어퍼컷", "images/enemy/type_boss/boss-5_upperCut.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-하이킥", "images/enemy/type_boss/boss-6_highKick.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-달리기펀치", "images/enemy/type_boss/boss-7_run+punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-점프", "images/enemy/type_boss/boss-8_jump.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-점프킥", "images/enemy/type_boss/boss-9_jump+kick.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-방어", "images/enemy/type_boss/boss-10_defend.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-피격", "images/enemy/type_boss/boss-11_beatUp.bmp", 2212, 408, 7, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-KO", "images/enemy/type_boss/boss-12_ko.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-스틱", "images/enemy/type_boss/boss-13_stick.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-체인", "images/enemy/type_boss/boss-14_chain.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-너클", "images/enemy/type_boss/boss-15_knuckle.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-돌", "images/enemy/type_boss/boss-16_rock.bmp", 1264, 408, 4, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-쓰레기", "images/enemy/type_boss/boss-17_trash.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-박스", "images/enemy/type_boss/boss-18_box.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-타이어", "images/enemy/type_boss/boss-19_tire.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-사람", "images/enemy/type_boss/boss-20_human.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-스틱던지기", "images/enemy/type_boss/boss-21_throw-stick.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-체인던지기", "images/enemy/type_boss/boss-22_throw-chain.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-너클던지기", "images/enemy/type_boss/boss-23_throw-knucle.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-돌던지기", "images/enemy/type_boss/boss-24_throw-rock.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-쓰레기던지기", "images/enemy/type_boss/boss-25_throw-trash.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-박스던지기", "images/enemy/type_boss/boss-26_throw-box.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-타이어던지기", "images/enemy/type_boss/boss-27_throw-tire.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
	IMG->addF("보스-사람던지기", "images/enemy/type_boss/boss-28_throw-human.bmp", 1896, 408, 6, 2, true, RGB(255, 0, 255));
}

void loadingScene::wpImg()
{
	IMG->addF("쓰레기통", "images/weapon/can.bmp", 256, 64, 4, 1, true, RGB(255, 0, 255));
	IMG->addF("체인", "images/weapon/chain.bmp", 432, 72, 6, 1, true, RGB(255, 0, 255));
	IMG->addF("박스", "images/weapon/crate.bmp", 480, 64, 6, 1, true, RGB(255, 0, 255));
	IMG->addF("너클", "images/weapon/knuckles.bmp", 56, 32, 2, 1, true, RGB(255, 0, 255));
	IMG->addF("파이프", "images/weapon/pipe.bmp", 256, 64, 4, 1, true, RGB(255, 0, 255));
	IMG->addF("돌", "images/weapon/rock.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMG->addF("스틱", "images/weapon/stick.bmp", 256, 64, 4, 1, true, RGB(255, 0, 255));
	IMG->addF("타이어", "images/weapon/tire.bmp", 384, 64, 6, 1, true, RGB(255, 0, 255));
}
