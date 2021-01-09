#pragma once
#include "singleton.h"
#include "image.h"
#include <map>
#include <unordered_map>
#include <functional>

class imageManager : public singleton<imageManager>
{
private:
	typedef map<string, image*>				imageList;
	typedef map<string, image*>::iterator	imageListIter;

private:
	imageList _imageList;
	map<string, function<void()>> _availableFuncs;
	unordered_multimap<LONG, function<void()>> _funcsToCall;
	vector<LONG> _funcListKeys;

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

	void frameRender(string strKey, HDC hDC, int destX, int destY);

	void frameRender(string strKey, HDC hDC, int destX, int destY,
		int currentFrameX, int currentFrameY);

	void adjFrameRender(string strKey, HDC hDC, int destX, int destY, int currentFrameX, int currentFrameY, int adjWidth, int adjHeight);

	void alphaRender(string strKey, HDC hDC, BYTE alpha);
	void alphaRender(string strKey, HDC hDC, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hDC, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight, BYTE alpha);

	void aniRender(string strKey, HDC hDC, int destX, int destY, animation* anim);

	void loopRender(string strKey, HDC hDC, const LPRECT drawArea, int offSetX, int offSetY);

	template<typename...Args>
	void renderZ(LONG zIndex, image* img, Args... params);
	template<typename...Args>
	void frameRenderZ(LONG zIndex, image* img, Args... params);
	template<typename...Args>
	void adjFrameRenderZ(LONG zIndex, image* img, Args... params);
	template<typename...Args>
	void alphaRenderZ(LONG zIndex, image* img, Args... params);
	template<typename...Args>
	void aniRenderZ(LONG zIndex, image* img, Args... params);
	template<typename...Args>
	void loopRenderZ(LONG zIndex, image* img, Args... params);

	template<typename...Args>
	void renderZ(LONG zIndex, string strKey, Args... params);
	template<typename...Args>
	void frameRenderZ(LONG zIndex, string strKey, Args... params);
	template<typename...Args>
	void adjFrameRenderZ(LONG zIndex, string strKey, Args... params);
	template<typename...Args>
	void alphaRenderZ(LONG zIndex, string strKey, Args... params);
	template<typename...Args>
	void aniRenderZ(LONG zIndex, string strKey, Args... params);
	template<typename...Args>
	void loopRenderZ(LONG zIndex, string strKey, Args... params);

	void execZ();
};


// 참고: variadic templates
template<typename ...Args>
inline void imageManager::renderZ(LONG zIndex, image* img, Args ...params)
{
	if (img == nullptr) return;
	if (sizeof...(params) == 0) return;
	function<void()> func = [img, params...]() { return img->render(params...); };
	if (func == NULL) return;
	_funcsToCall.insert(make_pair(zIndex, func));
}

template<typename ...Args>
inline void imageManager::frameRenderZ(LONG zIndex, image* img, Args ...params)
{
	if (img == nullptr) return;
	if (sizeof...(params) == 0) return;
	function<void()> func = [img, params...]() { return img->frameRender(params...); };
	if (func == NULL) return;
	_funcsToCall.insert(make_pair(zIndex, func));
}

template<typename ...Args>
inline void imageManager::adjFrameRenderZ(LONG zIndex, image* img, Args ...params)
{
	if (img == nullptr) return;
	if (sizeof...(params) == 0) return;
	function<void()> func = [img, params...]() { return img->adjFrameRender(params...); };
	if (func == NULL) return;
	_funcsToCall.insert(make_pair(zIndex, func));
}

template<typename ...Args>
inline void imageManager::alphaRenderZ(LONG zIndex, image* img, Args ...params)
{
	if (img == nullptr) return;
	if (sizeof...(params) == 0) return;
	function<void()> func = [img, params...]() { return img->alphaRender(params...); };
	if (func == NULL) return;
	_funcsToCall.insert(make_pair(zIndex, func));
}

template<typename ...Args>
inline void imageManager::aniRenderZ(LONG zIndex, image* img, Args ...params)
{
	if (img == nullptr) return;
	if (sizeof...(params) == 0) return;
	function<void()> func = [img, params...]() { return img->aniRender(params...); };
	if (func == NULL) return;
	_funcsToCall.insert(make_pair(zIndex, func));
}

template<typename ...Args>
inline void imageManager::loopRenderZ(LONG zIndex, image* img, Args ...params)
{
	if (img == nullptr) return;
	if (sizeof...(params) == 0) return;
	function<void()> func = [img, params...]() { return img->loopRender(params...); };
	if (func == NULL) return;
	_funcsToCall.insert(make_pair(zIndex, func));
}

template<typename ...Args>
inline void imageManager::renderZ(LONG zIndex, string strKey, Args ...params)
{
	image* img = find(strKey); if (img == nullptr) return;
	if (sizeof...(params) == 0) return;
	function<void()> func = [img, params...]() { return img->render(params...); };
	if (func == NULL) return;
	_funcsToCall.insert(make_pair(zIndex, func));
}

template<typename ...Args>
inline void imageManager::frameRenderZ(LONG zIndex, string strKey, Args ...params)
{
	image* img = find(strKey); if (img == nullptr) return;
	if (sizeof...(params) == 0) return;
	function<void()> func = [img, params...]() { return img->frameRender(params...); };
	if (func == NULL) return;
	_funcsToCall.insert(make_pair(zIndex, func));
}

template<typename ...Args>
inline void imageManager::adjFrameRenderZ(LONG zIndex, string strKey, Args ...params)
{
	image* img = find(strKey); if (img == nullptr) return;
	if (sizeof...(params) == 0) return;
	function<void()> func = [img, params...]() { return img->adjFrameRender(params...); };
	if (func == NULL) return;
	_funcsToCall.insert(make_pair(zIndex, func));
}

template<typename ...Args>
inline void imageManager::alphaRenderZ(LONG zIndex, string strKey, Args ...params)
{
	image* img = find(strKey); if (img == nullptr) return;
	if (sizeof...(params) == 0) return;
	function<void()> func = [img, params...]() { return img->alphaRender(params...); };
	if (func == NULL) return;
	_funcsToCall.insert(make_pair(zIndex, func));
}

template<typename ...Args>
inline void imageManager::aniRenderZ(LONG zIndex, string strKey, Args ...params)
{
	image* img = find(strKey); if (img == nullptr) return;
	if (sizeof...(params) == 0) return;
	function<void()> func = [img, params...]() { return img->aniRender(params...); };
	if (func == NULL) return;
	_funcsToCall.insert(make_pair(zIndex, func));
}

template<typename ...Args>
inline void imageManager::loopRenderZ(LONG zIndex, string strKey, Args ...params)
{
	image* img = find(strKey); if (img == nullptr) return;
	if (sizeof...(params) == 0) return;
	function<void()> func = [img, params...]() { return img->loopRender(params...); };
	if (func == NULL) return;
	_funcsToCall.insert(make_pair(zIndex, func));
}