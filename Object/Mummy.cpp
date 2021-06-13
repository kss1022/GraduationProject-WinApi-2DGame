#include "Mummy.h"
#include  "../Animation/Animation.h"
#include "../Collider/ColliderReact.h"
#include "../Scene/Scene.h"
#include "../Sound/SoundManager.h"

Mummy::Mummy()
{
}

Mummy::Mummy(const Mummy & Mummy) : MoveObject(Mummy)
{
}

Mummy::~Mummy()
{
}

bool Mummy::Init()
{
	SetPos(1700.f, 600.f);
	SetSize(200, 200.0f);
	SetSpeed(150.f);
	SetPivot(0.5f, 0.5f);
	//SetImageOffset(8.f, 8.f);



	ColliderReact* pReact = AddCollider<ColliderReact>("MummyBody");


	pReact->SetRect(-30, -65, 30, 65);
	pReact->AddCollisionFunction(CS_ENTER, this, &Mummy::Hit);
	pReact->SetCollierOffset(0.f, 10.f);

	pReact->Release();
	pReact = nullptr;



	Animation* pAnmation = CreateAnimation("MummyAnimation");


	AddAnimationClip("MummyNone", AT_ATLAS, AO_LOPE, 1.f, 5, 1, 0, 0, 5, 1,
		0.f, "MummyNone", L"Enemy/Mummy/Mummy.bmp");
	SetAnimationClipColorKey("MummyNone", 84, 109, 142);

	AddAnimationClip("MummyDie", AT_ATLAS, AO_LOPE, 0.6f, 5, 1, 0, 0, 5, 1,
		0.f, "MummyDie", L"Enemy/Mummy/MummyDie.bmp");
	SetAnimationClipColorKey("MummyDie", 84, 109, 142);

	pAnmation->Release();
	pAnmation = nullptr;



	return true;
}

void Mummy::Input(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);
}

int Mummy::Update(float fDeltaTime)
{
	MoveObject::Update(fDeltaTime);

	MoveXFromSpeed(fDeltaTime, MD_BACK);

	if (m_pAnimation->GetCurrentStrClip() == "MummyDie")
	{
		if (m_pAnimation->GetMotionEnd())
		{
			m_pScene->GoldUp(100);
			Die();
		}

	}


	return 0;
}

int Mummy::LateUpdate(float fDeltaTime)
{
	MoveObject::LateUpdate(fDeltaTime);



	if (m_tPos.x <= 45.f)
	{
		m_pScene->GameOver(fDeltaTime);
	}


	return 0;
}

void Mummy::Collision(float fDeltaTime)
{
	MoveObject::Collision(fDeltaTime);

}

void Mummy::Render(HDC hDC, float fDeltaTime)
{
	MoveObject::Render(hDC, fDeltaTime);

}

Mummy * Mummy::Clone()
{
	return new Mummy(*this);
}

void Mummy::Hit(Collider * pSrc, Collider * pDest, float fDeltaTime)
{
	Mummy* pMummy = (Mummy*)pSrc->GetObject_();

	if ((pDest->GetTag() == "WeaponBody" || pDest->GetTag() == "Skill1Range" || pDest->GetTag() == "SkillRange" ||
		pDest->GetTag() == "DraculaSkillBody" || pDest->GetTag() == "HorseBody")
		)
	{
		pMummy->m_pAnimation->ChangeClip("MummyDie");
		pMummy->SetSpeed(0.f);

		SoundManager::GetInst()->LoadSound("Enemy hit", false, "Enemy hit.wav");
		SoundManager::GetInst()->Play("Enemy hit");
	}
}
