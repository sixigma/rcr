
#include "stdafx.h"
#include "Lines.h"

/*Lines::Lines() :
	CNT(0),
	STR_IDX(0),
	APPROACH(true),
	KILL_COMPLETE(false),
	LAUNCH_COMPLETE(false),
	CLOCK_1(0.0f)
{

}

Lines::~Lines()
{

}

HRESULT Lines::init(RECT _rect, int _fontsize, bool _alive, int _time, string _Lines)
{
	LINE_RECT	= _rect;		//입력받은 텍스트범위 렉트를 저장한다.
	SUBSTR_LINE = _Lines;		//입력받은 대사를 저장한다.
	FONT_SIZE	= _fontsize;	//폰트사이즈
	ALIVE		= _alive;		//TRUE일땐 특정시간만큼 있다가 없앰 FALSE일땐 계속띄움
	CLOCK		= (float)_time;	//ALIVE가 TRUE일때 몇초정도띄우고있을것인가.
	return S_OK;
}

void Lines::release()
{

}

void Lines::update()
{
	if (!ALIVE)
	{
		launcher_Line();
	}
	else if (ALIVE)
	{
		if (!LAUNCH_COMPLETE) launcher_Line();
		if (LAUNCH_COMPLETE)  CLOCK_1 += (1.0f/60.0f);	//프레임이 60fps 이므로 1/60하면 1초에 1이된다.
		if (CLOCK_1 >= CLOCK) kill_Line();
	}
}

void Lines::render()
{
	HFONT Font = CreateFont(FONT_SIZE, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "궁서체");
	HFONT oFont = (HFONT)SelectObject(getMemDC(), Font);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);

	if (LAUNCH_COMPLETE == false)	DrawText(getMemDC(), OUTPUT_LINE, strlen(OUTPUT_LINE), &LINE_RECT, DT_WORDBREAK | DT_LEFT);
	if (LAUNCH_COMPLETE)			DrawText(getMemDC(), OUTPUT_LINE, strlen(OUTPUT_LINE), &LINE_RECT, DT_WORDBREAK | DT_RIGHT);
	//DrawText(getMemDC(), OUTPUT_LINE, strlen(OUTPUT_LINE), &LINE_RECT, DT_WORDBREAK | DT_LEFT);

	SetTextColor(getMemDC(), RGB(0, 0, 0));

	SelectObject(getMemDC(), oFont);
	DeleteObject(Font);
}

void Lines::launcher_Line()
{
	if (APPROACH)
	{
		CNT = CNT % 2;

		if (!CNT)
		{	//영문 : 1byte, 한글 : 2byte
			if ((SUBSTR_LINE[STR_IDX] & 0x80) == 0x80)		//한글일때
			{
				STR_IDX += 2;	//2바이트씩 (안해주면 외계어랑 같이 뜸)
				C_STR_LINE = SUBSTR_LINE.substr(0, STR_IDX);
			}
			else											//한글이 아닐떄
			{
				STR_IDX++;		//1바이트씩
				C_STR_LINE = SUBSTR_LINE.substr(0, STR_IDX);
			}
			//만약 현재의 인덱스가 입력받은 문자열의 인덱스보다 커지거나 같아질때
			if (STR_IDX >= SUBSTR_LINE.size())
			{
				APPROACH = false;
				LAUNCH_COMPLETE = true;
				STR_IDX = 0;
				C_STR_LINE = SUBSTR_LINE.substr(0, SUBSTR_LINE.size());
			}
			//string형 문자열 C_STR_LINE을 c_str()을 이용해 char 형식으로 바꿔 OUTPUT_LINE에 저장함.
			sprintf_s(OUTPUT_LINE, "%s", C_STR_LINE.c_str());
		}
		CNT++;
	}
}

void Lines::kill_Line()
{
	if (KILL_COMPLETE == false)
	{
		CNT = CNT % 2;

		if (!CNT)
		{	//영문 : 1byte, 한글 : 2byte
			if ((SUBSTR_LINE[STR_IDX] & 0x80) == 0x80)		//한글일때
			{
				STR_IDX += 2;	//2바이트씩 (안해주면 외계어랑 같이 뜸)
				C_STR_LINE = SUBSTR_LINE.substr(STR_IDX, SUBSTR_LINE.size());
			}
			else											//한글이 아닐떄
			{
				STR_IDX++;		//1바이트씩
				C_STR_LINE = SUBSTR_LINE.substr(STR_IDX, SUBSTR_LINE.size());
			}
			//만약 현재의 인덱스가 입력받은 문자열의 인덱스보다 커지거나 같아질때
			if (STR_IDX >= SUBSTR_LINE.size())
			{
				KILL_COMPLETE = true;
				C_STR_LINE = SUBSTR_LINE.substr(SUBSTR_LINE.size(), SUBSTR_LINE.size());
			}
			//string형 문자열 C_STR_LINE을 c_str()을 이용해 char 형식으로 바꿔 OUTPUT_LINE에 저장함.
			sprintf_s(OUTPUT_LINE, "%s", C_STR_LINE.c_str());
		}
		CNT++;
	}
}

//     int nHeight,               // 높이(글자 크기)
//     int nWidth,                // 폭. 0을 넣어주면 높이에 비례함
//     int nEscapement,           // 글자 전체 기울기
//     int nOrientation,          // 기준선이 정해져 있고 기우는 기울기
//     int fnWeight,              // 폰트의 두께
//     DWORD fdwItalic,           // 이탤릭
//     DWORD fdwUnderline,        // 밑줄
//     DWORD fdwStrikeOut,        // 취소선
//     DWORD fdwCharSet,		  // 캐릭터 셋
//     DWORD fdwOutputPrecision,  // 정밀도
//     DWORD fdwClipPrecision,    // 정밀도
//     DWORD fdwQuality,          // 정밀도
//     DWORD fdwPitchAndFamily,   // 정밀도
//     LPCTSTR lpszFace           // 글꼴이름
*/

