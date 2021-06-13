#pragma once
#include "StaticObject.h"


class Enemy :
	public StaticObject
{
private:
	friend class Object;
	friend class Scene;


protected:
	Enemy();
	Enemy(const Enemy& Enemy);
	~Enemy();



public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Enemy*	 Clone();


private:
	Object* m_pObject;

public:
	Object* GetObject_() const;
	void SetObject(class Object* obj);



private:
	float m_fMummyTime;
	float m_fSkeletonTime;
	float m_fCreatureTime;
	float m_fDeathTime;
	

public:
	void SummonSkeleton();
	void SummonDeath();
	void SummonCreature();
	void SummonMummy();

};

