#include "Dracula.h"

#include "../Collider/ColliderReact.h"
#include "../Animation/Animation.h"
#include "../Collider/Collider.h"
#include "../Scene/Scene.h"
#include "DraculaSkill.h"

Dracula::Dracula()
{
	m_iHP = 500;
	m_bMotion = false;
	m_eMotionType = MT_MOVE;

	m_fDemageTime = 0.f;

	m_fSkillTIme = 0.f;
}

Dracula::Dracula(const Dracula & Dracula) : MoveObject(Dracula)
{
	m_iHP = 500;
	m_bMotion = false;
	m_eMotionType = MT_MOVE;

	m_fDemageTime = 0.f;

	m_fSkillTIme = 0.f;
}

Dracula::~Dracula()
{
}

bool Dracula::Init()
{
	SetPos(30.f, 610.f);
	SetSize(200.f, 200.f);
	SetSpeed(150.f);
	SetPivot(0.5f, 0.5f);

	ColliderReact* pReact = AddCollider<ColliderReact>("DraculaBody");
	pReact->AddCollisionFunction(CS_ENTER, this, &Dracula::Hit);
	pReact->SetRect(-30, -43, 30, 43);
	pReact->SetCollierOffset(-45.f, 28.f);
	pReact->Release();
	pReact = nullptr;


	pReact = AddCollider<ColliderReact>("DraculaRange");

	pReact->AddCollisionFunction(CS_ENTER, this, &Dracula::Hit);
	pReact->AddCollisionFunction(CS_STAY, this, &Dracula::Stay);


	pReact->SetRect(-150, -30, 150, 30);
	pReact->SetCollierOffset(150.f, 28.f);
	pReact->Release();
	pReact = nullptr;


	Animation* pAnmation = CreateAnimation("DraculaAnimation");


	AddAnimationClip("DraculaNone", AT_ATLAS, AO_LOPE, 3.f, 9, 1, 0, 0, 9, 1,
		0.f, "DraculaNone", L"Friendly/Dracula/DraculaNone.bmp");
	SetAnimationClipColorKey("DraculaNone", 0, 255, 0);



	AddAnimationClip("DraculaAttack", AT_ATLAS, AO_LOPE, 1.f, 9, 1, 0, 0, 9, 1,
		0.f, "DraculaAttack", L"Friendly/Dracula/DraculaAttack.bmp");
	SetAnimationClipColorKey("DraculaAttack", 0, 255, 0);


	AddAnimationClip("DraculaAttacked", AT_ATLAS, AO_LOPE, 1.f, 5, 1, 0, 0, 5, 1,
		0.f, "DraculaAttacked", L"Friendly/Dracula/DraculaAttacked.bmp");
	SetAnimationClipColorKey("DraculaAttacked", 0, 255, 0);


	AddAnimationClip("DraculaDie", AT_ATLAS, AO_LOPE, 5.f, 9, 1, 0, 0, 9, 1,
		0.f, "DraculaDie", L"Friendly/Dracula/DraculaDie.bmp");
	SetAnimationClipColorKey("DraculaDie", 0, 255, 0);


	m_pAnimation->SetCDefaultClip("DraculaNone");

	pAnmation->Release();
	pAnmation = nullptr;

	return true;
}

void Dracula::Input(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);
}

int Dracula::Update(float fDeltaTime)
{
	MoveObject::Update(fDeltaTime);

	MoveXFromSpeed(fDeltaTime, MD_FRONT);

	if (m_eMotionType != MT_DIE)
	{
		SetSpeed(150.f);
	}

	//모션발동 && 에니메이션의 모션이 끝남->모션이 끝남
	if (m_bMotion && m_pAnimation->GetMotionEnd())
	{
		if (m_pAnimation->GetDefaultStrClip() == "DraculaDie")
		{
			Die();
		}

		m_bMotion = false;
	}

	//움직이지 않는 상태 && 모션이 끝난경우 DefaultClip으로 변경
	if (!m_bMove && !m_bMotion)
	{
		m_pAnimation->ReturenClip();
	}


	return 0;
}

