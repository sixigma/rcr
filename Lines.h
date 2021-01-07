#pragma once
#include "gameNode.h"

class Lines : public gameNode
{
private:
	int
		CNT,		//글자가 나오는 속도에대한 인터벌
		STR_IDX,	//현재까지 출력된 문자열의 순번, 번호 , 인덱스
		FONT_SIZE
		;

	float
		CLOCK,		//띄어지는 초단위 인터벌
		CLOCK_1
		;

	bool 
		APPROACH,			//다 출력됐을때와 안됐을때 접근제한 이거 없으면 터짐
		ALIVE,
		LAUNCH_COMPLETE,	//텍스트를 모두 띄었다는 트리거 bool 변수
		KILL_COMPLETE		//텍스트를 모두 죽였다는 트리거 bool 변수
		;

	char OUTPUT_LINE[256];	//실제로 출력되는 대사를 가지고있는 문자열

	string SUBSTR_LINE;		//입력됀 대사를 인덱스 0~n 까지의 문자를 담아두는 문자열
	string C_STR_LINE;		//SUBSTR_LINE가 가지고있는 string형 문자열을 char형으로 바꿔저장하는 문자열 없으면 외계어뜸

	RECT LINE_RECT;			//대사의 범위를 지정해주는 렉트

	void launcher_Line();
	void kill_Line();

public:
	Lines();
	~Lines();

	virtual HRESULT init(RECT _rect, int _fontsize, bool _alive, int _time, string _Lines);
	virtual void release();
	virtual void update();
	virtual void render();

	bool getDeadTrigger() { return KILL_COMPLETE; }

};