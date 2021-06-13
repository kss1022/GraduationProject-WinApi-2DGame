#pragma once

#include "Game.h"

class Core
{
private:
	Core();
	~Core();

	static Core* m_pInst;

	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	HDC			m_hDC;
	RESOLUTION	m_tRS;		//해상도
	static bool		m_bLoop;

public:
	inline RESOLUTION	GetResoulution() const;
	inline HWND			GetWindowHandle() const;
	inline	HINSTANCE	GetWindowInsatnce() const;
public:
	static Core* GetInst();
	static void DestroyInst();


	bool Init(HINSTANCE hINst);
	int Run();
private:
	void Logic();
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);	//업데이트 후 후처리
	void Collision(float fDeltaTime);
	void Render(float fDeltaTime);

private:
	ATOM MyRegisterClass();
	BOOL Create();


	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


public:
	void DestroyGame();

};


RESOLUTION Core::GetResoulution() const
{
	return m_tRS;
}

inline HWND Core::GetWindowHandle() const
{
	return m_hWnd;
}

inline HINSTANCE Core::GetWindowInsatnce() const
{
	return m_hInst;
}

