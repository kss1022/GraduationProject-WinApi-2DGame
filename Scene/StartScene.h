#pragma once

#include "Scene.h"

class StartScene :
	public Scene
{
private:
	friend class SceneManager;

private:
	StartScene();
	~StartScene();

	virtual bool Init();

public:
	void StatButtonCallBack(float fTime);
	void EndButtonCallBack(float fTime);
	void EditButtonCallBack(float fTime);
};

