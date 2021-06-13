#pragma once
#include "Object.h"
class UI :
	public Object
{
protected:
	UI();
	UI(const UI& ui);
	virtual ~UI() =0;


public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual int	 LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	UI*	 Clone() = 0;
};

