#pragma once
#include "singleton.h"
#include "image.h"
#include <map>

class imageManager : public singleton<imageManager>
{
private:
	typedef map<string, image*>				imageList;
	typedef map<string, image*>::iterator	imageListIter;

private:
	imageList _imageList;

public:
	imageManager();
	~imageManager();

	HRESULT init();
	void release();

	// 이미지 추가
	image* add(string strKey, int width, int height);

	// 이미지 추가
	image* add(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);

	// 프레임 이미지 추가
	image* addF(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY,
		BOOL trans, COLORREF transColor);

	// 프레임 이미지 추가
	image* addF(string strKey, const char* fileName, int width, int height, int frameX, int frameY,
		BOOL trans, COLORREF transColor);

	// 이미지 찾기
	image* find(string strKey);

	// 이미지 제거
	BOOL del(string strKey);

	// 이미지 전부 제거
	BOOL delAll();

	void render(string strKey, HDC hDC);
	void render(string strKey, HDC hDC, int destX, int destY);
	void render(string strKey, HDC hDC, int destX, int destY, int sourX, int sourY, int srcWidth, int srcHeight);

	void loopRender(string strKey, HDC hDC, const LPRECT drawArea, int offSetX, int offSetY);
};

