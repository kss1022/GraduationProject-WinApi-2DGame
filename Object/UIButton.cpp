#include "UIButton.h"
#include "../Collider/ColliderReact.h"
#include "../Animation/Animation.h"
#include "../Core/Input.h"

UIButton::UIButton() :
	m_bEnableCallback(false),
	m_eState(BS_NONE)
{
}

UIButton::UIButton(const UIButton & ui) : UI(ui)
{
	m_bEnableCallback = false;
	m_eState = BS_NONE;
}

UIButton::~UIButton()
{
}



bool UIButton::Init()
{
	ColliderReact* pColl = AddCollider<ColliderReact>("ButtonBody");

	if (pColl)
	{
		pColl->AddCollisionFunction(CS_ENTER, this, &UIButton::MouseOn);
		pColl->AddCollisionFunction(CS_LEAVE, this, &UIButton::MouseOut);
	}

	pColl->Release();
	pColl = nullptr;

	return true;
}



void UIButton::Input(float fDeltaTime)
{
	UI::Input(fDeltaTime);
}

int UIButton::Update(float fDeltaTime)
{
	UI::Update(fDeltaTime);

	return 0;
}

int UIButton::LateUpdate(float fDeltaTime)
{
	UI::LateUpdate(fDeltaTime);

	if (m_eState != BS_NONE)
	{
		if (KEYPRESS("MouseLButton"))
		{
			m_eState = BS_CLICK;
			SetImageOffset(m_tSize.x * 2, 0.f);
		}
	}

	if (m_eState == BS_CLICK && KEYUP("MouseLButton"))
	{
		m_eState = BS_MOUSEON;
		SetImageOffset(m_tSize.x, 0.f);

		if (m_bEnableCallback)
		{
			m_BtnCallBack(fDeltaTime);
		}
	}

	return 0;
}

void UIButton::Collision(float fDeltaTime)
{
	UI::Collision(fDeltaTime);

}

void UIButton::Render(HDC hDC, float fDeltaTime)
{
	UI::Render(hDC, fDeltaTime);

}

UIButton * UIButton::Clone()
{
	return new UIButton(*this);
}


void UIButton::MouseOn(Collider * pSrc, Collider * pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "Mouse")
	{
		m_eState = BS_MOUSEON;
		SetImageOffset(m_tSize.x, 0.f);
	}
}

void UIButton::MouseOut(Collider * pSrc, Collider * pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "Mouse")
	{
		m_eState = BS_NONE;
		SetImageOffset(0.f, 0.f);
	}
}


void UIButton::SetCallback(void(pFunc)(float))
{
	m_BtnCallBack = bind(pFunc, placeholders::_1);
	m_bEnableCallback = true;
}
