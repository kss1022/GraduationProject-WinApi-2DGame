#pragma once
#include "UI.h"


class HorseUI : public UI
{
private:
	friend class Object;
	friend class Scene;

protected:
	HorseUI();
	HorseUI(const HorseUI& HorseUI);
	virtual ~HorseUI();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	HorseUI*	 Clone();

private:
	int m_iNumber;
	float m_fTime;
};

