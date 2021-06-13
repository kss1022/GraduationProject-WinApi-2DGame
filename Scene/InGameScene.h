#pragma once

#include "Scene.h"

class InGameScene :public Scene
{
private:
	friend class SceneManager;
	InGameScene();
	~InGameScene();

	virtual bool Init();
};

