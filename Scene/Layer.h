#pragma once

#include "../Game.h"

class Layer
{
private:
	friend class Scene;
	Layer();
	~Layer();

	static Layer* m_pInst;

public:
	static Layer* GetInst();
	static void DestroyInst();

private:
	class Scene* m_pScene;

	string	m_strTag;
	int		m_iZOrder;		//Layer의  출력 우선순위

	list<class Object*> m_ObjectList;
	bool	m_bEnable;
	bool	m_bLife;

public:
	Scene* SetScene(class Scene* pScene);
	inline void SetTag(const string& strTag);
	inline void SetZOrder(const int iZorder);

	Scene* GetScene()const;
	inline string GetTag() const;
	inline int GetZOrder() const;


	inline void SetEnable(bool bEnable);
	inline void Die();

	inline bool GetEnable() const;
	inline bool GetLife() const;


public:

	bool Init();
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);


public:
	void AddObject(class Object* pObj);
};



inline Scene * Layer::SetScene(Scene * pScene)
{
	return m_pScene = pScene;
}

inline void Layer::SetTag(const string& strTag)
{
	m_strTag = strTag;
}

inline void Layer::SetZOrder(const int iZorder)
{
	m_iZOrder = iZorder;
}

inline Scene * Layer::GetScene() const
{
	return m_pScene;
}

inline string Layer::GetTag() const
{
	return m_strTag;
}

inline int Layer::GetZOrder() const
{
	return m_iZOrder;
}



void Layer::SetEnable(bool bEnable)
{
	m_bEnable = bEnable;
}

void Layer::Die()
{
	m_bLife = false;
}

bool Layer::GetEnable() const
{
	return m_bEnable;
}


bool Layer::GetLife() const
{
	return m_bLife;
}