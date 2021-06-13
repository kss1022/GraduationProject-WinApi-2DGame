#include "Number.h"
#include "../Scene/Scene.h"
#include "../Resource/Texture.h"
#include "../Collider/ColliderReact.h"

Number::Number()
{
}

Number::Number(const Number & Number) : UI(Number)
{
}

Number::~Number()
{
}

bool Number::Init()
{
	//SetPos(500.f, 30.f);
	SetSize(60.f, 60.f);
	SetPivot(0.5f, 0.5f);


	SetTexture("Number", L"Number/Number.bmp");
	m_pTexture->SetColorKey(255,255,255);

	return true;
}

void Number::Input(float fDeltaTime)
{
	UI::Input(fDeltaTime);
}

int Number::Update(float fDeltaTime)
{
	UI::Update(fDeltaTime);


	SetImageOffset(m_tSize.x * m_iNumber, 0);

	/*

	wchar_t strFileName[MAX_PATH] = {};
	wsprintf(strFileName, L"Number/%d.bmp", m_iNumber);


	string strNumber = "";
	strNumber += m_iNumber;

	SetTexture(strNumber, strFileName);
	m_pTexture->SetColorKey(255, 255, 255);

	*/

	
	return 0;
}

int Number::LateUpdate(float fDeltaTime)
{
	UI::LateUpdate(fDeltaTime);

	return 0;
}

void Number::Collision(float fDeltaTime)
{
	UI::Collision(fDeltaTime);

}

void Number::Render(HDC hDC, float fDeltaTime)
{
	UI::Render(hDC, fDeltaTime);

}

Number * Number::Clone()
{
	return new Number(*this);
}

void Number::SetNumber(int iNumber)
{
	m_iNumber = iNumber;
}
