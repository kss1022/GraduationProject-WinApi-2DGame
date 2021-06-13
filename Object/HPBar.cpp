#include "HPBar.h"
#include "Player.h"

HPBar::HPBar()
{
	m_pObject = nullptr;
}

HPBar::HPBar(const HPBar & obj) :MoveObject(obj)
{
	m_pObject = nullptr;

}

HPBar::~HPBar()
{
}

bool HPBar::Init()
{
	SetPos(0.f, 0.f);
	SetSize(50.f, 10.f);
	SetTexture("PlayerHPBar", L"Player/HPBar.bmp");


	m_fHPMAX = 1500;
	m_fHP = 1500;
	return true;
}

void HPBar::Input(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);
}

int HPBar::Update(float fDeltaTime)
{
	MoveObject::Update(fDeltaTime);

	
	m_tSize.x = m_fHP / m_fHPMAX * 100.f;

	return 0;
}

int HPBar::LateUpdate(float fDeltaTime)
{
	MoveObject::LateUpdate(fDeltaTime);

	m_tPos = m_pObject->GetPos();

	m_tPos.x -= 50.f;
	m_tPos.y -= 80.f;


	m_fHP = ((Player*)m_pObject )->GetHP();
	if (m_fHP <= 0) Die();


	return 0;
}

void HPBar::Collision(float fDeltaTime)
{
	MoveObject::Collision(fDeltaTime);

}

void HPBar::Render(HDC hDC, float fDeltaTime)
{
	MoveObject::Render(hDC, fDeltaTime);

}

HPBar * HPBar::Clone()
{
	return new HPBar(*this);
}

Object * HPBar::GetObject_() const
{
	return m_pObject;
}

void HPBar::SetObject(Object * obj)
{
	m_pObject = obj;
}

