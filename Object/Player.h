#pragma once
#include "MoveObject.h"

class Player : public MoveObject
{
private:
	friend class Object;
	friend class Scene;

protected:
	Player();
	Player(const Player& player);
	~Player();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Player*	 Clone();


private:
	void Hit(class Collider * pSrc, class  Collider * pDest, float fDeltaTime);
	void HitStay(class Collider * pSrc, class  Collider * pDest, float fDeltaTime);


private:
	int m_iHP;
	int m_iMP;
public:
	int GetHP() const;
	int GetMP() const;

private:
	bool m_bMotion;
	int m_iDir;

	class ColliderReact* m_WeaponBody;

private:
	void Attack();
	
	bool m_bSkill;
	int m_iSkillNumber;
	float m_fSkillTime;

	void SkillMotion();
	void Skill1();
	void Skill_2();

	
	bool m_bFrontDash;
	bool m_bBackDash;
	float m_fDashTime;

	void FrontDash();
	void BackDash();


	bool m_bDemage;
	float m_fDemageTime;


	void Demage(int iDemage);

//	void Fire();
};
