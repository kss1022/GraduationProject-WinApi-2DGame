#pragma once
#include "StaticObject.h"
class Friendly :
	public StaticObject
{
private:
	friend class Object;
	friend class Scene;


protected:
	Friendly();
	Friendly(const Friendly& Friendly);
	~Friendly();



public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Friendly*	 Clone();




private:
	Object* m_pObject;

	float m_fDraculaTime;
	float m_fHorseTime;
public:
	Object* GetObject_() const;
	void SetObject(class Object* obj);



	void SummonHorse();
	void SummonDracula();
};

