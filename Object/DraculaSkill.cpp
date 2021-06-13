#include "DraculaSkill.h"
#include "../Collider/ColliderReact.h"
#include "../Animation/Animation.h"


DraculaSkill::DraculaSkill()
{
	m_fLifeTime = 0.f;
}

DraculaSkill::DraculaSkill(const DraculaSkill & DraculaSkill) :MoveObject(DraculaSkill)
{
	m_fLifeTime = 0.f;
}

DraculaSkill::~DraculaSkill()
{
}

bool DraculaSkill::Init()
{
	SetSpeed(400.f);
	SetPivot(0.5f, 0.5);
	SetSize(62.f, 38.f);

	ColliderReact* pReact = AddCollider<ColliderReact>("DraculaSkillBody");
	pReact->AddCollisionFunction(CS_ENTER, this, &DraculaSkill::Hit);

	pReact->SetRect(-30, -19, 30, 19);
	pReact->Release();
	pReact = nullptr;



	Animation* pAnmation = CreateAnimation("DraculaSkillAnimation");


	AddAnimationClip("DraculaSkill", AT_ATLAS, AO_LOPE, 2.f, 5, 1, 0, 0, 5, 1,
		0.f, "DraculaSkill", L"Friendly/Dracula/DraculaSkill.bmp");

	SetAnimationClipColorKey("DraculaSkill", 0, 255, 0);

	pAnmation->Release();
	pAnmation = nullptr;

	return true;
}

void DraculaSkill::Input(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);

}

int DraculaSkill::Update(float fDeltaTime)
{
	MoveObject::Update(fDeltaTime);

	m_fLifeTime += fDeltaTime;

	if (m_fLifeTime >= 3.f)
	{
		Die();
	}

	MoveXFromSpeed(fDeltaTime, MD_FRONT);

	return 0;
}

int DraculaSkill::LateUpdate(float fDeltaTime)
{

	MoveObject::LateUpdate(fDeltaTime);

	return 0;
}

void DraculaSkill::Collision(float fDeltaTime)
{
	MoveObject::Collision(fDeltaTime);

}

void DraculaSkill::Render(HDC hDC, float fDeltaTime)
{
	MoveObject::Render(hDC, fDeltaTime);
}

DraculaSkill * DraculaSkill::Clone()
{
	return new DraculaSkill(*this);
}

void DraculaSkill::Hit(Collider * pSrc, Collider * pDest, float fDeltaTime)
{
	if ((pDest->GetTag() == "SkeletonBody" || pDest->GetTag() == "SkeletonBulletBody" ||
		pDest->GetTag() == "DeathBody" || pDest->GetTag() == "DeathAttack" ||
		pDest->GetTag() == "DeathWeaponBody" || pDest->GetTag() == "CreatureSkill" ||
		pDest->GetTag() == "CreatureBody" || pDest->GetTag() == "MummyBody") && pSrc->GetTag() == "DraculaSkillBody"
		)
	{
		pSrc->GetObject_()->Die();
	}
}
