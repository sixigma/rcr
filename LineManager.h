
#pragma once
#include "singleton.h"
#include "Lines.h"
#include <fstream>
#include <vector>

enum Trigger
{
	NO,			//그냥 초기화
	P_DIE,		//플레이어가 죽었을때
	E_DIE,		//적이 죽었을때
	E_HELP,		//적이 도망
	MAP1,		//맵1 일때
	MAP2,		//맵2 일때
	MAP3,		//맵3 일때
	MAP4,		//맵4 일때
	MAP5		//맵5 일떄
};

class LineManager : public singleton<LineManager>
{
private:
	bool POSITION;
	vector<Lines*> _vLine;

public:
	LineManager();
	~LineManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void CreateLine(POINT _rect, string _Lines, string _name, bool _bold, int _time = 99999);
	void CorrectLine(string _name, POINT _pos);
	void trgLine(Trigger _trg, string _name = "no");

	void AllDeleteLine();

	string txtFind(string _line, string _name = "no", int _plusLine = 1);

};

