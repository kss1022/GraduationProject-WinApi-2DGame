#include "EndingTexture.h"
#include "../Core.h"

EndingTexture::EndingTexture()
{
	m_iOffset = 0;
	m_fInputTime = 0.f;
}

EndingTexture::EndingTexture(const EndingTexture & EndingTexture) : UI(EndingTexture)
{
	m_iOffset = 0;
	m_fInputTime = 0.f;
}

EndingTexture::~EndingTexture()
{
}

bool EndingTexture::Init()
{
	SetPos(250.f, 10.f);
	SetSize(768.f, 672.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("EndingTexture", L"Stage/EndingText.bmp");
	SetImageOffset(m_tSize.x * m_iOffset, 0);

	return true;
}

void EndingTexture::Input(float fDeltaTime)
{
	UI::Input(fDeltaTime);

	if (m_iOffset < 3 && m_fInputTime > 1.f)
	{
		for (int i = 8; i < 255; i++)
		{
			if (GetAsyncKeyState(i))
			{
				m_iOffset++;
				m_fInputTime = 0.f;
				SetImageOffset(m_tSize.x * m_iOffset, 0);
			}
		}
	}

}

int EndingTexture::Update(float fDeltaTime)
{
	UI::Update(fDeltaTime);

	m_fInputTime += fDeltaTime;


	if (m_iOffset > 2)
	{
		Core::GetInst()->DestroyGame();
	}

	return 0;
}

int EndingTexture::LateUpdate(float fDeltaTime)
{
	UI::LateUpdate(fDeltaTime);

	return 0;
}

void EndingTexture::Collision(float fDeltaTime)
{
	UI::Collision(fDeltaTime);

}

void EndingTexture::Render(HDC hDC, float fDeltaTime)
{
	UI::Render(hDC, fDeltaTime);

}

EndingTexture * EndingTexture::Clone()
{
	return new EndingTexture(*this);
}

