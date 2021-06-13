#pragma once
#include "MoveObject.h"
class Skill2 :
	public MoveObject
{
private:
	friend class Object;
	friend class Scene;

protected:
	Skill2();
	Skill2(const Skill2& Skill2);
	~Skill2();


public:

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Skill2*	 Clone();
};