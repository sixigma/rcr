#pragma once
#include "animation.h"

class image
{
public:

	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,
		LOAD_FILE,
		LOAD_EMPTY
	};

	typedef struct tagImageInfo
	{
		DWORD resID;
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float x;
		float y;
		int width;
		int height;
		int currentFrameX;
		int currentFrameY;
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		BYTE loadType;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}

	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;	
	CHAR*			_fileName;
	BOOL			_trans;
	COLORREF		_transColor;
	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO	_blendImage;
public:

	image();
	~image();

	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const char* fileName, float x, float y,
		int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const char* fileName, int width, int height, 
		int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	void release();
	void setTransColor(BOOL trans, COLORREF transColor);


	void render(HDC hDC);
	void render(HDC hDC, int destX, int destY);
	void render(HDC hDC, int destX, int destY, int srcX, int srcY,
		int srcWidth, int srcHeight);

	void frameRender(HDC hDC, int destX, int destY);

	void frameRender(HDC hDC, int destX, int destY,
		int currentFrameX, int currentFrameY);

	void adjFrameRender(HDC hDC, int destX, int destY, int currentFrameX, int currentFrameY, int adjWidth, int adjHeight);

	void alphaRender(HDC hDC, BYTE alpha);
	void alphaRender(HDC hDC, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hDC, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight, BYTE alpha);

	void aniRender(HDC hDC, int destX, int destY, animation* anim);

	void loopRender(HDC hDC, const LPRECT drawArea, int offSetX, int offSetY);

	// 이미지 특정 색을 변경하고 새 색을 반환하는 함수(32 비트 비트맵 전용)
	COLORREF changeColor(COLORREF originalColor, COLORREF newColor);

	inline HDC getMemDC() { return _imageInfo->hMemDC; }


	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ?
			_imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ?
			_imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;

		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;

		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}


	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }

	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }

};

