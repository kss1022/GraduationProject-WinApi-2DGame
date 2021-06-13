#include "InGameScene.h"
#include "../Object/Player.h"
#include "../Object/Monster.h"
#include "../Object/Bullet.h"
#include "../Object/Minion.h"
#include "../Object/Stage.h"

#include "../Scene/Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderPixel.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

bool InGameScene::Init()
{
	if (!Scene::Init())
	{
		return false;
	}

	Layer* pStageLayer = FindLayer("STAGE");
	Stage* pStage = Object::CreateObj<Stage>("STAGE", pStageLayer);


	//pStage->LoadFromPath("Map1");


	ColliderPixel * pPixel = pStage->AddCollider<ColliderPixel>("StageColl");

	pPixel->SetPixelInfo("Stage1.bmp");

	
	pPixel->Release();
	pPixel = nullptr;

	pStage->Release();
	pStage = nullptr;



	Layer* pLayer = FindLayer("Default");

	Player* pPlayer = Object::CreateObj<Player>("Player", pLayer);

	Camera::GetInst()->SetTarget(pPlayer);
	Camera::GetInst()->SetPivot(0.8f, 0.3f);
	
	Monster* pMonster = Object::CreateObj<Monster>("Monser", pLayer);
	Minion* pMinion = Object::CreateObj<Minion>("Minion", pLayer);


	//pPlayer는 지역변수 -> (스택) 초기화 후 사용할수 없음 pLayer에서 pPlayer를 관리하므로 Releae를 해줘야함!(Object를 Layer에서만 가지고 있어야함)
	pPlayer->Release();
	pPlayer = nullptr;

	pMonster->Release();
	pMonster =nullptr;

	pMinion->Release();
	pMinion = nullptr;


	


	//총알 프로토타입을 만들어준다
	Bullet* pBullet = Scene::CreatePrototype<Bullet>("Bullet", m_eSceneType);

	pBullet->SetSize(50.f, 50.f);

	pBullet->Release();
	pBullet = nullptr;

	return true;
}
