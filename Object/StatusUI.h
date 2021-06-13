#pragma once
#include "UI.h"
class StatusUI :
	public UI
{
private:
	friend class Object;
	friend class Scene;

protected:
	StatusUI();
	StatusUI(const StatusUI& Number);
	virtual ~StatusUI();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	StatusUI*	 Clone();
};


