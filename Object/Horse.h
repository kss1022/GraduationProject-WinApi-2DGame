#pragma once
#include "MoveObject.h"

class Horse :
	public MoveObject
{
private:
	friend class Object;
	friend class Scene;


protected:
	Horse();
	Horse(const Horse& Horse);
	~Horse();

public:

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Horse*	 Clone();


private:
	int		m_iHP;

	bool	m_bDemage;
	float	m_fDemageTime;

public:
	void Hit(Collider * pSrc, Collider * pDest, float fDeltaTime);


	void Demage(int iDemage);

};





