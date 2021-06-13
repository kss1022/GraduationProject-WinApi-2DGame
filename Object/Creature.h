#pragma once
#include "MoveObject.h"

class Creature:
	public MoveObject
{
private:
	friend class Object;
	friend class Scene;


protected:
	Creature();
	Creature(const Creature& Creature);
	~Creature();

public:

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Creature*	 Clone();


private:
	float	m_fAtackTime;
	bool	m_bSkill;
	float	m_fSkillTime;


	class ColliderReact* m_WeaponBody;


public:
	void Hit(Collider * pSrc, Collider * pDest, float fDeltaTime);
	void Attack();
};

