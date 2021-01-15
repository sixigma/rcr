
#include "stdafx.h"
#include "LineManager.h"

LineManager::LineManager() :
	POSITION(false)
{
	AddFontResource("RCR_Mono2.ttf");
}
LineManager::~LineManager()
{

}

HRESULT LineManager::init()
{
	IMG->addF("타일셋", "images/tileset/tileset.bmp", 512, 256, 16, 8, true, RGB(0, 0, 0));
	return S_OK;
}

void LineManager::release()
{
	RemoveFontResourceA("RCR_Mono2.ttf");
	AllDeleteLine();
}

void LineManager::update()
{
	for (int i = 0; i < _vLine.size(); )
	{
		if (_vLine[i]->getDead())
		{
			SAFE_DEL(_vLine[i]);
			_vLine.erase(_vLine.begin() + i);
		}
		else
		{
			_vLine[i]->update();
			i++;
		}
	}
}

void LineManager::selectUpdate(string _name)
{
	for (int i = 0; i < _vLine.size(); i++)
	{
		if (_vLine[i]->getName() != _name) continue;
		if (_vLine[i]->getDead())
		{
			SAFE_DEL(_vLine[i]);
			_vLine.erase(_vLine.begin() + i);
		}
		else
		{
			_vLine[i]->update();
			i++;
		}
		break;
	}
}

void LineManager::render()
{
	for (int i = 0; i < _vLine.size(); i++)
	{
		_vLine[i]->render();
	}
}

void LineManager::selectRender(string _name)
{
	for (int i = 0; i < _vLine.size(); i++)
	{
		if (_vLine[i]->getName() == _name)
		{
			_vLine[i]->render();
			return;
		}
	}
}

void LineManager::CreateLine(POINT _rect, string _Lines, string _name, bool _bold, int _time)
{
	Lines* line;
	line = new Lines;

	//line->init(_rect, _fontsize, _time, _Lines);
	line->init(_rect, _time, _Lines, _bold, _name);

	_vLine.push_back(line);
}

//그냥 딱 나오는넘
void LineManager::calmLine(POINT _rect, string _Lines)
{
	Lines* line;
	line = new Lines;

	line->init(_rect, 99998, _Lines, false, "CaLm");

	_vLine.push_back(line);
}

//얘는 현재위치에서 +, - 해주는얘
void LineManager::CorrectLine(string _name, POINT _pos)
{
	for (int i = 0; i < _vLine.size(); i++)
	{
		if (_vLine[i]->getName() == _name)
		{
			_vLine[i]->setPos(_pos);
			return;
		}
	}
}
//얘는 x, y축 자체를 입력됀 매게변수위치로 바꾸는얘
void LineManager::setPosLine(string _name, POINT _pos)
{
	for (int i = 0; i < _vLine.size(); i++)
	{
		if (_vLine[i]->getName() == _name)
		{
			_vLine[i]->setPlace(_pos);
			return;
		}
	}
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
		CreateLine(MakePt(200, 766), txtFind("<map1>"), _name, false, 2);
	}
	else if (_trg == MAP2 || _trg == MAP4 || _trg == MAP5)
	{
		CreateLine(MakePt(248, 766), txtFind("<map245>"), _name, false, 2);
	}
	else if (_trg == MAP4_2)
	{
		CreateLine(MakePt(240, 766), txtFind("<map4-2>"), _name, false, 2);
	}
	else if (_trg == MAP3)
	{
		CreateLine(MakePt(248, 766), txtFind("<map3>"), _name, false, 2);
	}
	else if (_trg == P_DIE)
	{
		CreateLine(MakePt(34, 766), txtFind("<p_die>"), _name, false, 1);
	}
	else if (_trg == E_DIE)
	{
		CreateLine(MakePt(34, (766 * (!POSITION)) + (830 * (POSITION))), "n", txtFind("<e_die>", _name, RNG->getInt(2) + 1), false, 1);
		POSITION = !POSITION;
	}
	else if (_trg == E_HELP)
	{
		CreateLine(MakePt(34, (766 * (!POSITION)) + (830 * (POSITION))), "n", txtFind("<e_help>", _name), false, 1);
		POSITION = !POSITION;
	}
}

void LineManager::AllDeleteLine()
{
	for (int i = 0; i < _vLine.size(); i++)
	{
		SAFE_DEL(_vLine[i]);
	}
	_vLine.clear();
}

void LineManager::selectDeleteLine(string _name)
{
	for (int i = 0; i < _vLine.size(); )
	{
		if (_vLine[i]->getName() == _name)
		{
			SAFE_DEL(_vLine[i]);
			_vLine.erase(_vLine.begin() + i);
			return;
		}
		else
		{
			i++;
		}
	}
}

void LineManager::selectChangeLine(string _name, int _i, char _cW)
{
	for (int i = 0; i < _vLine.size(); i++)
	{
		if (_vLine[i]->getName() == _name)
		{
			_vLine[i]->chageWord(_i, _cW);
			return;
		}
	}
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

	return _name != "no"? _name + ":" + line : line;
}