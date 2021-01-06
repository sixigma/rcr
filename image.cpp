#include "stdafx.h"
#include "image.h"

//#pragma comment(lib, "msimg32.lib")

image::image(): _imageInfo(NULL), _fileName(NULL), _trans(FALSE), _transColor(RGB(0,0,0)) {}


image::~image() {}

HRESULT image::init(int width, int height)
{
	if (_imageInfo != NULL) release();

	HDC hDC = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hDC);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hDC, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hDC);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hDC, WINW, WINH);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINW;
	_blendImage->height = WINH;
	
	if (_imageInfo == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hDC);
	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL) release();

	HDC hDC = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hDC);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	size_t len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hDC);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hDC, width, height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = width;
	_blendImage->height = height;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hDC);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL) release();

	HDC hDC = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hDC);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	size_t len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hDC);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hDC, width, height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = width;
	_blendImage->height = height;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hDC);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL) release();

	HDC hDC = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hDC);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	size_t len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hDC);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hDC, width, height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = width;
	_blendImage->height = height;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hDC);

	return S_OK;
}

void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DEL(_imageInfo);
		SAFE_DEL(_fileName);
		SAFE_DEL(_blendImage);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}

}

void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void image::render(HDC hDC)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hDC,
			_currOrg.x,
			_currOrg.y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);
	}
	else
	{
		BitBlt(hDC,
			_currOrg.x,
			_currOrg.y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			SRCCOPY);
	}
}

void image::render(HDC hDC, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hDC,
			destX - _currOrg.x,
			destY - _currOrg.y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);
	}
	else
	{
		BitBlt(hDC,
			destX - _currOrg.x,
			destY - _currOrg.y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			SRCCOPY);
	}


}

void image::render(HDC hDC, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hDC,
			destX - _currOrg.x,
			destY - _currOrg.y,
			srcWidth,
			srcHeight,
			_imageInfo->hMemDC,
			srcX, srcY,
			srcWidth,
			srcHeight,
			_transColor
		);
	}
	else
	{
		BitBlt(hDC,
			destX - _currOrg.x,
			destY - _currOrg.y,
			srcWidth,
			srcHeight,
			_imageInfo->hMemDC,
			srcX, srcY,
			SRCCOPY);
	}
}

void image::frameRender(HDC hDC, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hDC,
			destX - _currOrg.x,
			destY - _currOrg.y,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth, 
			_imageInfo->currentFrameY * _imageInfo->frameHeight,					
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		BitBlt(hDC,
			   destX - _currOrg.x,
			   destY - _currOrg.y,
			   _imageInfo->frameWidth,
			   _imageInfo->frameHeight,
			   _imageInfo->hMemDC,
			   _imageInfo->currentFrameX * _imageInfo->frameWidth,
			   _imageInfo->currentFrameY * _imageInfo->frameHeight,
			   SRCCOPY);
	}
}

void image::frameRender(HDC hDC, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hDC,
			destX - _currOrg.x,
			destY - _currOrg.y,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		BitBlt(hDC,
			   destX - _currOrg.x,
			   destY - _currOrg.y,
			   _imageInfo->frameWidth,
			   _imageInfo->frameHeight,
			   _imageInfo->hMemDC,
			   _imageInfo->currentFrameX * _imageInfo->frameWidth,
			   _imageInfo->currentFrameY * _imageInfo->frameHeight,
			   SRCCOPY);
	}
}

void image::adjFrameRender(HDC hDC, int destX, int destY, int currentFrameX, int currentFrameY, int adjWidth, int adjHeight)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hDC,
			destX - _currOrg.x,
			destY - _currOrg.y,
			adjWidth,
			adjHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		SetStretchBltMode(hDC, HALFTONE);
		StretchBlt(hDC,
				   destX - _currOrg.x,
				   destY - _currOrg.y,
				   adjWidth,
				   adjHeight,
				   _imageInfo->hMemDC,
				   _imageInfo->currentFrameX * _imageInfo->frameWidth,
				   _imageInfo->currentFrameY * _imageInfo->frameHeight,
				   _imageInfo->frameWidth,
				   _imageInfo->frameHeight,
				   SRCCOPY
		);
	}
}

