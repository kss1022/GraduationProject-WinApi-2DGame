#pragma once
#include "MoveObject.h"


class Minion : public MoveObject
{
private:
	friend class Object;
	friend class Scene;

protected:
	Minion();
	Minion(const Minion& minion);
	~Minion();

private:
	MOVE_DIR	m_eDir;
	float		m_fFireTime;
	float		m_fFireLimit;


public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Minion*	 Clone();

	void CollisionBullet(class Collider* pSrc, class Collider* pDest,
		float fDeltaTime);

	void Fire();
};

