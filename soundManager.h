#pragma once
#include "singleton.h"
#include <map>
#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex64_vc.lib")

using namespace FMOD;

constexpr size_t SOUNDBUFFER = 10;
constexpr size_t EXTRACHANNELBUFFER = 5;
#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class soundManager : public singleton<soundManager>
{
private:
	typedef map<string, Sound**>			soundList;
	typedef map<string, Sound**>::iterator	soundListIter;

	typedef map<string, Channel**>				channelList;
	typedef map<string, Channel**>::iterator	channelListIter;

private:
	System*			_system;
	Sound**			_sound;
	Channel**		_channel;

	soundList		_soundList;
	soundListIter   _soundListIter;

public:
	soundManager();
	~soundManager();

	HRESULT init();
	void release();
	void update();

	// 음악 파일 추가 함수(키 값, 파일명, 배경음인지 여부, 반복 재생 여부)
	void addSound(string strKey, string soundFileName, bool isBGM, bool isLoop);

	// 추가된 음악 파일을 재생 함수 (음량은 0.0f부터 1.0f까지)
	void play(string strKey, float volume = 1.0f);
	void stop(string strKey);
	void pause(string strKey);
	void resume(string strKey);

	bool isPlaying(string strKey);
	bool isPaused(string strKey);
};

