#pragma once
#include "MoveObject.h"
class Skeleton :
	public MoveObject
{
private:
	friend class Object;
	friend class Scene;


protected:
	Skeleton();
	Skeleton(const Skeleton& Skeleton);
	~Skeleton();

public:

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Skeleton*	 Clone();


private:
	bool		m_bStay;
	bool		m_bAttack;
	float		m_fAttackTime;

	bool		m_bDie;
	float		m_fDieTime;


public:


	void Hit(Collider * pSrc, Collider * pDest, float fDeltaTime);
	void Stay(Collider * pSrc, Collider * pDest, float fDeltaTime);
	void Leave(Collider * pSrc, Collider * pDest, float fDeltaTime);


	void Fire(Collider * pSrc);
	void Fire();

	bool GetDie() const;
};

