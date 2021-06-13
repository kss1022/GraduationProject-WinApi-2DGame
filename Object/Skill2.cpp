#include "Skill2.h"
#include "../Collider/ColliderReact.h"
#include "../Resource/Texture.h"
#include "../Animation/Animation.h"
#include "../Sound/SoundManager.h"
Skill2::Skill2()
{
}

Skill2::Skill2(const Skill2 & Skill2) : MoveObject(Skill2)
{
}

Skill2::~Skill2()
{
}

bool Skill2::Init()
{
	SetPivot(0.5f, 0.5);
	SetPos(0.f, 0.f);
	SetSize(165.f, 210.f);
	SetSpeed(2000.f);

	SetTexture("Skill2", L"Player/Idle/Skill2.bmp");

	m_pTexture->SetColorKey(255, 255, 255);



	ColliderReact* pRect = AddCollider<ColliderReact>("SkillRange");
	pRect->SetRect(-80.f, -100.f, 80.f, 100.f);

	pRect->Release();
	pRect = nullptr;


	return true;
}

void Skill2::Input(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);
}

int Skill2::Update(float fDeltaTime)
{
	MoveObject::Update(fDeltaTime);


	if (m_tPos.y >590.f)
	{
		SetSpeed(50.f);
		SoundManager::GetInst()->LoadSound("Skill2", false, "IceMagic.wav");
		SoundManager::GetInst()->Play("Skill2");
		SoundManager::GetInst()->Volume(ST_EFFECT, 0.3f);


	}

	if (m_tPos.y > 600.f)
	{
		Die();
	}


	MoveXFromSpeed(fDeltaTime / 2, MD_FRONT);
	MoveYFromSpeed(fDeltaTime, MD_FRONT);

	return 0;
}

int Skill2::LateUpdate(float fDeltaTime)
{
	MoveObject::LateUpdate(fDeltaTime);

	return 0;
}

void Skill2::Collision(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);

}

void Skill2::Render(HDC hDC, float fDeltaTime)
{
	MoveObject::Render(hDC, fDeltaTime);

}

Skill2 * Skill2::Clone()
{
	return new Skill2(*this);
}