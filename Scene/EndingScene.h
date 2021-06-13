#pragma once
#include "Scene.h"

class EndingScene :
	public Scene
{
private:
	friend class SceneManager;
	EndingScene();
	~EndingScene();
public:

	virtual bool Init();

};

