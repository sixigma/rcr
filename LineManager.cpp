#include "stdafx.h"
#include "LineManager.h"


HRESULT LineManager::init()
{
	return S_OK;
}

void LineManager::release()
{

}

void LineManager::update()
{
	for (int i = 0; i < _vLine.size(); )
	{
		if(_vLine[i]->getDead())
		{
			_vLine.erase(_vLine.begin() + i);
		}
		else
		{
			_vLine[i]->update();
			i++;
		}
	}
}

void LineManager::render()
{
	for (int i = 0; i < _vLine.size(); i++)
	{
		_vLine[i]->render();
	}
}

void LineManager::CreateLine(POINT _rect, int _fontsize, string _Lines, int _time)
{
	Lines* line;
	line = new Lines;

	line->init(_rect, _fontsize, _time, _Lines);

	_vLine.push_back(line);
}

void LineManager::AllDeleteLine()
{
	_vLine.clear();
}