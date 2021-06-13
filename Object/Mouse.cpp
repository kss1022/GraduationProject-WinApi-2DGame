#include "Mouse.h"
#include "../Core.h"
#include "../Collider/ColliderPoint.h"
#include "../Core/Camera.h"

Mouse::Mouse()
{
}

Mouse::Mouse(const Mouse & mouse) : UI(mouse)
{
}

Mouse::~Mouse()
{
}



bool Mouse::Init()
{
	POINT	pt;

	//스크린 좌표 기준으로 나온다.
	GetCursorPos(&pt);
	ScreenToClient(Core::GetInst()->GetWindowHandle(), &pt);

	ShowCursor(FALSE);

	POSITION tCamPos = Camera::GetInst()->GetPos();

	m_tPos = pt;
	m_tWorldPos.x = pt.x + tCamPos.x;
	m_tWorldPos.y = pt.y + tCamPos.y;

	ColliderPoint* pColl = AddCollider<ColliderPoint>("Mouse");

	//pColl->SetDistance(10.f,10.f);

	pColl->Release();
	pColl = nullptr;

	return true;
}

void Mouse::Input(float fDeltaTime)
{
	UI::Input(fDeltaTime);
}

int Mouse::Update(float fDeltaTime)
{
	UI::Update(fDeltaTime);

	POINT	pt;

	//스크린 좌표 기준으로 나온다.
	GetCursorPos(&pt);
	ScreenToClient(Core::GetInst()->GetWindowHandle(), &pt);

	m_tMove.x = pt.x - m_tPos.x;
	m_tMove.y = pt.y - m_tPos.y;


	POSITION tCamPos = Camera::GetInst()->GetPos();
	
	m_tPos = pt;
	m_tWorldPos.x = pt.x + tCamPos.x;
	m_tWorldPos.y = pt.y + tCamPos.y;


	return 0;
}

int Mouse::LateUpdate(float fDeltaTime)
{
	UI::LateUpdate(fDeltaTime);
	return 0;
}

void Mouse::Collision(float fDeltaTime)
{
	UI::Collision(fDeltaTime);
}

void Mouse::Render(HDC hDC, float fDeltaTime)
{
	UI::Render(hDC, fDeltaTime);
}

Mouse * Mouse::Clone()
{
	return new Mouse(*this);
}


