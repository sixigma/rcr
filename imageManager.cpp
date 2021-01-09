#include "stdafx.h"
#include "imageManager.h"
#include <algorithm>

imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

HRESULT imageManager::init()
{
	return S_OK;
}

void imageManager::release()
{
	delAll();
}

image* imageManager::add(string strKey, int width, int height)
{
	image* img = find(strKey);

	//해당 이미지가 있으면 그 이미지를 반환해라
	if (img) return img;
	
	//없으면 새로 하나 할당해줘라
	img = new image;

	if (FAILED(img->init(width, height)))
	{
		SAFE_DEL(img);
		return nullptr;
	}

	_imageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::add(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	image* img = find(strKey);

	//해당 이미지가 있으면 그 이미지를 반환해라
	if (img) return img;

	//없으면 새로 하나 할당해줘라
	img = new image;

	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DEL(img);
		return nullptr;
	}

	_imageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addF(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	image* img = find(strKey);

	//해당 이미지가 있으면 그 이미지를 반환해라
	if (img) return img;

	//없으면 새로 하나 할당해줘라
	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DEL(img);
		return nullptr;
	}

	_imageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addF(string strKey, const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	image* img = find(strKey);

	//해당 이미지가 있으면 그 이미지를 반환해라
	if (img) return img;

	//없으면 새로 하나 할당해줘라
	img = new image;

	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DEL(img);
		return nullptr;
	}

	_imageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::find(string strKey)
{
	imageListIter key = _imageList.find(strKey);

	//찾았다
	if (key != _imageList.end())
	{
		return key->second;
	}

	return nullptr;
}

BOOL imageManager::del(string strKey)
{
	imageListIter key = _imageList.find(strKey);

	if (key != _imageList.end())
	{
		key->second->release();
		SAFE_DEL(key->second);
		_imageList.erase(key);
		return TRUE;
	}

	return FALSE;
}

BOOL imageManager::delAll()
{
	imageListIter iter = _imageList.begin();

	for (; iter != _imageList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DEL(iter->second);
			iter = _imageList.erase(iter);
		}
		else ++iter;
	}
	_imageList.clear();
	return TRUE;
}

void imageManager::render(string strKey, HDC hDC)
{
	image* img = find(strKey);
	if (img) img->render(hDC);
}

void imageManager::render(string strKey, HDC hDC, int destX, int destY)
{
	image* img = find(strKey);
	if (img) img->render(hDC, destX, destY);
}

void imageManager::render(string strKey, HDC hDC, int destX, int destY, int sourX, int sourY, int srcWidth, int srcHeight)
{
	image* img = find(strKey);
	if (img) img->render(hDC, destX, destY, sourX, sourY, srcWidth, srcHeight);
}

void imageManager::frameRender(string strKey, HDC hDC, int destX, int destY)
{
	image* img = find(strKey);
	if (img) img->frameRender(hDC, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hDC, int destX, int destY, int currentFrameX, int currentFrameY)
{
	image* img = find(strKey);
	if (img) img->frameRender(hDC, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::adjFrameRender(string strKey, HDC hDC, int destX, int destY, int currentFrameX, int currentFrameY, int adjWidth, int adjHeight)
{
	image* img = find(strKey);
	if (img) img->adjFrameRender(hDC, destX, destY, currentFrameX, currentFrameY, adjWidth, adjHeight);
}

void imageManager::alphaRender(string strKey, HDC hDC, BYTE alpha)
{
	image* img = find(strKey);
	if (img) img->alphaRender(hDC, alpha);
}

void imageManager::alphaRender(string strKey, HDC hDC, int destX, int destY, BYTE alpha)
{
	image* img = find(strKey);
	if (img) img->alphaRender(hDC, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hDC, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight, BYTE alpha)
{
	image* img = find(strKey);
	if (img) img->alphaRender(hDC, destX, destY, srcX, srcY, srcWidth, srcHeight, alpha);
}

void imageManager::aniRender(string strKey, HDC hDC, int destX, int destY, animation* anim)
{
	image* img = find(strKey);
	if (img) img->aniRender(hDC, destX, destY, anim);
}

void imageManager::loopRender(string strKey, HDC hDC, const LPRECT drawArea, int offSetX, int offSetY)
{
	image* img = find(strKey);
	if (img) img->loopRender(hDC, drawArea, offSetX, offSetY);
}

void imageManager::execZ()
{
	if (!_funcListKeys.empty()) _funcListKeys.clear();
	if (_funcsToCall.empty()) return;
	_funcListKeys.reserve(_funcsToCall.size());

	for (auto& iter : _funcsToCall)
	{
		_funcListKeys.push_back(iter.first);
	}

	sort(_funcListKeys.begin(), _funcListKeys.end());

	for (LONG& key : _funcListKeys)
	{
		auto iterRange = _funcsToCall.equal_range(key);
		for (auto& it = iterRange.first; it != iterRange.second; ++it)
		{
			it->second();
		}
		//_funcsToCall.find(key)->second();
	}
	_funcsToCall.clear();
}

