#pragma once
#include "singleton.h"
#include "Lines.h"
#include <vector>

class LineManager : public singleton<LineManager>
{
private:
	vector<Lines*> _vLine;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void CreateLine(POINT _rect, int _fontsize, string _Lines, int _time = 99999);

	void AllDeleteLine();

};

