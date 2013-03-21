#include "WayPoint.h"
#include <GL/GL.h>
#include <glut.h>

float X=0,Y=0;
bool UP, DOWN, LEFT, RIGHT;



WayPoint::WayPoint()
{
	init(0, 0, true, true, true, true);
}

WayPoint::WayPoint(float Corx, float Cory, bool up, bool down, bool left, bool right)
{
	init(Corx, Cory, up, down, left, right);
}


WayPoint::~WayPoint(void)
{

}

void WayPoint::init(float Corx, float Cory, bool up, bool down, bool left, bool right)
{
	X=Corx;
	Y=Cory;
	UP=up;
	DOWN=down;
	LEFT=left;
	RIGHT=right;
}


void WayPoint::draw()
{
	glPushMatrix();
	glTranslatef(X,0,Y);
	glutSolidSphere(0.3,16,16);
	if(DOWN){
		glutSolidCone(0.3,1.0,8,8);
	}
	if(UP){
		glRotatef(180,0,1,0);
			glutSolidCone(0.3,1.0,8,8);
		glRotatef(-180,0,1,0);
	}
	if(RIGHT){
		glRotatef(90,0,1,0);
		glutSolidCone(0.3,1.0,8,8);
		glRotatef(-90,0,1,0);
	}
	if(LEFT){
		glRotatef(270,0,1,0);
		glutSolidCone(0.3,1.0,8,8);
		glRotatef(-270,0,1,0);
	}
	glPopMatrix();
}
