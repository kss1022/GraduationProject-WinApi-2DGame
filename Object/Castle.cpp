#include "Castle.h"
#include "../Animation/Animation.h"
#include "../Scene/Scene.h"
Castle::Castle()
{
}

Castle::Castle(const Castle & Castle) : UI(Castle)
{
}

Castle::~Castle()
{
}

bool Castle::Init()
{
	SetPos(687.f, 9.f);
	SetSize(565.f, 427.f);
	SetPivot(0.5f, 0.5f);

	
	Animation* pAnmation = CreateAnimation("CastleAnimation");
	//AddAnimationClip("Castle", AT_ATLAS, AO_LOPE, 5.f, 14, 1, 0, 0, 14, 1,
	//	0.f, "Castle", L"Stage/Castle.bmp");

	
	vector<wstring> vecFileName;
	vecFileName.reserve(14);

	for (int i = 1; i <= 14; i++)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Stage/Castle/%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip("Castle", AT_FRAME, AO_LOPE, 5.f, 14, 1, 0, 0, 14, 1,
		0.f, "Castle", vecFileName);
	


	pAnmation->Release();
	pAnmation = nullptr;


	return true;
}

void Castle::Input(float fDeltaTime)
{
	UI::Input(fDeltaTime);
}

int Castle::Update(float fDeltaTime)
{
	UI::Update(fDeltaTime);
	return 0;
}

int Castle::LateUpdate(float fDeltaTime)
{
	UI::LateUpdate(fDeltaTime);
	return 0;
}

void Castle::Collision(float fDeltaTime)
{
	UI::Collision(fDeltaTime);
}

void Castle::Render(HDC hDC, float fDeltaTime)
{
	UI::Render(hDC, fDeltaTime);
}

Castle * Castle::Clone()
{
	return new Castle(*this);
}
