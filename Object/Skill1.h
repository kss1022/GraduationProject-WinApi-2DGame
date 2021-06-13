#pragma once
#include "StaticObject.h"
class Skill1 :
	public StaticObject
{
private:
	friend class Object;
	friend class Scene;

protected:
	Skill1();
	Skill1(const Skill1& skill1);
	~Skill1();


public:

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Skill1*	 Clone();


public:
	float m_fSkillTime;
};

