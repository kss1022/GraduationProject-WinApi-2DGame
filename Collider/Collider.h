#pragma once

#include "../Ref.h"
#include "../Game.h"

class Collider : public Ref
{
private:
	friend class Object;

protected:
	Collider();
	Collider(const Collider& coll);
	virtual ~Collider() = 0;

protected:
	COLLIDER_TYPE	m_eCollType;
	class Object*	m_pObject;
	list<Collider*>	m_ColliderLIst;
	list<function < void(Collider*, Collider*, float)> >  m_FuncList[CS_END];
	POSITION	m_tHitPoint;


public:
	inline COLLIDER_TYPE	GetColliderType() const;

	void AddCollider(Collider* pCollider);
	bool CheckCollisionList(Collider* pCollider);
	void EraseCollisionList(Collider* pCollider);

	void AddCollisionFunction(COLLISION_STATE eState,
		void(*pFunc)(Collider*, Collider*, float));

	inline POSITION	GetHitPoint() const;
	inline	void SetHitPoint(const POSITION& tPos);

	template<typename T>
	void AddCollisionFunction(COLLISION_STATE eState, T* pObj,
		void(T::*pFunc)(Collider*, Collider*, float));

	void Callfunction(COLLISION_STATE eState, Collider* pDest, float fDeltaTime);
	
protected:
	bool CollisionReactToReact(const RECTANGLE& src, const RECTANGLE& dest);
	bool CollisionSphereToSphere(const SPHERE& src, const SPHERE& dest);
	bool CollisionReactToSphere(const RECTANGLE& src, const SPHERE& dest);
	bool CollisionReactToPixel(const RECTANGLE&src, const vector<PIXEL>& vecPixel , int iWidth, int iHeight);
	bool CollisionSphereToPixel(const SPHERE&src, const vector<PIXEL>& vecPixel , int iWidth, int iHeight);
	bool CollisionReactToPoint(const RECTANGLE&src, const POSITION& dest);
	bool CollisionSphereToPoint(const SPHERE& src, const POSITION& dest);
	bool CollisionPixelToPoint(const vector<PIXEL>& vecPixel, int iWidth, int iHeight, const POSITION& dest);

public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual int	 LateUpdate(float fDeltaTime);
	virtual bool Collision(Collider* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Collider*	 Clone() = 0;
	
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);


	inline class Object* GetObject_() const;
	inline void SetObject(class Object* obj);
};









COLLIDER_TYPE Collider::GetColliderType() const
{
	return m_eCollType;
}



Object * Collider::GetObject_() const
{
	return m_pObject;
}

void Collider::SetObject(Object * obj)
{
	m_pObject = obj;
}

POSITION Collider::GetHitPoint() const
{
	return m_tHitPoint;
}

inline void Collider::SetHitPoint(const POSITION& tPos)
{
	m_tHitPoint = tPos;
}


template<typename T>
 void Collider::AddCollisionFunction(COLLISION_STATE eState, T * pObj,
	 void(T::* pFunc)(Collider *, Collider *, float))
{
	function<void(Collider*, Collider*, float)> func;

	func = bind(pFunc, pObj,placeholders::_1, placeholders::_2, placeholders::_3);

	m_FuncList[eState].push_back(func);
}
