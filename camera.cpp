#include "main.h"
#include "camera.h"
#include "input.h"



void Camera3D::Draw()
{
	double aspect = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,	// 視点
		xLookAt, yLookAt, zLookAt,		// 注視点
		0.0, 1.0, 0.0);		// 上ベクトル
}

void Camera3D::Update()
{
	if (CInput::GetKeyPress(VK_LEFT))
	{
		xangle += 10.0f;
	}
	if (CInput::GetKeyPress(VK_RIGHT))
	{
		xangle -= 10.0f;
	}
	if (Mouse::Get().GetState().leftButton && (Mouse::Get().mouseTracker.leftButton == Mouse::Get().mouseTracker.HELD))
	{
		yangle += (Mouse::Get().GetState().y - Mouse::Get().mouseTracker.GetLastState().y) * 0.05f;
		float mouseX = Mouse::Get().GetState().x;
		float lastMouseX = Mouse::Get().mouseTracker.GetLastState().x;
		xangle += (mouseX - lastMouseX) * 0.5f;
	}
	if (Mouse::Get().GetState().rightButton && (Mouse::Get().mouseTracker.rightButton == Mouse::Get().mouseTracker.HELD))
	{
		yLookAt -= (Mouse::Get().GetState().y - Mouse::Get().mouseTracker.GetLastState().y) * 0.05f;
	}
	if (Mouse::Get().GetState().middleButton && (Mouse::Get().mouseTracker.middleButton == Mouse::Get().mouseTracker.HELD))
	{
		distance += (Mouse::Get().GetState().y - Mouse::Get().mouseTracker.GetLastState().y) * 0.05f;
		distance = std::max<float>(distance, 0.1f);
	}
	x = sin(xangle / 180 * 3.14f) * distance + xLookAt;
	y = yangle + yLookAt;
	z = cos(xangle / 180 * 3.14f) * distance + zLookAt;
	

}
