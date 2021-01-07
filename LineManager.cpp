#include "stdafx.h"
#include "LineManager.h"
#include <vector>

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
		if (_vLine[i]->getDeadTrigger())
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

void LineManager::CreateLine(RECT _rect, int _fontsize, bool _alive, int _time, string _Lines)
{
	Lines* line;
	line = new Lines;

	line->init(_rect, _fontsize, _alive, _time, _Lines);

	_vLine.push_back(line);
}

void LineManager::AllDeleteLine()
{
	_vLine.clear();
}