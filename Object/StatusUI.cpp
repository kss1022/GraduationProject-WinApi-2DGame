#include "StatusUI.h"

StatusUI::StatusUI()
{
}

StatusUI::StatusUI(const StatusUI & Number)
{
}

StatusUI::~StatusUI()
{

}

bool StatusUI::Init()
{
	SetSize(60.f, 60.f);
	SetPivot(0.5f, 0.5f);
	return true;
}

void StatusUI::Input(float fDeltaTime)
{
	UI::Input(fDeltaTime);

}

int StatusUI::Update(float fDeltaTime)
{
	UI::Update(fDeltaTime);

	return 0;
}

int StatusUI::LateUpdate(float fDeltaTime)
{
	UI::LateUpdate(fDeltaTime);

	return 0;
}

void StatusUI::Collision(float fDeltaTime)
{
	UI::Collision(fDeltaTime);

}

void StatusUI::Render(HDC hDC, float fDeltaTime)
{
	UI::Render(hDC,fDeltaTime);
}

StatusUI * StatusUI::Clone()
{
	return nullptr;
}
