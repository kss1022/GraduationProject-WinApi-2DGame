#include "MoveObject.h"

MoveObject::MoveObject() :
	m_fAngle(0.0f),
	m_fSpeed(100.0f),
	m_bMove(false),
	m_bFalling(true),
	m_fForce(0.f),
	m_fForceOrigin(0.f),
	m_bJump(false),
	m_fJumpTime(0.f)
{
}

MoveObject::MoveObject(const MoveObject & obj) :Object(obj)
{
	m_fAngle = obj.m_fAngle;
	m_fSpeed = obj.m_fSpeed;

	m_bMove = false;
	m_bFalling = true;

	m_fForce = obj.m_fForce;
	m_fForceOrigin = obj.m_fForceOrigin;
	m_bJump = false;
	m_fJumpTime = 0.f;
}

MoveObject::~MoveObject()
{
}

bool MoveObject::Init()
{
	return true;
}

void MoveObject::Input(float fDeltaTime)
{
	Object::Input(fDeltaTime);
}

int MoveObject::Update(float fDeltaTime)
{
	if (m_bIsPhysics)
	{
		m_fGravityTime += fDeltaTime;


		m_fForce -= (GRAVITY * m_fGravityTime * m_fGravityTime);

		//m_tPos.y += (GRAVITY * m_fGravityTime * m_fGravityTime);

		m_tPos.y -= m_fForce * fDeltaTime;
	}


	Object::Update(fDeltaTime);
	return 0;
}

int MoveObject::LateUpdate(float fDeltaTime)
{
	Object::LateUpdate(fDeltaTime);
	return 0;
}

void MoveObject::Collision(float fDeltaTime)
{
	Object::Collision(fDeltaTime);
}

void MoveObject::Render(HDC hDC, float fDeltaTime)
{
	Object::Render(hDC, fDeltaTime);



	m_bMove = false;
}


void MoveObject::Move(float x, float y)
{
	m_tPos.x += x;
	m_tPos.y += y;

	m_bMove = true;
}

void MoveObject::Move(float x, float y, float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime;
	m_tPos.y += y * fDeltaTime;

	m_bMove = true;

}

void MoveObject::Move(const POSITION & tMove)
{
	m_tPos += tMove;

	m_bMove = true;
}

void MoveObject::Move(const POSITION & tMove, float fDeltaTime)
{
	m_tPos += tMove * fDeltaTime;
	m_bMove = true;
}

void MoveObject::MoveX(float x)
{
	m_tPos.x += x;
	m_bMove = true;
}

void MoveObject::MoveXFromSpeed(float fDeltaTime, MOVE_DIR eDir)
{
		m_tPos.x += m_fSpeed * fDeltaTime  * eDir;
}

void MoveObject::MoveX(float x, float fDeletaTime)
{
	m_tPos.x += x * fDeletaTime;
	m_bMove = true;
}

void MoveObject::MoveY(float y)
{
	m_tPos.y += y;
	m_bMove = true;
}

void MoveObject::MoveY(float y, float fDeletaTime)
{
	m_tPos.y += y * fDeletaTime;
	m_bMove = true;
}

void MoveObject::MoveYFromSpeed(float fDeltaTime, MOVE_DIR eDir)
{
	m_tPos.y += m_fSpeed * fDeltaTime * eDir;
}


void MoveObject::MoveAngle()
{
	m_tPos.x += cosf(m_fAngle) * m_fSpeed;
	m_tPos.y += sinf(m_fAngle) * m_fSpeed;
}

void MoveObject::MoveAngle(float fDeltaTime)
{
	m_tPos.x += cosf(m_fAngle) * m_fSpeed * fDeltaTime;
	m_tPos.y += sinf(m_fAngle) * m_fSpeed * fDeltaTime;
	//m_bMove = true;
}

void MoveObject::Jump(float fDeltaTime)
{
	m_bMove = true;

	if (!m_bFalling)
	{
		m_fJumpTime += fDeltaTime;


		MoveY(-5.f);
		m_bFalling = true;
		m_fForce = m_fForceOrigin;
		m_bJump = true;
	}
}

void MoveObject::DoubleJump()
{
	m_bMove = true;

	if (m_bJump)
	{
		ClearGravity();
		JumpEnd();


		Jump(0.f);
		m_bJump = true;
	}
}

void MoveObject::JumpEnd()
{
	m_bFalling = false;
	m_fForce = 0.f;
	m_bJump = false;
	m_fJumpTime = 0.f;
}








