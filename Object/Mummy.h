#pragma once
#include "MoveObject.h"
class Mummy :
	public MoveObject
{
private:
	friend class Object;
	friend class Scene;

protected:
	Mummy();
	Mummy(const Mummy& Mummy);
	~Mummy();

public:

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Mummy*	 Clone();

	void Hit(Collider * pSrc, Collider * pDest, float fDeltaTime);
};

