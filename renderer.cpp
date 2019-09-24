#include "renderer.h"

HWND g_Wnd;
HGLRC g_GLRC;
HDC g_DC;

void InitRenderer(HWND wnd)
{
	g_Wnd = wnd;
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 24, 
		0,0,0,0,0,0,
		0,0,0,
		0,0,0,0,
		32,0,0,
		PFD_MAIN_PLANE,
		0,0,0,0
	};
	g_DC = GetDC(g_Wnd);
	int pixelFormat = ChoosePixelFormat(g_DC, &pfd);
	SetPixelFormat(g_DC, pixelFormat, &pfd);
	g_GLRC = wglCreateContext(g_DC);
	wglMakeCurrent(g_DC, g_GLRC);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.5f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void UninitRenderer()
{
	wglMakeCurrent(NULL, NULL);
	ReleaseDC(g_Wnd, g_DC);
	wglDeleteContext(g_GLRC);
}

void BeginRenderer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

void EndRenderer()
{
	SwapBuffers(g_DC);
}
