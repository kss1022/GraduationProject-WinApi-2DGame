#pragma once
#include "MoveObject.h"
class SkeletonBullet :
	public MoveObject
{

private:
	friend class Object;
	friend class Scene;

protected:
	SkeletonBullet();
	SkeletonBullet(const SkeletonBullet& bullet);
	~SkeletonBullet();


public:

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	SkeletonBullet*	 Clone();

	void Hit(class Collider* pSrc, class Collider* pDest,
		float fDeltaTime);
};

