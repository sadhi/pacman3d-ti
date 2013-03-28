#include "SuperOrb.h"

SuperOrb::SuperOrb(int x, int z):Orb(x, z)
{
	this->type = SUPERORB;

	this->x = (x*10.0f)-5.0f;
	this->y = -5.0f;
	this->z = (z*10.0f)-5.0f;
	this->w = 10.0f;
	this->h = 10.0f;
	this->d = 10.0f;

	this->radius = 3.0f;
}

void SuperOrb:: update()
{
}

void SuperOrb::draw()
{
	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(x + 5.0f, 0.0f, z + 5.0f);
	drawSphere(radius, 20, 20);
	glPopMatrix();
}
