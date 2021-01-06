#include "stdafx.h"
#include "imageManager.h"


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

image * imageManager::addF(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
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

image * imageManager::addF(string strKey, const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
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

void imageManager::loopRender(string strKey, HDC hDC, const LPRECT drawArea, int offSetX, int offSetY)
{
	image* img = find(strKey);
	if (img) img->loopRender(hDC, drawArea, offSetX, offSetY);
}
