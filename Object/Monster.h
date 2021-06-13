#pragma once

#include "MoveObject.h"

class Monster : public MoveObject
{
private:
	friend class Object;
	friend class Scene;

	MOVE_DIR		m_eDir;
	float			m_fFireTime;
	float			m_fFireLimit;

protected:
	Monster();
	Monster(const Monster& monster);
	~Monster();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Monster* Clone();


	void Fire();

	void FollowPlayer(Collider * pSrc, Collider * pDest, float fDeltaTime);
};

