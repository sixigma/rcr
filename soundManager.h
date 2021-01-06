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

	soundList		_totSounds;

public:
	soundManager();
	~soundManager();

	HRESULT init();
	void release();
	void update();

	//   사운드 추가함수(키 값, 음악파일명, 브금or효과음, 루프할껀지)
	void addSound(string keyName, string soundName, bool bgm, bool loop);

	//                             0.0f ~ 1.0f -> 0 ~ 255
	void play(string keyName, float volume = 1.0f);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	//호옥시이 몰라서 만들어둠
	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);
};

