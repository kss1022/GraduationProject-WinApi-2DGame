#pragma once
#include "Object.h"

class MoveObject : public Object
{
protected:
	MoveObject();
	MoveObject(const MoveObject& obj);
	virtual ~MoveObject() = 0;

private:
	float		m_fAngle;
	float		m_fSpeed;
	bool		m_bFalling;
	float		m_fForce;
	float		m_fForceOrigin;


protected:
	bool		m_bJump;
	float		m_fJumpTime;
public:
	bool		m_bMove;

public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	MoveObject*	 Clone() = 0;


	void Move(float x, float y);
	void Move(float x, float y, float fDeltaTime);
	void Move(const POSITION& tMove);
	void Move(const POSITION& tMove, float fDeltaTime);
	void MoveX(float x);
	void MoveXFromSpeed(float fDeltaTime, MOVE_DIR eDir);
	void MoveX(float x, float fDeletaTime);
	void MoveY(float y);
	void MoveY(float y, float fDeletaTime);
	void MoveYFromSpeed(float fDeltaTime, MOVE_DIR eDir);
	void MoveAngle();
	void MoveAngle(float fDeltaTime);


	void Jump(float fDeltaTime);
	void DoubleJump();

	void JumpEnd();

	inline void SetAngle(const float fAangle);
	inline void SetSpeed(const float fSpeed);
	inline float GetAngle() const;
	inline float GetSpeed() const;

	inline void SetForce(const float fForce);
	inline float GetForce() const;
	inline float GetJumpFime() const;
};

void  MoveObject::SetAngle(const float fAngle)
{
	m_fAngle = fAngle;
}

void  MoveObject::SetSpeed(const float fSpeed)
{
	m_fSpeed = fSpeed;
}

float MoveObject::GetAngle() const
{
	return m_fAngle;
}

float MoveObject::GetSpeed() const
{
	return m_fSpeed;
}

inline void MoveObject::SetForce(const float fForce)
{
	m_fForceOrigin = fForce;
}

inline float MoveObject::GetForce() const
{
	return m_fForce;
}

inline float MoveObject::GetJumpFime() const
{
	return m_fJumpTime;
}
