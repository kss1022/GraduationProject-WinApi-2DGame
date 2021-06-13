#include "Camera.h"
#include "../Object/Object.h"

Camera*	Camera::m_pInst = nullptr;

Camera::Camera() : m_pTarget(nullptr)
{
}

Camera::~Camera()
{
	if(m_pTarget)
	{
	m_pTarget->Release();
	m_pTarget = nullptr;
	}
}

Camera * Camera::GetInst()
{
	if (!m_pInst)
	{
		m_pInst = new Camera;
	}
	return m_pInst;
}

void Camera::DestroyInst()
{
	delete m_pInst;
	m_pInst = nullptr;
}



bool Camera::Init(const POSITION & tPos, const RESOLUTION & tRS, const RESOLUTION & tWorldRS)
{
	m_tPos = tPos;
	m_tClientRS = tRS;
	m_tWolrdRS = tWorldRS;
	m_tPivot = POSITION(0.5f, 0.5f);

	return true;
}

void Camera::Input(float fDeltaTime)
{
	if (!m_pTarget)
	{

	}
}

void Camera::Update(float fDeltaTIme)
{
	if (m_pTarget)
	{
		POSITION	tPos = m_pTarget->GetPos();
		POSITION	tPivot = m_pTarget->GetPivot();
		_SIZE		tSize = m_pTarget->GetSize();
		
		float fLeftArea = m_tClientRS.iW * m_tPivot.x;
		float fRightArea = m_tClientRS.iW - fLeftArea;
		float fTopArea = m_tClientRS.iH * m_tPivot.y;
		float fBottomArea = m_tClientRS.iH - fTopArea;

		//가로
		if (tPos.x <= fLeftArea)
		{
			m_tPos.x = 0.f;
		}

		else if (tPos.x >=  m_tWolrdRS.iW - fRightArea)
		{
			m_tPos.x = static_cast<float>( m_tWolrdRS.iW - m_tClientRS.iW);
		}

		else
		{
			m_tPos.x = tPos.x - m_tClientRS.iW * m_tPivot.x;
		}



		//세로
		if (tPos.y <= fTopArea)
		{
			m_tPos.y = 0.f;
		}

		else if (tPos.y >= m_tWolrdRS.iH - fBottomArea)
		{
			m_tPos.y = static_cast<float>( m_tWolrdRS.iH - m_tClientRS.iH);
		}

		else
		{
			m_tPos.y = tPos.y - m_tClientRS.iH * m_tPivot.y;
		}

	}
}

void Camera::Scroll(float x, float y)
{
	m_tPos.x += x;
	m_tPos.y += y;

	if (m_tPos.x <= 0 )
	{
		m_tPos.x = 0;
	}
	else if (m_tPos.x > m_tWolrdRS.iW - m_tClientRS.iW)
	{
		m_tPos.x = m_tWolrdRS.iW - m_tClientRS.iW;
	}


	if (m_tPos.y <= 0)
	{
		m_tPos.y = 0;
	}
	else if (m_tPos.y > m_tWolrdRS.iH -m_tClientRS.iH)
	{
		m_tPos.y = m_tWolrdRS.iH - m_tClientRS.iH;
	}
}


void Camera::SetTarget(Object * pObj)
{
	if(m_pTarget)
	{
	m_pTarget->Release();
	m_pTarget = nullptr;
	}

	m_pTarget = pObj;
	
	if (m_pTarget)
	{
		m_pTarget->AddRef();
	}
}