#include "main.h"
#include "light.h"
void SetLight()
{
	VECTOR4 lightPosition;
	lightPosition.x = -1.0f;
	lightPosition.y = 1.0f;
	lightPosition.z = -1.0f;
	lightPosition.w = 0.0f; // 1 pointlight 0 directlight
	VECTOR4 lightAmbient;
	lightAmbient.x = 0.75f;
	lightAmbient.y = 0.75f;
	lightAmbient.z = 0.75f;
	lightAmbient.w = 1.0f;
	VECTOR4 lightDiffuse;
	lightDiffuse.x = 1.0f;
	lightDiffuse.y = 1.0f;
	lightDiffuse.z = 1.0f;
	lightDiffuse.w = 1.0f;
	VECTOR4 lightSpecular;
	lightDiffuse.x = 1.0f;
	lightDiffuse.y = 1.0f;
	lightDiffuse.z = 1.0f;
	lightDiffuse.w = 1.0f;
	glLightfv(GL_LIGHT0, GL_POSITION, (float*)&lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, (float*)&lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, (float*)&lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, (float*)&lightSpecular);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}
