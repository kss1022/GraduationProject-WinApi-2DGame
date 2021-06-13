#pragma once
#include "UI.h"
class Castle :
	public UI
{
private:
	friend class Object;
	friend class Scene;

protected:
	Castle();
	Castle(const Castle& Castle);
	virtual ~Castle();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Castle*	 Clone();
};

