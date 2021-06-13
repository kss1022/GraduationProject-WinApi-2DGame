#include "Input.h"
#include "../Object/Mouse.h"
#include "../Animation/Animation.h"
#include "../Collider/CollisionManager.h"

Input* Input::m_pInst = nullptr;

Input::Input() : m_pCreateKey(nullptr), m_pMouse(nullptr)
{
}

Input::~Input()
{

	unordered_map<string, KEYINFO*>::iterator iter;
	unordered_map<string, KEYINFO*>::iterator iterEnd = m_mapKey.end();

	for (iter = m_mapKey.begin(); iter != iterEnd; iter++)
	{
		delete iter->second;
		iter->second = nullptr;
	}

	Object::EraseObject(m_pMouse);
	m_pMouse->Release();
	m_pMouse = nullptr;
}

Input * Input::GetInst()
{
	if (!m_pInst)
	{
		m_pInst = new Input;
	}


	return m_pInst;
}

void Input::DestroyInst()
{
	delete m_pInst;
	m_pInst = nullptr;
}

Mouse * Input::GetMouse() const
{
	return m_pMouse;
}

POSITION Input::GetMouseClinetPos() const
{
	return m_pMouse->GetPos();
}

POSITION Input::GetMouseWorldPos() const
{
	return m_pMouse->GetWorldPos();
}

POSITION Input::GetMouseMove() const
{
	return m_pMouse->GetMove();
}



bool Input::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	AddKey('W', "MoveFront");
	AddKey('S', "MoveBack");
	AddKey("MoveLeft", 'A');
	AddKey("MoveRight", 'D');
	AddKey("Attack", 'K');
	AddKey("Jump", VK_SPACE);
	//AddKey(VK_CONTROL, "Skill1", '1');
	AddKey(VK_CONTROL, "Skill1");
	AddKey(VK_SHIFT, "Skill2");
	AddKey(VK_LBUTTON, "MouseLButton");
	AddKey(VK_RBUTTON, "MouseRButton");
	


	AddKey('1', "KeyPad1");
	AddKey('2', "KeyPad2");
	AddKey('3', "KeyPad3");
	AddKey('4', "KeyPad4");
	AddKey('5', "KeyPad5");
	AddKey('Q', "KeyPadQ");
	AddKey('E', "KeyPadE");
	


	//마우스 위치를 얻어옴
	GetCursorPos(&m_tMousePos);
	
	m_pMouse = Object::CreateObj<Mouse>("Mouse");

	m_pMouse->SetSize(20.f, 20.f);


	
	Animation* pAnimation = m_pMouse->CreateAnimation("MouseAnimation");

	
	m_pMouse->AddAnimationClip("MousePointer", AT_ATLAS, AO_LOPE, 0.5f, 2, 1, 0, 0, 2, 1,
		0.f, "MousePointer", L"/UI/pointer.bmp");
	
	m_pMouse->SetAnimationClipColorKey("MousePointer", 255, 255, 255);

	
	pAnimation->Release();
	pAnimation = nullptr;
	return true;
}

void Input::Update(float fDeltaTime)
{
	unordered_map<string, KEYINFO*>::iterator iter;
	unordered_map<string, KEYINFO*>::iterator iterEnd = m_mapKey.end();

	for (iter = m_mapKey.begin(); iter != iterEnd; iter++)
	{
		int iPushCount = 0;
		
		for (size_t i= 0; i < iter->second->vecKey.size(); i++)
		{
			if (GetAsyncKeyState(iter->second->vecKey[i]) & 0x8000)
			{
				iPushCount++;
			}
		}

		if (iPushCount == iter->second->vecKey.size())
		{
			if (!iter->second->bDown && !iter->second->bPress)
			{
				iter->second->bDown = true;
			}
			else if (iter->second->bDown && !iter->second->bPress)
			{
				iter->second->bPress = true;
				iter->second->bDown = false;
			}
		}

		else
		{
			if (iter->second->bDown || iter->second->bPress)
			{
				iter->second->bUp = true;
				iter->second->bDown = false;
				iter->second->bPress = false;
			}

			else if (iter->second->bUp)
			{
				iter->second->bUp = false;
			}
		}
	}

	m_pMouse->Update(fDeltaTime);
	m_pMouse->LateUpdate(fDeltaTime);
	CollisionManager::GetInst()->AddObject(m_pMouse);
}

bool Input::KeyDown(const string & strKey) const
{
	KEYINFO* pInfo = FindKey(strKey);

	if (!pInfo)
	{
		return false;
	}

	return pInfo->bDown;
}

bool Input::KeyPress(const string & strKey) const
{
	KEYINFO* pInfo = FindKey(strKey);

	if (!pInfo)
	{
		return false;
	}

	return pInfo->bPress;
}

bool Input::KeyUp(const string & strKey) const
{
	KEYINFO* pInfo = FindKey(strKey);

	if (!pInfo)
	{
		return false;
	}

	return pInfo->bUp;
}

KEYINFO * Input::FindKey(const string & strKey) const
{
	unordered_map<string, KEYINFO*>::const_iterator iter = m_mapKey.find(strKey);

	if (iter == m_mapKey.end())
	{
		return nullptr;
	}

		
	return iter->second;
}