Lines::Lines() :
	CURRENT_LEN(0),
	CNT(0),
	APPROACH(false),
	I(0),
	IMDEAD(false)
{

}

Lines::~Lines()
{

}

HRESULT Lines::init(POINT _pos, int _fontsize, int _time, string _Lines)
{
	FONT_SIZE = _fontsize;
	SUBSTR_LINE = _Lines;
	CLOCK = (float)_time;

	int e = 0;
	int h = 0;

	//한글자 한글자를 떼어내서 벡터에 담는다.
	for (int i = 0; i < SUBSTR_LINE.size(); )
	{
		oneChar ONE_WORD;

		if (SUBSTR_LINE[i] == '/')
		{
			e = 0;
			h++;
			i++;
			continue;
		}
		ONE_WORD._x = _pos.x + (e * FONT_SIZE);
		ONE_WORD._y = _pos.y + (h * FONT_SIZE);

		string C_STR_LINE;

		if ((SUBSTR_LINE[i] & 0x80) == 0x80)
		{
			C_STR_LINE = SUBSTR_LINE.substr(i, 2);
			i += 2;
		}
		else
		{
			C_STR_LINE = SUBSTR_LINE.substr(i, 1);
			i++;
		}

		sprintf_s(ONE_WORD.oChar, "%s", C_STR_LINE.c_str());

		_vChar.push_back(ONE_WORD);

		e++;
	}
	return S_OK;
}

void Lines::release()
{

}

void Lines::update()
{
	if (!APPROACH) newLine();
	if (APPROACH) CURRENT_CLOCK += (1.0f / 60.0f);
	if (APPROACH && CURRENT_CLOCK >= CLOCK) deleteLine();
}

void Lines::render()
{
	HFONT Font = CreateFont(FONT_SIZE, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "AaCassiopeia");
	HFONT oFont = (HFONT)SelectObject(getMemDC(), Font);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);

	for (int i = I; i < CURRENT_LEN; i++)
	{
		TextOut(getMemDC(), _vChar[i]._x, _vChar[i]._y, _vChar[i].oChar, strlen(_vChar[i].oChar));
	}

	SetTextColor(getMemDC(), RGB(0, 0, 0));

	SelectObject(getMemDC(), oFont);
	DeleteObject(Font);
}

void Lines::newLine()
{
	CNT = CNT % 1;

	if (!CNT)
	{
		if (CURRENT_LEN < _vChar.size())
		{
			CURRENT_LEN++;
		}
		else if (CURRENT_LEN >= _vChar.size())
		{
			CNT = 0;
			APPROACH = true;
		}
	}

	CNT++;
}

void Lines::deleteLine()
{
	CNT = CNT % 1;

	if (!CNT)
	{
		if (CURRENT_LEN >= I) I++;
		if (CURRENT_LEN <= I) IMDEAD = true;
	}

	CNT++;
}