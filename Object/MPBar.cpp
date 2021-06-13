#include "MPBar.h"
#include "Player.h"

MPBar::MPBar()
{
	m_pObject = nullptr;
}

MPBar::MPBar(const MPBar & obj) : MoveObject(obj)
{
	m_pObject = nullptr;
}

MPBar::~MPBar()
{
}



bool MPBar::Init()
{
	SetPos(0.f, 0.f);
	SetSize(50.f, 10.f);


	m_fMP = 1500;
	m_fMPMAX = 1500;
	SetTexture("PlayerMPBar", L"Player/MPBar.bmp");

	return true;
}

void MPBar::Input(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);

}

int MPBar::Update(float fDeltaTime)
{
	MoveObject::Update(fDeltaTime);

	m_tSize.x = m_fMP / m_fMPMAX * 100.f;


	return 0;
}

int MPBar::LateUpdate(float fDeltaTime)
{
	MoveObject::LateUpdate(fDeltaTime);

	m_tPos = m_pObject->GetPos();

	m_tPos.x -= 50.f;
	m_tPos.y -= 70.f;



	m_fMP = ((Player*)m_pObject)->GetMP();

	if (((Player*)m_pObject)->GetHP() == 0)
	{
		Die();
	}

	return 0;
}

void MPBar::Collision(float fDeltaTime)
{
	MoveObject::Collision(fDeltaTime);

}

void MPBar::Render(HDC hDC, float fDeltaTime)
{
	MoveObject::Render(hDC,fDeltaTime);

}

MPBar * MPBar::Clone()
{
	return new MPBar(*this);
}


Object * MPBar::GetObject_() const
{
	return m_pObject;;
}

void MPBar::SetObject(Object * obj)
{
	m_pObject = obj;
}