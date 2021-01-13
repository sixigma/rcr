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
		xpos
		;

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
	void SceneRender();

};

