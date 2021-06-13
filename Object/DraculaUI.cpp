#include "DraculaUI.h"
#include "../Scene/Scene.h"
#include "../Resource/Texture.h"
#include "../Collider/ColliderReact.h"
#include "../Core/Input.h"

DraculaUI::DraculaUI()
{
	m_iNumber = 0;
	m_fTime = 0.f;

}

DraculaUI::DraculaUI(const DraculaUI & DraculaUI) :UI(DraculaUI)
{
	m_iNumber = 0;

	m_fTime = 0.f;
}

DraculaUI::~DraculaUI()
{
}

bool DraculaUI::Init()
{
	SetSize(100.f, 100.f);
	SetPivot(0.5f, 0.5f);


	SetTexture("DraculaUI", L"Friendly/Dracula/DraculaUI.bmp");
	m_pTexture->SetColorKey(0, 255, 0);
	return true;
}

void DraculaUI::Input(float fDeltaTime)
{
	if (m_iNumber <= 0 && m_pScene->GetGold() >= 100)
	{
		if (KEYPRESS("KeyPad2"))
		{
			m_iNumber = 5;
			m_fTime = 6.f;			
			m_pScene->GoldUp(-100);
		}
	}
	UI::Input(fDeltaTime);
}

int DraculaUI::Update(float fDeltaTime)
{
	UI::Update(fDeltaTime);


	SetImageOffset(m_tSize.x * m_iNumber, 0);


	return 0;
}

int DraculaUI::LateUpdate(float fDeltaTime)
{
	UI::LateUpdate(fDeltaTime);


	if (m_fTime > 0)
	{
		m_fTime -= fDeltaTime;
	}

	m_iNumber = static_cast<int>(m_fTime);

	return 0;
}

void DraculaUI::Collision(float fDeltaTime)
{
	UI::Collision(fDeltaTime);

}

void DraculaUI::Render(HDC hDC, float fDeltaTime)
{
	UI::Render(hDC, fDeltaTime);
}

DraculaUI * DraculaUI::Clone()
{
	return new DraculaUI(*this);
}
