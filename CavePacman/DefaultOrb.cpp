#include "DefaultOrb.h"


DefaultOrb::DefaultOrb(int x, int z):Orb(x, z)
{
	this->x = (x*10.0f)-5.0f;
	this->y = -5.0f;
	this->z = (z*10.0f)-5.0f;
	this->w = 2.0f;
	this->h = 2.0f;
	this->d = 2.0f;
}

void DefaultOrb:: update()
{
}

void DefaultOrb::draw()
{
	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(x + 5.0f, 0.0f, z + 5.0f);
	drawSphere(2.0, 20, 20);
	glPopMatrix();
}
