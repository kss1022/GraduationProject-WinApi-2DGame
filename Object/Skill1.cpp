#include "Skill1.h"
#include "../Collider/ColliderReact.h"
#include "../Resource/Texture.h"
#include "../Animation/Animation.h"

Skill1::Skill1()
{
}

Skill1::Skill1(const Skill1 & skill1) : StaticObject(skill1)
{
}

Skill1::~Skill1()
{
}

bool Skill1::Init()
{
	SetPivot(0.5f, 0.5);
	SetSize(60.f, 140.f);





	
	ColliderReact* pRect = AddCollider<ColliderReact>("SkillRange");
	pRect->SetRect(-30.f, -70.f, 30.f, 70.f);

	pRect->Release();
	pRect = nullptr;
	

	Animation* pAnmation = CreateAnimation("Skill1Animation");



	
	AddAnimationClip("Skill1", AT_ATLAS, AO_LOPE, 2.f, 6, 1, 0, 0, 6, 1,
		0.f, "Skill1", L"Player/Idle/Skill1.bmp");

	SetAnimationClipColorKey("Skill1", 255, 255, 255);
	


	

	pAnmation->Release();
	pAnmation = nullptr;




	return true;
}

void Skill1::Input(float fDeltaTime)
{
	StaticObject::Input(fDeltaTime);
}

int Skill1::Update(float fDeltaTime)
{
	StaticObject::Update(fDeltaTime);

	m_fSkillTime += fDeltaTime;

	if (m_fSkillTime >= 1.f)
	{
		Die();
	}

	return 0;
}

int Skill1::LateUpdate(float fDeltaTime)
{
	StaticObject::LateUpdate(fDeltaTime);

	return 0;
}

void Skill1::Collision(float fDeltaTime)
{
	StaticObject::Input(fDeltaTime);

}

void Skill1::Render(HDC hDC, float fDeltaTime)
{
	StaticObject::Render(hDC, fDeltaTime);

}

Skill1 * Skill1::Clone()
{
	return new Skill1(*this);
}