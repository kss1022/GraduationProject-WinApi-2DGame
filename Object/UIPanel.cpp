#include "UIPanel.h"

UIPanel::UIPanel()
{
}

UIPanel::UIPanel(const UIPanel & ui) : UI(ui)
{
}

UIPanel::~UIPanel()
{
}

bool UIPanel::Init()
{
	return true;
}

void UIPanel::Input(float fDeltaTime)
{
	UI::Input(fDeltaTime);
}

int UIPanel::Update(float fDeltaTime)
{
	UI::Update(fDeltaTime);

	return 0;
}

int UIPanel::LateUpdate(float fDeltaTime)
{
	UI::LateUpdate(fDeltaTime);

	return 0;
}

void UIPanel::Collision(float fDeltaTime)
{
	UI::Collision(fDeltaTime);

}

void UIPanel::Render(HDC hDC, float fDeltaTime)
{
	UI::Render(hDC, fDeltaTime);

}

UIPanel * UIPanel::Clone()
{
	return new UIPanel(*this);
}
