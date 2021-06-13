#pragma once
#include "MoveObject.h"
class DeathWeapon:
	public MoveObject
{
private:
	friend class Object;
	friend class Scene;


protected:
	DeathWeapon();
	DeathWeapon(const DeathWeapon& DeathWeapon);
	~DeathWeapon();

public:

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	DeathWeapon*	 Clone();

private:
	float m_fLifeTime;
	POSITION	m_tPlayerPos;


public:
	void SetPlayerPos(const POSITION  tPos);
};

