#pragma once

#include "../Game.h"

typedef struct _tagKeyInfo
{
	string strName;
	bool	bDown;
	bool	bPress;
	bool	bUp;
	vector<DWORD>	vecKey;


	_tagKeyInfo() : bDown(false), bPress(false), bUp(false)
	{
	}
}KEYINFO;





class Input
{
private:
	Input();
	~Input();
	
	static Input*  m_pInst;

public:
	static Input* GetInst();
	static void DestroyInst();


private:
	HWND			m_hWnd;
	unordered_map<string, KEYINFO*> m_mapKey;
	KEYINFO*		m_pCreateKey;

	POINT			m_tMousePos;
	POINT			m_tMouseMove;
	
	class Mouse*	m_pMouse;

public:
	class Mouse*	GetMouse() const;

	POSITION GetMouseClinetPos() const;
	POSITION GetMouseWorldPos() const;
	POSITION GetMouseMove() const;


public:
	bool Init(HWND hWnd);
	void Update(float fDeltaTime);
	bool KeyDown(const string& strKey) const;
	bool KeyPress(const string& strKey) const;
	bool KeyUp(const string& strKey) const;

public:
	template <typename T>
	bool AddKey(const T& data);


	template <typename T, typename... Types>
	bool AddKey(const T& data, const Types&... arg);


private:
	KEYINFO* FindKey(const string& strKey) const;
};
 


template<typename T>
bool Input::AddKey(const T & data)
{
	if (!m_pCreateKey)
	{
		m_pCreateKey = new KEYINFO;
	}
	const char* pTType = typeid(T).name();

	if (strcmp(pTType, "char") == 0 || strcmp(pTType, "int") == 0)
	{
		m_pCreateKey->vecKey.push_back((DWORD)data);
	}
	else
	{
		m_pCreateKey->strName = data;
		m_mapKey.insert(make_pair(m_pCreateKey->strName, m_pCreateKey));
	}

	return true;
}

template <typename T, typename... Types>
bool Input::AddKey(const T& data, const Types&... arg)
{
	if (!m_pCreateKey)
	{
		m_pCreateKey = new KEYINFO;
	}
	const char* pTType = typeid(T).name();

	if (strcmp(pTType, "char") == 0 || strcmp(pTType, "int") == 0)
	{
		m_pCreateKey->vecKey.push_back((DWORD)data);
	}
	else
	{
		m_pCreateKey->strName = data;
		m_mapKey.insert(make_pair(m_pCreateKey->strName, m_pCreateKey));
	}

	AddKey(arg...);

	if (m_pCreateKey)
	{
		m_pCreateKey = nullptr;
	}

	return true;
}

