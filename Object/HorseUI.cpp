#include "HorseUI.h"
#include "../Scene/Scene.h"
#include "../Resource/Texture.h"
#include "../Collider/ColliderReact.h"
#include "../Core/Input.h"

HorseUI::HorseUI()
{
	m_iNumber = 0;
	m_fTime = 0.f;

}

HorseUI::HorseUI(const HorseUI & HorseUI) :UI(HorseUI)
{
	m_iNumber = 0;

	m_fTime = 0.f;
}

HorseUI::~HorseUI()
{
}

bool HorseUI::Init()
{
	SetSize(100.f, 100.f);
	SetPivot(0.5f, 0.5f);


	SetTexture("HorseUI", L"Friendly/Horse/HorseUI.bmp");
	m_pTexture->SetColorKey(255, 0, 255);
	return true;
}

void HorseUI::Input(float fDeltaTime)
{
	if (m_iNumber <= 0  && m_pScene->GetGold() >= 100)
	{
		if (KEYPRESS("KeyPad1"))
		{
			m_iNumber = 5;
			m_fTime = 6.f;
			m_pScene->GoldUp(-100);
		}
	}
	UI::Input(fDeltaTime);
}

int HorseUI::Update(float fDeltaTime)
{
	UI::Update(fDeltaTime);


	SetImageOffset(m_tSize.x * m_iNumber, 0);


	return 0;
}

int HorseUI::LateUpdate(float fDeltaTime)
{
	UI::LateUpdate(fDeltaTime);


	if (m_fTime > 0)
	{
		m_fTime -= fDeltaTime;
	}

	m_iNumber = static_cast<int>(m_fTime);

	return 0;
}

void HorseUI::Collision(float fDeltaTime)
{
	UI::Collision(fDeltaTime);

}

void HorseUI::Render(HDC hDC, float fDeltaTime)
{
	UI::Render(hDC, fDeltaTime);
}

HorseUI * HorseUI::Clone()
{
	return new HorseUI(*this);
}
