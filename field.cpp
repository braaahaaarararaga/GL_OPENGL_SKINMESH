#include "main.h"
#include "field.h"

void DrawField()
{
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	// matrix setting
	glBindTexture(GL_TEXTURE_2D,1);

	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-10.0f, 0.0f, -10.0f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-10.0f, 0.0f, 10.0f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, -10.0f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);

	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
