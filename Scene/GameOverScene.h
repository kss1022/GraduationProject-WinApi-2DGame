#pragma once
#include "Scene.h"
class GameOverScene :
	public Scene
{
private:
	friend class SceneManager;
	GameOverScene();
	~GameOverScene();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
};

