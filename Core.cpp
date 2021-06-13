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
	//�ܼ�â�� ���������ִ� �Լ��̴�
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

	//ȭ�� DC�� �������

	m_hDC = GetDC(m_hWnd);


	//Timer �ʱ�ȭ
	if (!Timer::GetInst()->Init(m_hWnd))
	{
		return false;
	}

	//��� ������ �ʱ�ȭ
	if (!PathManager::GetInst()->Init())
	{
		return false;
	}

	//���ҽ� ������ �ʱ�ȭ
	if (!ResourceManager::GetInst()->Init(m_hInst, m_hDC))
	{
		return false;
	}

	//�Է� ������ �ʱ�ȭ
	if (!Input::GetInst()->Init(m_hWnd))
	{
		return false;
	}

	//SceneManager �ʱ�ȭ
	if (!SceneManager::GetInst()->Init())
	{
		return false;
	}

	//ī�޶� �ʱ�ȭ
	if (!Camera::GetInst()->Init(POSITION(0.f, 0.f), m_tRS, RESOLUTION(1861, 720)))
	{
		return false;
	}

	//���� �ʱ�ȭ
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


	// �⺻ �޽��� �����Դϴ�:
	while (m_bLoop)
	{
		/*
			GetMessage �Լ��� ���������� �޽��� ť���� �޽����� �д´�.
			�޽����� ������ �� �� �ִ� ��ɵ� GetMessage�� �����ϴ�.
			�׷��� �� �Լ��� GetMessage�ʹ� �޸� ���� �޽����� ������ �������� ������
			ť�� ��� ���� ��� ������� �ʰ� ��ٷ� �����Ѵٴ� ���� �ٸ���.
			���� �� �Լ��� �޽����� ���� �ʰ� �ܼ��� �޽����� �ִ��� Ȯ�θ� �� �� ������
			�̷� Ư���� ��׶��� �۾��� �����ϴ�.
		*/
		//PeekMessage�� �޼����� �޼��� ť�� ��� �ٷ� �������´�
		//�޼����� �ִ°��true ���°�� false 
		//���� �ð��� �������� ����Ÿ���̴�.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//������ ����Ÿ���� ���
		else
		{
			Logic();
		}

	}


	return (int)msg.wParam;
}


void Core::Logic()
{
	//Ÿ�̸� ����
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
	//���� ���۸�
	Texture* pBackBuffer = ResourceManager::GetInst()->GetBackBuffer();

	SceneManager::GetInst()->Render(pBackBuffer->GetDC(), fDeltaTime);

	//�������� ���콺�� �׸���.
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


	//���� �������� Ÿ��Ʋ�ٳ� �޴��� ǥ���� �������� ũ�⸦ �����ش�
	RECT rc = { 0 ,0, static_cast<long>(m_tRS.iW), static_cast<long>(m_tRS.iH) };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	//������ ������ ũ��� ������ Ŭ���̾�Ʈ ������ ũ�⸦ �����Ѵ�
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

		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
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

