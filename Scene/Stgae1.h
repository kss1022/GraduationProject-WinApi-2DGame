#pragma once

#include "Scene.h"

class Stage1 :public Scene
{
private:
	friend class SceneManager;
	Stage1();
	~Stage1();

public:
	virtual bool Init();
	virtual int Update(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);


private:
	class Number* m_pTimeNumber100;
	class Number* m_pTimeNumber10;
	class Number* m_pTimeNumber1;

	class Number* m_pGoldNumber100;
	class Number* m_pGoldNumber1000;

public:
	virtual void ChangeScene(float fTime);
	virtual void GameOver(float fTime);
};

