#pragma once
#include "Collider.h"
class ColliderSphere :
	public Collider
{
private:
	friend class Object;

protected:
	ColliderSphere();
	ColliderSphere(const ColliderSphere& collSphere);

	virtual ~ColliderSphere();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual int	 LateUpdate(float fDeltaTime);
	virtual bool Collision(Collider* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	ColliderSphere*	 Clone();

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
private:
	SPHERE	m_tInfo;
	SPHERE	m_tWorldInfo;


public:
	inline  void SetSphere(const POSITION& tCenter, float fRadius);

	inline SPHERE GetInfo() const;
	inline SPHERE GetWorldInfo() const;
};


void ColliderSphere::SetSphere(const POSITION & tCenter, float fRadius)
{
	m_tInfo.tCenter = tCenter;
	m_tInfo.fRadius = fRadius;
}



SPHERE ColliderSphere::GetInfo() const
{
	return m_tInfo;
}

SPHERE ColliderSphere::GetWorldInfo() const
{
	return m_tWorldInfo;
}