void image::alphaRender(HDC hDC, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hDC, static_cast<int>(_imageInfo->x) - _currOrg.x, static_cast<int>(_imageInfo->y) - _currOrg.y, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _transColor);

		GdiAlphaBlend(hDC, static_cast<int>(_imageInfo->x) - _currOrg.x, static_cast<int>(_imageInfo->y) - _currOrg.y, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		GdiAlphaBlend(hDC, static_cast<int>(_imageInfo->x) - _currOrg.x, static_cast<int>(_imageInfo->y) - _currOrg.y, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hDC, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hDC, destX - _currOrg.x, destY - _currOrg.y, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _transColor);

		GdiAlphaBlend(hDC, destX - _currOrg.x, destY - _currOrg.y, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		GdiAlphaBlend(hDC, destX - _currOrg.x, destY - _currOrg.y, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hDC, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	if (srcWidth == 0 && srcHeight == 0) { srcWidth = _imageInfo->width - srcX; srcHeight = _imageInfo->height - srcY; }

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, srcWidth, srcHeight,
			   hDC, destX - _currOrg.x, destY - _currOrg.y, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, srcWidth, srcHeight,
						  _imageInfo->hMemDC, srcX, srcY, srcWidth, srcHeight,
						  _transColor);

		GdiAlphaBlend(hDC, destX - _currOrg.x, destY - _currOrg.y, srcWidth, srcHeight,
					  _blendImage->hMemDC, 0, 0, srcWidth, srcHeight,
					  _blendFunc);
	}
	else
	{
		GdiAlphaBlend(hDC, destX - _currOrg.x, destY - _currOrg.y, srcWidth, srcHeight,
					  _imageInfo->hMemDC, srcX, srcY, srcWidth, srcHeight,
					  _blendFunc);
	}
}

void image::aniRender(HDC hDC, int destX, int destY, animation* anim)
{
	render(hDC, destX, destY, anim->getFramePos().x, anim->getFramePos().y,
		anim->getFrameWidth(), anim->getFrameHeight());
}

void image::loopRender(HDC hDC, const LPRECT drawArea, int offSetX, int offSetY)
{
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	int srcWidth;
	int srcHeight;

	RECT rcDest;
	RECT rcSrc;

	int drawAreaX = drawArea->left;					
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawAreaX;
	int drawAreaH = drawArea->bottom - drawAreaY;

	for (int y = 0; y < drawAreaH; y += srcHeight)
	{
		rcSrc.top = (y + offSetY) % _imageInfo->height;
		rcSrc.bottom = _imageInfo->height;

		srcHeight = rcSrc.bottom - rcSrc.top;

		if (y + srcHeight > drawAreaH)
		{
			rcSrc.bottom -= (y + srcHeight) - drawAreaH;
			srcHeight = rcSrc.bottom - rcSrc.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + srcHeight;

		for (int x = 0; x < drawAreaW; x += srcWidth)
		{
			rcSrc.left = (x + offSetX) % _imageInfo->width;
			rcSrc.right = _imageInfo->width;

			srcWidth = rcSrc.right - rcSrc.left;

			if (x + srcWidth > drawAreaW)
			{
				rcSrc.right -= (x + srcWidth) - drawAreaW;
				srcWidth = rcSrc.right - rcSrc.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + srcWidth;

			render(hDC, rcDest.left, rcDest.top,
				rcSrc.left, rcSrc.top,
				rcSrc.right - rcSrc.left,
				rcSrc.bottom - rcSrc.top);
		}
	}
}

COLORREF image::changeColor(COLORREF originalColor, COLORREF newColor)
{
	HDC hTempDC = CreateCompatibleDC(_imageInfo->hMemDC);
	BITMAPINFO bI = { 0 };
	DWORD* ptrToBitmapBits = nullptr;
	bI.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bI.bmiHeader.biBitCount = 32;
	bI.bmiHeader.biWidth = _imageInfo->width;
	bI.bmiHeader.biHeight = _imageInfo->height;
	bI.bmiHeader.biCompression = BI_RGB;
	bI.bmiHeader.biPlanes = 1;

	BYTE originalB = static_cast<BYTE>((originalColor >> 16) & 0xFF);
	BYTE originalG = static_cast<BYTE>((originalColor >> 8) & 0xFF);
	BYTE originalR = static_cast<BYTE>((originalColor) & 0xFF);

	BYTE newB = static_cast<BYTE>((newColor >> 16) & 0xFF);
	BYTE newG = static_cast<BYTE>((newColor >> 8) & 0xFF);
	BYTE newR = static_cast<BYTE>((newColor) & 0xFF);

	HBITMAP hTempBitmap = CreateDIBSection(hTempDC, &bI, DIB_RGB_COLORS, reinterpret_cast<void**>(&ptrToBitmapBits), 0, 0);
	if (hTempBitmap == NULL) return originalColor;
	HBITMAP hTempOldBitmap = (HBITMAP)SelectObject(hTempDC, hTempBitmap);
	BitBlt(hTempDC, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	size_t area = static_cast<size_t>(_imageInfo->width * _imageInfo->height);
	for (size_t i = 0; i < area; ++i)
	{
		BYTE* ptrToCurrPixel = reinterpret_cast<BYTE*>(&ptrToBitmapBits[i]);
		if ((ptrToCurrPixel[0] == originalB) && (ptrToCurrPixel[1] == originalG) && (ptrToCurrPixel[2] == originalR))
		{
			ptrToCurrPixel[0] = newB; ptrToCurrPixel[1] = newG; ptrToCurrPixel[2] = newR;
		}
	}
	BitBlt(_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hTempDC, 0, 0, SRCCOPY);
	DeleteObject(SelectObject(hTempDC, hTempOldBitmap));
	DeleteDC(hTempDC);
	return newColor;
}

