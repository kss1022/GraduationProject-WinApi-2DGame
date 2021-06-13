#include "CreatureSkill.h"
#include "../Collider/ColliderReact.h"

CreatureSkill::CreatureSkill()
{
	m_iLength = 0;

}

CreatureSkill::CreatureSkill(const CreatureSkill & CreatureSkill) : StaticObject(CreatureSkill)
{
	m_iLength = 0;

}

CreatureSkill::~CreatureSkill()
{
}

bool CreatureSkill::Init()
{
	SetPivot(0.5f, 0.1f);

	SetSize(50.f, 0.f);

	SetTexture("CreatureSkill", L"Enemy/Creature/CreatureSkill.bmp");
	SetColorKey(0, 255, 0);




	return true;
}

void CreatureSkill::Input(float fDeltaTime)
{
	StaticObject::Input(fDeltaTime);

}

int CreatureSkill::Update(float fDeltaTime)
{
	StaticObject::Update(fDeltaTime);




	m_iLength += 15;
	if (m_iLength >= 520)
	{
		Die();
	}

	SetSize(50.f, m_iLength);



	return 0;
}

int CreatureSkill::LateUpdate(float fDeltaTime)
{
	StaticObject::LateUpdate(fDeltaTime);

	return 0;
}

void CreatureSkill::Collision(float fDeltaTime)
{
	StaticObject::Collision(fDeltaTime);
}

void CreatureSkill::Render(HDC hDC, float fDeltaTime)
{
	StaticObject::Render(hDC, fDeltaTime);

}

CreatureSkill * CreatureSkill::Clone()
{
	return new CreatureSkill(*this);
}
