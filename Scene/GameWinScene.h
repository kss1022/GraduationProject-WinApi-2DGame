#pragma once
#include "Scene.h"
class GameWinScene :
	public Scene
{
private:
	friend class SceneManager;
	GameWinScene();
	~GameWinScene();
public:

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
};

