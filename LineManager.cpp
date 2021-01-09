
#include "stdafx.h"
#include "LineManager.h"

LineManager::LineManager() :
	POSITION(false)
{
	AddFontResource("RCR.ttf");
}
LineManager::~LineManager()
{

}

HRESULT LineManager::init()
{
	return S_OK;
}

void LineManager::release()
{
	RemoveFontResourceA("RCR.ttf");
}

void LineManager::update()
{
	for (int i = 0; i < _vLine.size(); )
	{
		if (_vLine[i]->getDead())
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

/* 적 종류 */
/*
"The GENERIC DUDES' turf!"
"The FRAT GUYS's turf!"
*/

void LineManager::trgLine(Trigger _trg, string _name)
{
	if (_trg == MAP1)
	{
		CreateLine(MakePt(166, 766), 40, txtFind("<map1>"), 2);
		//CreateLine(MakePt(47, 817), 40, "적 종류", 2);
	}
	else if (_trg == MAP2 || _trg == MAP4 || _trg == MAP5)
	{
		CreateLine(MakePt(187, 766), 40, txtFind("<map245>"), 2);
	}
	else if (_trg == MAP3)
	{
		CreateLine(MakePt(229, 766), 40, txtFind("<map3>"), 2);
	}
	else if (_trg == P_DIE)
	{
		CreateLine(MakePt(34, 766), 40, txtFind("<p_die>"), 1);
	}
	else if (_trg == E_DIE)
	{
		CreateLine(MakePt(34, (766 * (!POSITION)) + (830 * (POSITION))), 40, txtFind("<e_die>", _name, RNG->getInt(2) + 1), 1);
		POSITION = !POSITION;
	}
	else if (_trg == E_HELP)
	{
		CreateLine(MakePt(34, (766 * (!POSITION)) + (830 * (POSITION))), 40, txtFind("<e_help>", _name), 1);
		POSITION = !POSITION;
	}
}

void LineManager::AllDeleteLine()
{
	_vLine.clear();
}

string LineManager::txtFind(string _line, string _name, int _plusLine)
{
	ifstream file;
	file.open("lines/lines.txt");

	string line;
	int endline = 100;

	for (int i = 0; i <= endline; i++)
	{
		getline(file, line);

		if (line == _line)
		{
			endline = i + _plusLine;
		}
	}
	file.close();

	return _name != "no" ? _name + ":" + line : line;
}