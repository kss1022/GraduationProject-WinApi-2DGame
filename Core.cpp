#include "Core.h"
#include "Scene/SceneManager.h"
#include "Core/Timer.h"
#include "Core//PathManager.h"
#include "Resource/ResourceManager.h"
#include "Resource//Texture.h"
#include "Core/Camera.h"
#include "Core/Input.h"
#include "Collider/CollisionManager.h"
#include "Object/Mouse.h"
#include "Sound/SoundManager.h"

Core* Core::m_pInst = nullptr;
bool Core::m_bLoop = true;

Core::Core()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(28510);

#ifdef _DEBUG
	//콘솔창을 생성시켜주는 함수이다
	AllocConsole();
#endif // _DEBUG
}

Core::~Core()
{
	SceneManager::DestroyInst();
	Timer::DestroyInst();
	PathManager::DestroyInst();
	ResourceManager::DestroyInts();
	CollisionManager::DestroyInst();

	Camera::DestroyInst();
	Input::DestroyInst();
	SoundManager::DestroyInst();

	ReleaseDC(m_hWnd, m_hDC);


#ifdef _DEBUG
	FreeConsole();
#endif // _DEBUG
}


Core * Core::GetInst()
{
	if (!m_pInst)
	{
		m_pInst = new Core;
	}
	return m_pInst;
}

void Core::DestroyInst()
{
	delete m_pInst;
	m_pInst = nullptr;
}

bool Core::Init(HINSTANCE hInst)
{
	this->m_hInst = hInst;
	MyRegisterClass();

	m_tRS.iW = 1280;
	m_tRS.iH = 720;


	Create();

	//화면 DC를 만들어줌

	m_hDC = GetDC(m_hWnd);


	//Timer 초기화
	if (!Timer::GetInst()->Init(m_hWnd))
	{
		return false;
	}

	//경로 관리자 초기화
	if (!PathManager::GetInst()->Init())
	{
		return false;
	}

	//리소스 관리자 초기화
	if (!ResourceManager::GetInst()->Init(m_hInst, m_hDC))
	{
		return false;
	}

	//입력 관리자 초기화
	if (!Input::GetInst()->Init(m_hWnd))
	{
		return false;
	}

	//SceneManager 초기화
	if (!SceneManager::GetInst()->Init())
	{
		return false;
	}

	//카메라 초기화
	if (!Camera::GetInst()->Init(POSITION(0.f, 0.f), m_tRS, RESOLUTION(1861, 720)))
	{
		return false;
	}

	//사운드 초기화
	if (!SoundManager::GetInst()->Init())
	{
		return false;
	}

	SoundManager::GetInst()->LoadSound("BGM", true, "TitleScreen.wav");
	SoundManager::GetInst()->Play("BGM");
	SoundManager::GetInst()->Volume(ST_BGM, 0.3f);

	return true;
}

int Core::Run()
{
	MSG msg;


	// 기본 메시지 루프입니다:
	while (m_bLoop)
	{
		/*
			GetMessage 함수와 마찬가지로 메시지 큐에서 메시지를 읽는다.
			메시지의 범위를 줄 수 있는 기능도 GetMessage와 동일하다.
			그러나 이 함수는 GetMessage와는 달리 읽은 메시지를 무조건 제거하지 않으며
			큐가 비어 있을 경우 대기하지 않고 곧바로 리턴한다는 점이 다르다.
			따라서 이 함수는 메시지를 읽지 않고 단순히 메시지가 있는지 확인만 할 수 있으며
			이런 특성은 백그라운드 작업에 적절하다.
		*/
		//PeekMessage는 메세지가 메세지 큐에 없어도 바로 빠져나온다
		//메세지가 있는경우true 없는경우 false 
		//없는 시간이 윈도우의 데드타임이다.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//윈도우 데드타임의 경우
		else
		{
			Logic();
		}

	}


	return (int)msg.wParam;
}


void Core::Logic()
{
	//타이머 갱신
	Timer::GetInst()->Update();

	float fDeltaTime = Timer::GetInst()->GetDeltaTime();


	Input(fDeltaTime);
	if (Update(fDeltaTime) == SC_CHANGE)
	{
		return;
	}

	if (LateUpdate(fDeltaTime) == SC_CHANGE)
	{
		return;
	}
	Collision(fDeltaTime);
	Render(fDeltaTime);
}


void Core::Input(float fDeltaTime)
{
	Input::GetInst()->Update(fDeltaTime);
	SceneManager::GetInst()->Input(fDeltaTime);
	Camera::GetInst()->Input(fDeltaTime);
}

int Core::Update(float fDeltaTime)
{
	SCENE_CHANGE	sc;
	sc = SceneManager::GetInst()->Update(fDeltaTime);
	Camera::GetInst()->Update(fDeltaTime);

	return sc;
}

int Core::LateUpdate(float fDeltaTime)
{
	SCENE_CHANGE	sc;
	sc = SceneManager::GetInst()->LateUpdate(fDeltaTime);
	return 0;
}

void Core::Collision(float fDeltaTime)
{
	SceneManager::GetInst()->Collision(fDeltaTime);
	CollisionManager::GetInst()->Collision(fDeltaTime);
}

void Core::Render(float fDeltaTime)
{
	//더블 버퍼링
	Texture* pBackBuffer = ResourceManager::GetInst()->GetBackBuffer();

	SceneManager::GetInst()->Render(pBackBuffer->GetDC(), fDeltaTime);

	//마지막에 마우스를 그린다.
	Mouse* pMouse = Input::GetInst()->GetMouse();

	pMouse->Render(pBackBuffer->GetDC(), fDeltaTime);

	BitBlt(m_hDC, 0, 0, m_tRS.iW, m_tRS.iH, pBackBuffer->GetDC(), 0, 0, SRCCOPY);



	pBackBuffer->Release();


	pBackBuffer = nullptr;
}

ATOM Core::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL; //MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
	wcex.lpszClassName = L"Project";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassExW(&wcex);
}

BOOL Core::Create()
{
	m_hWnd = CreateWindowW(L"Project", L"Project", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
	{
		return FALSE;
	}


	//실제 윈도우의 타이틀바나 메뉴를 표함한 위도우의 크기를 구해준다
	RECT rc = { 0 ,0, static_cast<long>(m_tRS.iW), static_cast<long>(m_tRS.iH) };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	//위에서 구해준 크기로 윈도우 클라이언트 영영의 크기를 설정한다
	SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left,
		rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);


	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return TRUE;
}

LRESULT Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		break;
	case WM_CREATE:

		MoveWindow(hWnd, 100, 50, 1280, 720, TRUE);

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		m_bLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Core::DestroyGame()
{
	DestroyWindow(m_hWnd);
}