int Dracula::LateUpdate(float fDeltaTime)
{
	MoveObject::LateUpdate(fDeltaTime);


	//Demage인경우 넉백
	if (m_eMotionType == MT_DEMAGE)
	{
		SetSpeed(150.f);

		m_fDemageTime += fDeltaTime;


		if (m_fDemageTime >= 0.5f)
		{
			m_tPos.y = 610.f;
			m_fDemageTime = 0.f;
			m_eMotionType = MT_NONE;
			SetSpeed(0.f);
		}
		MoveXFromSpeed(fDeltaTime * 1.5, MD_BACK);


		if (m_fDemageTime <= 0.25f)
		{
			MoveYFromSpeed(fDeltaTime / 2, MD_BACK);
		}
		else MoveYFromSpeed(fDeltaTime / 2, MD_FRONT);
	}


	if (m_tPos.x >= 1820)
	{
		m_pScene->ChangeScene(fDeltaTime);
	}

	return 0;
}

void Dracula::Collision(float fDeltaTime)
{
	MoveObject::Collision(fDeltaTime);
}

void Dracula::Render(HDC hDC, float fDeltaTime)
{
	MoveObject::Render(hDC, fDeltaTime);
}

Dracula * Dracula::Clone()
{
	return new Dracula(*this);
}

void Dracula::Hit(Collider * pSrc, Collider * pDest, float fDeltaTime)
{
	if ((pDest->GetTag() == "SkeletonBody" || pDest->GetTag() == "SkeletonBulletBody" ||
		pDest->GetTag() == "DeathBody" || pDest->GetTag() == "DeathAttack" ||
		pDest->GetTag() == "DeathWeaponBody" || pDest->GetTag() == "CreatureSkill" ||
		pDest->GetTag() == "CreatureBody" || pDest->GetTag() == "MummyBody") && pSrc->GetTag() == "DraculaBody"
		)
	{
		if (m_eMotionType != MT_DEMAGE && m_eMotionType != MT_DIE)
		{
			((Dracula*)pSrc->GetObject_())->Demage(100);
		}
	}



	if ((pDest->GetTag() == "SkeletonBody" || pDest->GetTag() == "DeathBody" ||
		pDest->GetTag() == "CreatureBody" || pDest->GetTag() == "MummyBody") && pSrc->GetTag() == "DraculaRange"
		)
	{
		((Dracula*)pSrc->GetObject_())->SetSpeed(0.f);
	}
}

void Dracula::Stay(Collider * pSrc, Collider * pDest, float fDeltaTime)
{
	Dracula* pDracula = (Dracula*)pSrc->GetObject_();


	if ((pDest->GetTag() == "SkeletonBody" || pDest->GetTag() == "DeathBody" ||
		pDest->GetTag() == "CreatureBody" || pDest->GetTag() == "MummyBody") && pSrc->GetTag() == "DraculaRange" && pDracula->m_iHP > 0
		)
	{
		m_fSkillTIme += fDeltaTime;


		if (m_fSkillTIme >= 8.f)
		{
			m_fSkillTIme = 0.f;
			Skill(pSrc);
			pDracula->m_pAnimation->ChangeClip("DraculaAttack");
			m_eMotionType = MT_FIGHT;
			pDracula->m_bMotion = true;
		}
		((Dracula*)pSrc->GetObject_())->SetSpeed(0.f);
	}
}




//Demage를 입음
void Dracula::Demage(int iDemage)
{
	m_iHP -= iDemage;

	if (m_iHP <= 0)
	{
		m_eMotionType = MT_DIE;
		m_pAnimation->ChangeClip("DraculaDie");
		m_pAnimation->SetCDefaultClip("DraculaDie");
		m_bMotion = true;
	}
	else
	{
		m_eMotionType = MT_DEMAGE;
		m_pAnimation->ChangeClip("DraculaAttacked");
		m_bMotion = true;
	}
}




//스킬
void Dracula::Skill(Collider * pSrc)
{
	Object* pSkill = Object::CreateCloneObject("DraculaSkill", "DraculaSkill", pSrc->GetObject_()->GetScene()
		->GetSceneType(), pSrc->GetObject_()->GetLayer());

	pSkill->m_pAnimation->SetObject(pSkill);

	float	x = pSrc->GetObject_()->GetCenter().x;
	float	y = pSrc->GetObject_()->GetCenter().y + 50.f;

	pSkill->SetPos(x, y);


	pSkill->Release();
	pSkill = nullptr;
}