#pragma once

#include "../Game.h"

class Camera
{
private:
	Camera();
	~Camera();

	static Camera* m_pInst;
public:
	static Camera*	GetInst();
	static void		DestroyInst();
	bool Init(const POSITION& tPos, const RESOLUTION& tRS, const RESOLUTION& tWorldRS);
	void Input(float fDeltaTime);
	void Update(float fDeltaTIme);
	void Scroll(float x, float y);

private:
	POSITION	m_tPos;
	RESOLUTION	m_tClientRS;
	RESOLUTION	m_tWolrdRS;
	POSITION	m_tPivot;

	class Object* m_pTarget;
public:

	void SetTarget(class Object* pObj);


	inline void SetPos(const POSITION& tPos);
	inline void SetPos(const float x, const float y);
	inline POSITION GetPos() const;

	inline void SetClinetRS(const RESOLUTION& tPos);
	inline void SetClinetRS(const int x, const int y);
	inline RESOLUTION GetClinetRS() const;

	inline void SetWolrdRS(const RESOLUTION& tPos);
	inline void SetWolrdRS(const int x, const int y);
	inline RESOLUTION GetWolrdRS() const;


	inline void SetPivot(const POSITION& tPos);
	inline void SetPivot(const float  x, const float y);
	inline POSITION GetPivot()	const;
};








void Camera::SetPos(const POSITION & tPos)
{
	 m_tPos = tPos;
}

 void Camera::SetPos(const float x, const float y)
 {
	 m_tPos.x = x;
	 m_tPos.y = y;
 }

 POSITION Camera::GetPos() const
{
	return m_tPos;
}




 void Camera::SetClinetRS(const RESOLUTION & tRS)
 {
	 m_tClientRS = tRS;
 }

 void Camera::SetClinetRS(const int x, const int y)
 {
	 m_tClientRS.iW = x;
	 m_tClientRS.iH = y;
 }

 RESOLUTION Camera::GetClinetRS() const
 {
	 return m_tClientRS;
 }




 void Camera::SetWolrdRS(const RESOLUTION & tRS)
 {
	 m_tWolrdRS = tRS;
 }

 void Camera::SetWolrdRS(const int x, const int y)
 {
	 m_tWolrdRS.iW= x;
	 m_tWolrdRS.iH = y;
 }

 RESOLUTION Camera::GetWolrdRS() const
 {
	 return m_tWolrdRS;
 }

 void Camera::SetPivot(const POSITION & tPos)
 {
	 m_tPivot = tPos;
 }


 void Camera::SetPivot(const float  x, const float y)
 {
	 m_tPivot.x = x;
	 m_tPivot.y = y;
 }


 POSITION Camera::GetPivot() const
 {
	 return m_tPivot;
 }

