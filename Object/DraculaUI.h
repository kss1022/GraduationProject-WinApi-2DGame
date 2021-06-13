#pragma once
#include "UI.h"


class DraculaUI : public UI
{
private:
	friend class Object;
	friend class Scene;

protected:
	DraculaUI();
	DraculaUI(const DraculaUI& DraculaUI);
	virtual ~DraculaUI();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	DraculaUI*	 Clone();

private:
	int m_iNumber;
	float m_fTime;
};

