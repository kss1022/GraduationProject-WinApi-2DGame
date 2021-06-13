#pragma once
#include "MoveObject.h"
class Death :
	public MoveObject
{
private:
	friend class Object;
	friend class Scene;


protected:
	Death();
	Death(const Death& Death);
	~Death();

public:

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Death*	 Clone();

private:
	Object* m_pObject;

public:
	Object* GetObject_() const;
	void SetObject(class Object* obj);



private:
	class ColliderReact* m_WeaponBody;


	POSITION m_tDistance;
	MOVE_DIR m_eX;
	MOVE_DIR m_eY;
	bool m_bMotion;

	bool	m_bMoveAttack;
	float	m_fAttackTime;
	float	m_fSkillTime;


	bool	m_bDie;
public:
	int		m_iHP;


	void Warp();
	void DownAttack();
	void MoveAttack();
	void ThrowWeapon();


	void Hit(Collider * pSrc, Collider * pDest, float fDeltaTime);

};

