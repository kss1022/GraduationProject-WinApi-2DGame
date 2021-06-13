#include "StartScene.h"

#include "../Scene/Layer.h"
#include "../Collider/ColliderReact.h"
#include "../Core.h"

#include "../Object/UIButton.h"
#include "../Object/UIPanel.h"

#include "SceneManager.h"
#include "MapEditScene.h"
#include "Stgae1.h"
#include "InGameScene.h"

#include "../Sound/SoundManager.h"
StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::Init()
{
	SoundManager::GetInst()->Stop(ST_BGM);
	SoundManager::GetInst()->Play("BGM");
	SoundManager::GetInst()->Volume(ST_BGM, 0.3f);

	if (!Scene::Init())
	{
		return false;
	}

	Layer* pLayer = FindLayer("UI");

	UIPanel* pBackPanel = Object::CreateObj<UIPanel>("BackPanel", pLayer);

	
	pBackPanel->SetSize(Core::GetInst()->GetResoulution().iW, Core::GetInst()->GetResoulution().iH);

	pBackPanel->SetTexture("StartBack", L"Menu.bmp");


	pBackPanel->Release();
	pBackPanel = nullptr;


	//시작버튼
	UIButton* pStartButton = Object::CreateObj<UIButton>("StartButton", pLayer);

	pStartButton->SetSize(200.f, 50.f);
	pStartButton->SetPos(Core::GetInst()->GetResoulution().iW / 2 - 100,
		Core::GetInst()->GetResoulution().iH / 2 - 180);
	
	pStartButton->SetTexture("StartButton", L"UI/StartButton.bmp");
	pStartButton->SetColorKey(255, 255, 255);
	
	ColliderReact* pRC = (ColliderReact*)pStartButton->GetCollider("ButtonBody");
	pRC->SetRect(0.f, 0.f, 200, 50);
	pRC->Release();
	pRC = nullptr;

	pStartButton->SetCallback(this, &StartScene::StatButtonCallBack);

	pStartButton->Release();
	pStartButton = nullptr;


	//맵 에디터버튼
	UIButton* pEditButton = Object::CreateObj<UIButton>("EditButton", pLayer);

	pEditButton->SetSize(200.f, 50.f);
	pEditButton->SetPos(Core::GetInst()->GetResoulution().iW / 2 - 100,
		Core::GetInst()->GetResoulution().iH / 2 -80);

	pEditButton->SetTexture("EditButton", L"UI/EditButton.bmp");
	pEditButton->SetColorKey(255, 255, 255);

	pRC = (ColliderReact*)pEditButton->GetCollider("ButtonBody");
	pRC->SetRect(0.f, 0.f, 200, 50);
	pRC->Release();
	pRC = nullptr;




	pEditButton->SetCallback(this, &StartScene::EditButtonCallBack);

	pEditButton->Release();
	pEditButton = nullptr;


	//종료버튼
	UIButton* pEndButton = Object::CreateObj<UIButton>("EndButton", pLayer);

	pEndButton->SetSize(200.f, 50.f);
	pEndButton->SetPos(Core::GetInst()->GetResoulution().iW / 2 - 100,
		Core::GetInst()->GetResoulution().iH / 2 + 30);

	pEndButton->SetTexture("EndButton", L"UI/EndButton.bmp");
	pEndButton->SetColorKey(255, 255, 255);

	pRC = (ColliderReact*)pEndButton->GetCollider("ButtonBody");
	pRC->SetRect(0.f, 0.f, 200, 50);
	pRC->Release();
	pRC = nullptr;

	pEndButton->SetCallback(this, &StartScene::EndButtonCallBack);

	pEndButton->Release();
	pEndButton = nullptr;


	return true;
}

void StartScene::StatButtonCallBack(float fTime)
{
	SceneManager::GetInst()->CreateScene<Stage1>(SC_NEXT);
	//SceneManager::GetInst()->CreateScene<InGameScene>(SC_NEXT);

}

void StartScene::EditButtonCallBack(float fTime)
{
	SceneManager::GetInst()->CreateScene<MapEditScene>(SC_NEXT);
}


void StartScene::EndButtonCallBack(float fTime)
{
	Core::GetInst()->DestroyGame();
}
