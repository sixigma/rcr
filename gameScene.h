#pragma once
#include "gameNode.h"


constexpr int VIEWPORT_UPDATE_OFFSET = 2;

class player;
class map_;
class item;

class gameScene : public gameNode
{
private:
	static player* _p;

	static vector<map_*> _mapList;
	static map_* _currMap;

	static int _prevMapNum, _mapNum, _prevshopNum, _shopNum;

	static int _countForReEnablingKeyInput;

	int _topBoxAdjX; // 상단 영역 이동 시 사용하는 변수
	int _bottomBoxAdjX; // 하단 영역 이동 시 사용하는 변수

	int _countForFading; // 페이드아웃, 페이드인 적용 시 사용하는 변수

	// 상단, 하단 영역용 글꼴 핸들
	HFONT _hFont, _hOFont;

	// 상하단 영역용 DC 핸들, 비트맵 핸들
	HDC _hBoxDC;
	HBITMAP _hBoxBitmap, _hOBoxBitmap;
	
	// 상단 영역 표시 정보 전환용 변수
	bool _shouldShowMoneyOnTop;
	RECT _topBoxTextArea;

	// 하단 영역 화살표 출력용 변수
	bool _shouldShowBottomBoxArrow;
	vector<POINT> _bottomBoxArrowPos;
	BYTE _bottomBoxArrowPosIdx;
	vector<RECT> _bottomBoxTextArea;

	// 상단 영역 정보 출력용 변수
	string _hPString;

	// 주 화면 영역용 변수(메뉴)
	BYTE _currMenuIdx;
	vector<item*> _itemPtrList;
	vector<string> _itemList;
	vector<RECT> _itemNameTextArea;
	bool _shouldShowMainBoxArrow;
	vector<POINT> _mainBoxArrowPos;
	BYTE _mainBoxArrowPosIdx;

	// 특정 메뉴용 변수
	int _bottomBoxCountForBelongings;
	int _bottomBoxCountForVolume;
	RECT _volumeRct[6];
	HBRUSH _hBrush1, _hBrush2, _hOBrush;
	int _bottomBoxCountForLevels;
	int _prevYPosForLevels, _prevXPosForLevels, _yPosForLevels, _xPosForLevels;
	int _bottomBoxCountForStatus;
	int _bottomBoxCountForHelp;
public:
	gameScene();
	~gameScene() override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	static void setMapNum(int num) { _mapNum = num; }
	static void setShopNum(int num) { _shopNum = num; }
	static int getShopNum() { return _shopNum; }
	static int getPrevMapNum() { return _prevMapNum; }
	static void goToMap(int num);
	void updateViewport(int x, int y);
	void setViewport(int x, int y);

	void drawTopSecondBox(); // 상단 소지금 영역 출력 함수
	void drawBottomSecondBox(); // 하단 메뉴 영역 출력 함수

	void showBelongingsScr();
	void showVolumeScr();
	void showLevelsScr();
	void showStatusScr();
	void showHelpScr();
	void updateMenuScr(BYTE idx);
	void removeMenuScr(BYTE prevBottomBoxArrowPosIdx);
};

