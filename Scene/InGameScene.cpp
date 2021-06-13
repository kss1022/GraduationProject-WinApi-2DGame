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


	//pPlayer�� �������� -> (����) �ʱ�ȭ �� ����Ҽ� ���� pLayer���� pPlayer�� �����ϹǷ� Releae�� �������!(Object�� Layer������ ������ �־����)
	pPlayer->Release();
	pPlayer = nullptr;

	pMonster->Release();
	pMonster =nullptr;

	pMinion->Release();
	pMinion = nullptr;


	


	//�Ѿ� ������Ÿ���� ������ش�
	Bullet* pBullet = Scene::CreatePrototype<Bullet>("Bullet", m_eSceneType);

	pBullet->SetSize(50.f, 50.f);

	pBullet->Release();
	pBullet = nullptr;

	return true;
}
