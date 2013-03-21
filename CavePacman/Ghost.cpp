#include "Ghost.h"


Ghost::Ghost(float x, float z)
{
	this->x = (x*10.0f)-5.0f;
	this->y = -5.0f;
	this->z = (z*10.0f)-5.0f;
	this->w = 10.0f;
	this->h = 10.0f;
	this->d = 10.0f;

	this->red = (rand()%100)/100.0f;
	this->green = (rand()%100)/100.0f;
	this->blue = (rand()%100)/100.0f;
}

void Ghost::move()
{
	//Move randomly
	int i = rand()%4;
	float distance = (rand()%100)/100.0f;
	switch(i)
	{
		case 0: x += distance; break;
		case 1: x -= distance; break;
		case 2: z += distance; break;
		case 3: z -= distance; break;
	}
	if(x < -5.0f)
	{
		x = -5.0f;
	}
	else if(x > 180.0f)
	{
		x = 180.0f;
	}
	if(z < -5.0f)
	{
		z = -5.0f;
	}
	else if(z > 180.0f)
	{
		z = 180.0f;
	}

}

void Ghost::update()
{

}

void Ghost::draw()
{
	glColor3f(red, green, blue);
	glPushMatrix();
	glTranslatef(x + 5.0f, 0.0f, z + 5.0f);
	drawSphere(4.5, 20, 20);
	glPopMatrix();
}

void Ghost::drawSphere(double r, int lats, int longs) 
{
	float M_PI = 3.14159265359f;
      int i, j;
      for(i = 0; i <= lats; i++) {
            double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
           double z0  = sin(lat0);
          double zr0 =  cos(lat0);
    
          double lat1 = M_PI * (-0.5 + (double) i / lats);
           double z1 = sin(lat1);
          double zr1 = cos(lat1);
    
          glBegin(GL_QUAD_STRIP);
           for(j = 0; j <= longs; j++) {
              double lng = 2 * M_PI * (double) (j - 1) / longs;
              double x = cos(lng);
               double y = sin(lng);
    
              glNormal3f(x * zr0, y * zr0, z0);
               glVertex3f(x * zr0, y * zr0, z0);
             glNormal3f(x * zr1, y * zr1, z1);
              glVertex3f(x * zr1, y * zr1, z1);
           }
           glEnd();
       }
}

