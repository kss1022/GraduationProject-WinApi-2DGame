#include "Friendly.h"
#include "../Scene/Scene.h"
#include "../Animation/Animation.h"
#include "../Core/Input.h"


#include "../Object/Horse.h"
#include "../Object/Dracula.h"
Friendly::Friendly()
{
	m_fDraculaTime = 0.f;
	m_fHorseTime = 0.f;
}

Friendly::Friendly(const Friendly & Friendly) :StaticObject(Friendly)
{
	m_fDraculaTime = 0.f;
	m_fHorseTime = 0.f;
}

Friendly::~Friendly()
{
}

bool Friendly::Init()
{
	return true;
}

void Friendly::Input(float fDeltaTime)
{
	StaticObject::Input(fDeltaTime);

	if (m_fHorseTime <= 0 && m_pScene->GetGold() >= 100)
	{
		if (KEYDOWN("KeyPad1"))
		{
			SummonHorse();
			m_fHorseTime = 5.f;
		}
	}

	if (m_fDraculaTime <= 0 && m_pScene->GetGold() >= 100)
	{
		if (KEYDOWN("KeyPad2"))
		{
			SummonDracula();
			m_fDraculaTime = 5.f;
		}
	}
}

int Friendly::Update(float fDeltaTime)
{
	StaticObject::Update(fDeltaTime);

	if (m_fHorseTime > 0)
	{
		m_fHorseTime -= fDeltaTime;
	}

	if (m_fDraculaTime > 0)
	{
		m_fDraculaTime -= fDeltaTime;
	}

	return 0;
}

int Friendly::LateUpdate(float fDeltaTime)
{
	StaticObject::LateUpdate(fDeltaTime);

	return 0;
}

void Friendly::Collision(float fDeltaTime)
{
	StaticObject::Collision(fDeltaTime);

}

void Friendly::Render(HDC hDC, float fDeltaTime)
{
	StaticObject::Render(hDC, fDeltaTime);

}

Friendly * Friendly::Clone()
{
	return new Friendly(*this);
}


Object * Friendly::GetObject_() const
{
	return m_pObject;
}

void Friendly::SetObject(Object * obj)
{
	m_pObject = obj;
}

void Friendly::SummonHorse()
{
	Object* pHorse = Object::CreateCloneObject("Horse", "HorseProtoType", m_pScene->GetSceneType(), m_pLayer);

	pHorse->m_pAnimation->SetObject(pHorse);

	pHorse->AddCollisionFunction("HorseBody", CS_ENTER,
		(Horse*)pHorse, &Horse::Hit);



	pHorse->Release();
	pHorse = nullptr;

}


void Friendly::SummonDracula()
{
	Object* pDracula = Object::CreateCloneObject("Dracula", "DraculaProtoType", m_pScene->GetSceneType(), m_pLayer);

	pDracula->m_pAnimation->SetObject(pDracula);





	pDracula->Release();
	pDracula = nullptr;
}
