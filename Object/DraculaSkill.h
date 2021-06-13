#pragma once
#include "MoveObject.h"
class DraculaSkill :
	public MoveObject
{

private:
	friend class Object;
	friend class Scene;

protected:
	DraculaSkill();
	DraculaSkill(const DraculaSkill& DraculaSkill);
	~DraculaSkill();


public:

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	DraculaSkill*	 Clone();

	void Hit(class Collider* pSrc, class Collider* pDest,
		float fDeltaTime);


private:
	float m_fLifeTime;
};

