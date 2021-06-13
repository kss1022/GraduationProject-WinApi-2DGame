#pragma once

#include "../Game.h"

class Timer
{
private:
	Timer();
	~Timer();

	static Timer* m_pInst;

	HWND			m_hWnd;
	LARGE_INTEGER	m_tSecond;
	LARGE_INTEGER	m_tTime;

	float	m_fDeltaTime;
	float	m_fTimeScale;
	float	m_fFPS;
	float	m_fFPSTime;
	int		m_iFrameMax;
	int		m_iFrame;

public:
	static Timer* GetInst();
	static void DestroyInst();

	bool Init(HWND hWnd);
	void Update();

	inline float GetDeltaTime() const;
	inline float GetTimeScale() const;
	inline float GetFPS() const;
	
	inline void SetTimeScale(const float fTimeScale);
};



float Timer::GetDeltaTime() const
{
	return m_fDeltaTime * m_fTimeScale;
}

inline float Timer::GetTimeScale() const
{
	return m_fTimeScale;
}

float Timer::GetFPS() const
{
	return m_fFPS;
}

void Timer::SetTimeScale(const float fTimeScale)
{
	m_fTimeScale = fTimeScale;
}

