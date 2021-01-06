#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(int x, int y, int width, int height)
{
	_x = static_cast<float>(x);
	_y = static_cast<float>(y);

	_rctProgress = MakeRct(x, y, width, height);

	_progressBarFront = IMG->add("frontBar", "images/progressBars/fullBar.bmp", width, height, true, RGB(255, 0, 255));
	_progressBarBack = IMG->add("backBar", "images/progressBars/emptyBar.bmp", width, height, true, RGB(255, 0, 255));

	_width = static_cast<float>(_progressBarFront->getWidth());

	return S_OK;
}

void progressBar::release()
{

}

void progressBar::update()
{
	_rctProgress = MakeRctC(static_cast<int>(_x), static_cast<int>(_y), _progressBarFront->getWidth(), _progressBarFront->getHeight());
}

void progressBar::render()
{
	IMG->render("backBar", getMemDC(),
		_rctProgress.left + _progressBarBack->getWidth() / 2,
		static_cast<int>(_y) + _progressBarBack->getHeight() / 2, 0, 0,
		_progressBarBack->getWidth(), _progressBarBack->getHeight());

	IMG->render("frontBar", getMemDC(),
		_rctProgress.left + _progressBarFront->getWidth() / 2,
		static_cast<int>(_y) + _progressBarFront->getHeight() / 2, 0, 0,
		static_cast<int>(_width), _progressBarFront->getHeight());
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBack->getWidth();
}
