#pragma once

#include"../Game.h"
#include"../Ref.h"
#include "../Scene/Layer.h"
#include "../Collider/Collider.h"

class Object : public Ref
{
private:
	friend class Scene;

protected:
	Object();
	Object(const Object& obj);
	virtual ~Object() = 0;


	class Scene*	m_pScene;
	class Layer*	m_pLayer;

public:
	inline void SetScene(class Scene* pScene);
	inline void SetLayer(class Layer* pLayer);

	inline class Scene* GetScene()  const;
	inline class Layer* GetLayer()  const;


private:
	static list<Object*>	m_ObjectList;

public:
	static void AddObject(Object* pObj);
	static Object*	FindObjet(const string& strTag);
	static void		EraseObject(Object* pObj);
	static void		EraseObject(const string& strTag);
	static void		EraseObject();

public:
	template<typename T>
	static T* CreateObj(const string& strTag, class Layer* pLayer = nullptr);

	static Object* CreateCloneObject(const string & strPrototypeKey,
		const string& strTag, SCENE_CREATE sc, class Layer* pLayer = nullptr);

protected:
	POSITION	m_tPos;
	_SIZE		m_tSize;
	_SIZE		m_tImageOffset;
	POSITION	m_tPivot;

public:
	inline void	SetPos(const POSITION& tPos);
	inline void	SetPos(const float x, const float y);
	inline void	SetSize(const _SIZE& tSize);
	inline void	SetSize(const float x, const float y);
	inline void	SetPivot(const float x, const float y);
	inline void SetImageOffset(const _SIZE& tOffset);
	inline void SetImageOffset(const float x, const float y);
	inline POSITION	GetPos() const;
	inline _SIZE	GetSize() const;
	inline POSITION	GetPivot() const;


	inline float GetLeft() const;
	inline float GetRight() const;
	inline float GetTop() const;
	inline float GetBottom() const;
	inline POSITION GetCenter() const;

public:
	class Texture*	m_pTexture;

public:
	void SetTexture(class Texture* pTextrue);
	void SetTexture(const string& strKey,
		const wchar_t* pFileName = nullptr, const string& strPathKey = TEXTURE_PATH);
	void SetColorKey(unsigned char r, unsigned char g, unsigned char b);
protected:
	list<Collider*> m_ColliderList;


public:
	template <typename T>
	T* AddCollider(const string& strTag);

	bool CheckCollider();


	inline const list<Collider*>* GetColliderList() const;

	Collider*	 GetCollider(const string& strTag);

	template<typename T>
	void AddCollisionFunction(const string& strTag, COLLISION_STATE eState, T* pObj,
		void(T::*pFunc)(Collider*, Collider*, float));




protected:
	bool m_bIsPhysics;
	float m_fGravityTime;

public:
	inline void SetPhysics(bool bPhysics);
	inline bool GetPhysics() const;
	inline void ClearGravity();

public:
	class Animation*	m_pAnimation;

public:
	class Animation* CreateAnimation(const string& strTag);
	bool AddAnimationClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption,
		float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY,
		int iStartX, int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime,
		const string& strTextKey, const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);

	bool AddAnimationClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption,
		float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY,
		int iStartX, int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime,
		const string& strTextKey, const vector<wstring>& vecFileName, const string& strPathKey = TEXTURE_PATH);


	void SetAnimationClipColorKey(const string& strClip, unsigned char r, unsigned char g, unsigned char b);


public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual int	 LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Object*	 Clone() = 0;

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

public:
	void SaveFromPath(const char* pFileName, const string& strPathKey = DATA_PATH);	
	void SaveFromFullPath(const char* pFullPah);
	void LoadFromPath(const char* pFileName, const string& strPathKey = DATA_PATH);
	void LoadFromFullPath(const char* pFullPah);
};



template<typename T>
T * Object::CreateObj(const string & strTag, class Layer * pLayer)
{
	T* pObj = new T;

	pObj->SetTag(strTag);

	if (!pObj->Init())
	{
		pObj->Release();
		pObj = nullptr;

		return nullptr;
	}

	//Layer에 추가
	if (pLayer)
	{
		pLayer->AddObject(pObj);
	}

	//ObjectList에 추가
	AddObject(pObj);

	return pObj;
}


template<typename T>
T * Object::AddCollider(const string & strTag)
{
	T* pCollider = new T;

	pCollider->SetObject(this);
	pCollider->SetTag(strTag);

	if (!pCollider->Init())
	{
		pCollider->Release();
		pCollider = nullptr;
		return nullptr;
	}


	pCollider->AddRef();
	m_ColliderList.push_back(pCollider);

	return pCollider;
}

template<typename T>
void Object::AddCollisionFunction(const string& strTag, COLLISION_STATE eState, T * pObj, void(T::* pFunc)(Collider *, Collider *, float))
{
	list< Collider*>::iterator iter;
	list< Collider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; iter++)
	{
		if ((*iter)->GetTag() == strTag)
		{
			(*iter)->AddCollisionFunction(eState, pObj, pFunc);
			break;
		}
	}
}


const list<class Collider*>* Object::GetColliderList() const
{
	return &m_ColliderList;
}












void Object::SetScene(Scene * pScene)
{
	m_pScene = pScene;
}

void Object::SetLayer(class Layer * pLayer)
{
	m_pLayer = pLayer;
}


class Scene* Object::GetScene()  const
{
	return m_pScene;
}

class Layer* Object::GetLayer()  const
{
	return m_pLayer;
}







void Object::SetPos(const POSITION& tPos)
{
	m_tPos = tPos;
}

void Object::SetSize(const _SIZE& tSize)
{
	m_tSize = tSize;
}

void Object::SetPos(const float x, const float y)
{
	m_tPos.x = x;
	m_tPos.y = y;
}

void Object::SetSize(const float x, const float y)
{
	m_tSize.x = x;
	m_tSize.y = y;
}

void Object::SetPivot(const float x, const float y)
{
	m_tPivot.x = x;
	m_tPivot.y = y;
}

inline void Object::SetImageOffset(const _SIZE & tOffset)
{
	m_tImageOffset = tOffset;
}

inline void Object::SetImageOffset(const float x, const float y)
{
	m_tImageOffset.x = x;
	m_tImageOffset.y = y;
}




POSITION Object::GetPos() const
{
	return m_tPos;
}

_SIZE Object::GetSize() const
{
	return m_tSize;
}
POSITION Object::GetPivot() const
{
	return m_tPivot;
}


float Object::GetLeft() const
{
	return m_tPos.x - m_tSize.x * m_tPivot.x;
}


float Object::GetRight() const
{
	return GetLeft() + m_tSize.x;
}

float Object::GetTop() const
{
	return m_tPos.y - m_tSize.y * m_tPivot.y;
}


float Object::GetBottom() const
{
	return GetTop() + m_tSize.y;
}

POSITION Object::GetCenter() const
{
	return POSITION(GetLeft() + m_tSize.x / 2.f, GetTop() + m_tSize.y / 2.f);
}


void Object::SetPhysics(bool bPhysics)
{
	m_bIsPhysics = bPhysics;
}

bool Object::GetPhysics() const
{
	return m_bIsPhysics;
}

inline void Object::ClearGravity()
{
  	m_fGravityTime = 0.f;
}
