#include "main.h"
#include "camera.h"
#include "input.h"

float CAMx = 0.0f;
float CAMy = 5.0f;
float CAMz = 10.0f;
float xangle = 0.0f;

void DrawCamera()
{
	double aspect = 960.0 / 540.0;
	glViewport(0, 0, 960, 540);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(	CAMx, CAMy, CAMz,	// 視点
				0.0, 5.0, 0.0,		// 注視点
				0.0, 1.0, 0.0);		// 上ベクトル
}

void UpdateCamera()
{
	if (CInput::GetKeyPress(VK_LEFT))
	{
		xangle += 10.0f;
	}
	if (CInput::GetKeyPress(VK_RIGHT))
	{
		xangle -= 10.0f;
	}

	CAMx = sin(xangle / 180 * 3.14) * 10;
	CAMz = cos(xangle / 180 * 3.14) * 10;

}
