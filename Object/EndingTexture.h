#pragma once
#include "UI.h"
class EndingTexture :
	public UI
{
private:
	friend class Object;
	friend class Scene;

protected:
	EndingTexture();
	EndingTexture(const EndingTexture& EndingTexture);
	virtual ~EndingTexture();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	EndingTexture*	 Clone();


private:
	int		m_iOffset;
	float	m_fInputTime;
};

