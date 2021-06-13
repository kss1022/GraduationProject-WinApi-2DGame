#include "EndingScene.h"
#include "../Core.h"
#include "../Object/UIPanel.h"
#include "../Object/EndingTexture.h"
EndingScene::EndingScene()
{
}

EndingScene::~EndingScene()
{
}

bool EndingScene::Init()
{
	if (!Scene::Init())
	{
		return false;
	}

	Layer* pLayer = FindLayer("UI");

	UIPanel* pBackPanel = Object::CreateObj<UIPanel>("BackPanel", pLayer);


	pBackPanel->SetSize(Core::GetInst()->GetResoulution().iW, Core::GetInst()->GetResoulution().iH);

	pBackPanel->SetTexture("Ending", L"Stage/Ending.bmp");


	pBackPanel->Release();
	pBackPanel = nullptr;




	EndingTexture* pEndingTexture = Object::CreateObj<EndingTexture>("EndingTexture", pLayer);
	pEndingTexture->Release();
	pEndingTexture = nullptr;

	return true;
}