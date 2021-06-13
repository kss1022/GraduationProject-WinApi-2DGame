#pragma once
#include "MoveObject.h"
class Bullet : public MoveObject
{
private:
	friend class Object;
	friend class Scene;


protected:
	Bullet();
	Bullet(const Bullet& bullet);
	~Bullet();

private:
	float	m_fDist;
	float	m_fLimitDist;

public:
	inline void SetBulletDistance(float fDist);

public:

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	MoveObject*	 Clone();

	void Hit(class Collider* pSrc, class Collider* pDest,
		float fDeltaTime);
};

void Bullet::SetBulletDistance(float fDist)
{
	m_fLimitDist = fDist;
}

