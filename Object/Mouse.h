#pragma once
#include "UI.h"
class Mouse :
	public UI
{
private:
	friend class Object;
	friend class Scene;

private:
	Mouse();
	Mouse(const Mouse& mouse);
	~Mouse();
	
private:
	POSITION	m_tMove;
	POSITION	m_tWorldPos;

public:
	inline POSITION GetMove() const;
	inline POSITION GetWorldPos() const;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Mouse*	 Clone();
};


POSITION Mouse::GetMove() const
{
	return m_tMove;
}

POSITION Mouse::GetWorldPos() const
{
	return m_tWorldPos;
}
