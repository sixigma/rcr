#pragma once
#include "gameNode.h"
#include "Lines.h"

class LineManager : public gameNode
{
private:
	vector<Lines*> _vLine;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void CreateLine(RECT _rect, int _fontsize, bool _alive, int _time, string _Lines);

	void AllDeleteLine();

};

