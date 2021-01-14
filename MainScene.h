#pragma once
#include "gameNode.h"

class MainScene : public gameNode
{
private:
	int
		crtScene,
		alpha,
		cnt,
		ypos,
		xpos,
		pulse,
		_x, _y,
		other
		;

	bool
		pulser
		;

	char nameSet[384];
	char myName[5];

public:
	MainScene();
	~MainScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Turn1();
	void Turn2();
	void Turn3();
	void Turn4();
	void setName();
	void SceneRender();

};

