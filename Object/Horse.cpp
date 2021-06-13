#include "Horse.h"

#include "../Collider/ColliderReact.h"
#include "../Animation/Animation.h"
#include "../Scene/Stgae1.h"

Horse::Horse()
{
	m_iHP = 500;
	m_bDemage = false;
	m_fDemageTime = 0.f;
}

Horse::Horse(const Horse & Horse) : MoveObject(Horse)
{
	m_iHP = 500;
	m_bDemage = false;
	m_fDemageTime = 0.f;
}

Horse::~Horse()
{
}

bool Horse::Init()
{
	SetPos(30.f, 640.f);
	SetSize(125.f, 90.f);
	SetSpeed(400.f);
	SetPivot(0.5f, 0.5f);


	ColliderReact* pReact = AddCollider<ColliderReact>("HorseBody");
	pReact->SetRect(-60, -45, 60, 45);
	//	pReact->SetCollierOffset(20.f, 0.f);
	//	pReact->AddCollisionFunction(CS_ENTER, this, &Horse::Hit);
	pReact->Release();
	pReact = nullptr;

	Animation* pAnmation = CreateAnimation("HorseAnimation");

	AddAnimationClip("HorseMove", AT_ATLAS, AO_LOPE, 0.5f, 5, 1, 0, 0, 5, 1,
		0.f, "HorseMove", L"Friendly/Horse/Horse.bmp");
	SetAnimationClipColorKey("HorseMove", 255, 0, 255);



	AddAnimationClip("HorseAttacked", AT_ATLAS, AO_LOPE, 0.5f, 1, 1, 0, 0, 1, 1,
		0.f, "HorseAttacked", L"Friendly/Horse/HorseDie.bmp");
	SetAnimationClipColorKey("HorseAttacked", 255, 0, 255);



	pAnmation->Release();
	pAnmation = nullptr;

	return true;
}

void Horse::Input(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);
}

int Horse::Update(float fDeltaTime)
{
	MoveObject::Update(fDeltaTime);

	MoveXFromSpeed(fDeltaTime, MD_FRONT);

	return 0;
}

int Horse::LateUpdate(float fDeltaTime)
{
	MoveObject::LateUpdate(fDeltaTime);


	if (m_bDemage)
	{
		m_fDemageTime += fDeltaTime;


		if (m_fDemageTime >= 0.5f)
		{
			if (m_iHP <= 0)
			{
				Die();
			}


			m_tPos.y = 640.f;
			m_bDemage = false;
			m_fDemageTime = 0.f;
			m_pAnimation->ChangeClip("HorseMove");
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

void Horse::Collision(float fDeltaTime)
{
	MoveObject::Collision(fDeltaTime);

}

void Horse::Render(HDC hDC, float fDeltaTime)
{
	MoveObject::Render(hDC, fDeltaTime);
}

Horse * Horse::Clone()
{
	return new Horse(*this);
}

void Horse::Hit(Collider * pSrc, Collider * pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "SkeletonBody" || pDest->GetTag() == "SkeletonBulletBody" ||
		pDest->GetTag() == "DeathBody" || pDest->GetTag() == "DeathAttack" ||
		pDest->GetTag() == "DeathWeaponBody" || pDest->GetTag() == "CreatureSkill" ||
		pDest->GetTag() == "CreatureBody" || pDest->GetTag() == "MummyBody"
		)
	{

		Demage(100);

	}
}

void Horse::Demage(int iDemage)
{
	m_iHP -= iDemage;


	m_pAnimation->ChangeClip("HorseAttacked");

	m_bDemage = true;
}



