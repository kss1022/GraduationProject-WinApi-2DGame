#pragma once
#include "StaticObject.h"
class CreatureSkill :
	public StaticObject
{
private:
	friend class Object;
	friend class Scene;


protected:
	CreatureSkill();
	CreatureSkill(const CreatureSkill& CreatureSkill);
	~CreatureSkill();

public:

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	CreatureSkill*	 Clone();


private:
	int m_iLength;
};