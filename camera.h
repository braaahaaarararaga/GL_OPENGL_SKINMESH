#pragma once

class Camera3D
{
public:
	Camera3D()
		:
		x(0.0f), y(5.0f), z(10.0f),
		xRot(0.0f), yRot(0.0f), zRot(0.0f),
		xLookAt(0.0f), yLookAt(5.0f), zLookAt(0.0f)
	{}
	void Draw();
	void Update();

private:
	float x, y, z;
	float xRot, yRot, zRot;
	float xLookAt, yLookAt, zLookAt;
	float xangle = 0.0f;
	float yangle = 0.0f;
	float distance = 10.0f;
};