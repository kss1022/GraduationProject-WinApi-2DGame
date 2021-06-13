#pragma once
#include "MoveObject.h"

class HPBar : public MoveObject
{
private:
	friend class Object;
	friend class Scene;

protected:
	HPBar();
	HPBar(const HPBar& obj);
	virtual ~HPBar();

	Object* m_pObject;
	float m_fHP;
	float m_fHPMAX;

public:
	Object* GetObject_() const;
	void SetObject(class Object* obj);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	HPBar*	 Clone();
};


