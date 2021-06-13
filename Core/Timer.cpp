#include "Timer.h"
#include <time.h>
Timer* Timer::m_pInst = nullptr;

Timer::Timer() :m_fTimeScale(1.0)
{
}

Timer::~Timer() 
{
}

Timer * Timer::GetInst()
{
	if (!m_pInst)
	{
		m_pInst = new Timer;
	}

	return m_pInst;
}

void Timer::DestroyInst()
{
	delete m_pInst;
	m_pInst = nullptr;
}

bool Timer::Init(HWND hWnd)
{
	srand((unsigned int)time(NULL));

	m_hWnd = hWnd;

	QueryPerformanceFrequency(&m_tSecond);
	QueryPerformanceCounter(&m_tTime);

	m_fDeltaTime = 0.f;
	m_fFPS = 0.f;
	m_fFPSTime= 0.f;
	m_iFrame = 0;

	return true;
}

void Timer::Update()
{
	LARGE_INTEGER tTime;

	QueryPerformanceCounter(&tTime);
	m_fDeltaTime = static_cast<float>( (tTime.QuadPart - m_tTime.QuadPart) / (float)m_tSecond.QuadPart );

	m_tTime = tTime;

	m_fFPSTime += m_fDeltaTime;
	++m_iFrame;

	if (m_fFPSTime >= 1.f)
	{
		m_fFPS = m_iFrame / m_fFPSTime;
		m_fFPSTime = 0.f;
		m_iFrame = 0;

//#ifdef _DEBUG
		char strFPS[64] = {};
		sprintf_s(strFPS, "FPS : %.f\n", m_fFPS );
		_cprintf(strFPS);
		SetWindowTextA(m_hWnd, strFPS);
		OutputDebugStringA(strFPS);
//#endif // DEBUG
	}
}
