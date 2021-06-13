#pragma once
#include "MoveObject.h"


class Dracula :
	public MoveObject
{
private:
	friend class Object;
	friend class Scene;


protected:
	Dracula();
	Dracula(const Dracula& Dracula);
	~Dracula();

public:

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Dracula*	 Clone();


private:
	int		m_iHP;

	bool	m_bMotion;
	MOTION_TYPE	m_eMotionType;

	float	m_fDemageTime;

	float	m_fSkillTIme;

public:
	void Hit(Collider * pSrc, Collider * pDest, float fDeltaTime);
	void Stay(Collider * pSrc, Collider * pDest, float fDeltaTime);


	void Demage(int iDemage);
	void Skill(Collider * pSrc);
};
