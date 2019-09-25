


#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "camera.h"
#include "field.h"
#include "cube.h"
#include "input.h"
#include "light.h"
#include "model.h"
#include "modelAnimation.h"
#include "resource.h"
#include <memory>

const char* CLASS_NAME = "OpenGALAppClass";
const char* WINDOW_NAME = "OpenGAY";


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND g_Window;

HWND GetWindow()
{
	return g_Window;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		MAKEINTRESOURCE(IDR_MENU1),
		CLASS_NAME,
		NULL
	};

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	g_Window = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU)),
		NULL,
		NULL,
		hInstance,
		NULL);


	// ����������(�E�B���h�E���쐬���Ă���s��)
	Init(g_Window);


	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);



	//�t���[���J�E���g������
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;


	// ���b�Z�[�W���[�v
	MSG msg;
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();

				// �`�揈��
				Draw();
			}
		}
	}

	timeEndPeriod(1);				// ����\��߂�

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	return (int)msg.wParam;
}


//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_BUTT_PUBE:
			MessageBoxA(g_Window, "DONT TOUCH PUBE!!", "CAPTION", MB_OK);
			break;
		case ID_BUTT_CLICK:
			MessageBoxA(g_Window, "pube�͒p���̈Ӗ������`", "CAPTION", MB_OK);
			break;
		case ID_BOX2_X1:
		{
			OPENFILENAME of;
			char fileName[MAX_PATH];
			ZeroMemory(fileName, MAX_PATH);
			memset(&of, 0, sizeof(of));
			of.lStructSize = sizeof(of);
			of.hwndOwner = g_Window;
			of.lpstrFilter = "FBX�t�@�C��(*.fbx)\0*.fbx\0";
			of.lpstrTitle = "Open";
			of.lpstrFile = fileName;
			of.nMaxFile = MAX_PATH;
			of.Flags = OFN_PATHMUSTEXIST;
			of.lpstrDefExt = "fbx";
			if (GetOpenFileName(&of))
			{
				LoadModel(fileName);
			}
			break;
		}
		default:
			break;
		}
	}
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//  Drag Drop
//  case : WM_CREATE:  
//   {  DragAcceptFiles(window, TRUE); break;}
//   ..   case WM_DROPFILES:
//   { HDROP drop = (HDROP)wParam;
//     char fileName[MAX_PATH];
//     DragQueryFileA(Drop, 0, fileName, MAX_PATH); ...  break ;}

std::unique_ptr<ModelAnimation> model;
void Init(HWND wnd)
{
	CInput::Init();
	InitRenderer(wnd);
	InitModel();
	model = std::make_unique<ModelAnimation>("./asset/Model/mixamo/Walking2.fbx");
	InitPolygon();
}

void Uninit()
{
	UninitModel();
	CInput::Uninit();
	model.release();
	UninitRenderer();
}

void Update()
{
	CInput::Update();
	UpdateModel();
	model->Update();
	UpdateCamera();
	
}

void LoadModel(const char* filepath)
{
	model.release();
	model = std::make_unique<ModelAnimation>(filepath);
}

void Draw()
{
	BeginRenderer();

	DrawCamera()
		;
	SetLight();
	//DrawCube();
	
	DrawModel();
	model->Draw();

	DrawField();
	DrawPolygon();

	EndRenderer();
}