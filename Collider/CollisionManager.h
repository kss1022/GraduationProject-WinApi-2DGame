#pragma once

#include "../Game.h"

class CollisionManager
{
private:
	CollisionManager();
	~CollisionManager();

	static CollisionManager*	m_pInst;

public:
	static CollisionManager*	GetInst();
	static void				DestroyInst();


private:
	list<class Object*>	m_CollisionList;

public:
	void AddObject(class Object* pObj);
	void Collision(float fDeltaTime);
	bool Collision(class Object* pSrc, class Object* pDest,float fDeltaTime);
	void Clear();
};

