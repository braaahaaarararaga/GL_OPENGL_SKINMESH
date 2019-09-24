#include "main.h"
#include "polygon.h"
#include "texture.h"

unsigned int g_PolygonTexture;

void InitPolygon()
{
	g_PolygonTexture = LoadTexture("asset/0.tga");
}

void DrawPolygon()
{
	glDisable(GL_LIGHTING);  //  ライティング無効

	// projection 設定
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 960, 540, -20, 0, 1);

	glBindTexture(GL_TEXTURE_2D, g_PolygonTexture);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0.0f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 40.0f, 0.0f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(40.0f, 0, 0.0f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(40.0f, 40.0f, 0.0f);

	glEnd();

	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

