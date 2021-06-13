#pragma once
#include "UI.h"


class Number : public UI
{
private:
	friend class Object;
	friend class Scene;

protected:
	Number();
	Number(const Number& Number);
	virtual ~Number();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Number*	 Clone();

private:
	int m_iNumber;
public:
	void SetNumber(int iNumber);
};

