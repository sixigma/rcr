
#pragma once
#include "gameNode.h"
#include <vector>

//class Lines : public gameNode
//{
	/*private:
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

		bool getDeadTrigger() { return KILL_COMPLETE; }*/

		/*private:

			//각각의 한글자한글자에 대한 좌표와 글자
			struct oneChar
			{
				float _x, _y;
				char oChar[32];
			};

			int
				CNT,				//띄우는속도에대한 인터벌
				FONT_SIZE,			//폰트 사이즈
				CURRENT_LEN,		//현재가리키고있는 배열번호
				I					//이건그냥 지울때 필요한 변수
				;

			bool
				APPROACH,			//접근제한, 글자가 생성이 완료될때 true가 된다.
				IMDEAD
				;

			float
				CLOCK,				//init으로 부터 받아온 초단위시간
				CURRENT_CLOCK		//현재 프레임에 맞춰 1초를 카운트해주는 변수
				;

			string SUBSTR_LINE;		//init으로 부터 받아온 대사 문자열

			POINT LINE_POS;			//init으로 부터 받아온 생성위치

			vector<oneChar> _vChar;	//한글자한글자에가 저장되어있는 벡터

			void newLine();			//글자를 한글자한글자 띄어주기위한 함수
			void deleteLine();		//글자를 한글자한글자 지워주기위한 함수

		public:
			Lines();
			~Lines();

			virtual HRESULT init(POINT _pos, int _fontsize, int _time, string _Lines);
			virtual void release();
			virtual void update();
			virtual void render();

			bool getDead() { return IMDEAD; }

		};
		*/

class Lines : public gameNode
{
private:
	//각각의 한글자한글자에 대한 좌표와 글자
	struct oneChar
	{
		float _x, _y;
		int oChar;
	};

	int
		CNT,				//띄우는속도에대한 인터벌
		FONT_SIZE,			//폰트 사이즈
		CURRENT_LEN,		//현재가리키고있는 배열번호
		I					//이건그냥 지울때 필요한 변수
		;

	bool
		APPROACH,			//접근제한, 글자가 생성이 완료될때 true가 된다.
		IMDEAD,
		BOLD
		;

	float
		CLOCK,				//init으로 부터 받아온 초단위시간
		CURRENT_CLOCK		//현재 프레임에 맞춰 1초를 카운트해주는 변수
		;

	string
		SUBSTR_LINE,		//init으로 부터 받아온 대사 문자열
		NAME
		;

	POINT LINE_POS;			//init으로 부터 받아온 생성위치

	char WORD_CLIST[256];
	int WORD_ILIST[256];

	vector<oneChar> _vChar;	//한글자한글자에가 저장되어있는 벡터

public:
	Lines();
	~Lines();

	virtual HRESULT init(POINT _pos, int _time, string _Lines, bool _bold, string _name);
	virtual void release();
	virtual void update();
	virtual void render();

	void setLineKill() { CURRENT_CLOCK = 99999; }

	void charRender();

	void deleteLine();

	void newLine();

	bool getDead() { return IMDEAD; }
	void setPos(POINT _pos);
	void setPlace(POINT _pos);
	string getName() { return NAME; }
	void chageWord(int _i, char _cW);
	POINT getPos()
	{
		POINT POS = { _vChar[0]._x, _vChar[0]._y };
		return POS;
	}
	char getSelectArrWord(int _i) { return WORD_CLIST[_vChar[_i].oChar]; }
};