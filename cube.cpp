#include "main.h"
#include "cube.h"
#include "input.h"
#include "light.h"

float angle = 0.0f;
float x = 0.0f;
float y = 3.0f;
float z = -5.0f;
float moveSpeed = 0.07f;
float size = 1.0f;
void DrawCube()
{
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	// matrix setting

	//-
	angle += 1.6f;
	int xinput = CInput::GetKeyPress('A') - CInput::GetKeyPress('D');
	x += xinput * moveSpeed;
	int zinput = CInput::GetKeyPress('W') -CInput::GetKeyPress('S');
	z += zinput * moveSpeed;
	int sizeInput = CInput::GetKeyPress('Q') - CInput::GetKeyPress('E');
	size += sizeInput * 0.04f;
	glTranslatef(x, y, z);
	glRotatef(angle, 0.2f, 0.2f, 0.0f);
	glScalef(size, size, size);
	//-
	

	VECTOR4 diffuse, ambient, specular;
	diffuse.x = 1.0f;
	diffuse.y = .5f;
	diffuse.z = .5f;
	diffuse.w = 1.0f;
	ambient.x = 0.7f;
	ambient.y = 0.7f;
	ambient.z = 0.7f;
	ambient.w = 1.0f;
	specular.x = 1.0f;
	specular.y = 1.0f;
	specular.z = 1.0f;
	specular.w = 1.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (float *)&diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (float *)&ambient);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (float *)&specular);
	
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.5f);

	glBindTexture(GL_TEXTURE_2D, 1);

	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-.5f, 0.5f, .5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(.5f, 0.5f, -.5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, .5f);


	glEnd();
	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(1.0f, .0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(.5f, 0.5f, -.5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(1.0f, .0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, .5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(1.0f, .0f, 0.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(.5f, -0.5f, -.5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(1.0f, .0f, 0.0f);
	glTexCoord2f(2.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, .5f);


	glEnd();
	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(.5f, -0.5f, -.5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(2.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, .5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(-.5f, -0.5f, -.5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(2.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, .5f);


	glEnd();
	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(-.5f, -0.5f, -.5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(2.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, .5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-.5f, 0.5f, .5f);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, .0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-.5f, 0.5f, .5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, .0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-.5f, -0.5f, .5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, .0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(.5f, 0.5f, .5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, .0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(.5f, -0.5f, .5f);

	glEnd();


	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, .0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(.5f, 0.5f, -.5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, .0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(.5f, -0.5f, -.5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, .0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-.5f, 0.5f, -.5f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, .0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-.5f, -0.5f, -.5f);

	glEnd();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
