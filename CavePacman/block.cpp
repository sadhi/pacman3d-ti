#include "block.h"
#include "stdio.h"

Block::Block(){}

Block::Block(float x, float y, float z, float w, float h, float d, float xSpeed, float ySpeed, float zSpeed)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->h = h;
	this->d = d;
	this->xSpeed = xSpeed;
	this->ySpeed = ySpeed;
	this->zSpeed = zSpeed;
}

Block::Block(float x, float z)
{
	this->x = (x*10.0f)-5.0f;
	this->y = -5.0f;
	this->z = (z*10.0f)-5.0f;
	this->w = 10.0f;
	this->h = 10.0f;
	this->d = 10.0f;

	this->red = 1.0f;
	this->green = 1.0f;
	this->blue = 1.0f;
}

BOOL Block:: contains(float x2, float y2, float z2)
{
	//std::cout << x2 << ", " << y2 << ", " << z2 << std::endl;
	if(x2 >= x && x2 <= x+w && y2 >= y && y2 <= y+h && z2 >= z && z2 <= z+d)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Block:: setColor(float red, float green, float blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

void Block:: update()
{
	//this->xSpeed -= xSpeed/10.0f;
	this->x -= xSpeed;
	//this->ySpeed -= 0.005f;
	this->y += ySpeed;
	//this->zSpeed -= zSpeed/10.0f;
	this->z -= zSpeed;
}

void Block:: draw()
{
	glColor3f(red, green, blue);
	glNormal3d(0, 0, 1);
	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0,0); glVertex3f(x, y, z);
	glTexCoord2f(0,1); glVertex3f(x, y+h, z);
	glTexCoord2f(1,1); glVertex3f(x+w, y+h, z);
	glTexCoord2f(1,0); glVertex3f(x+w, y, z);
	//front
	glTexCoord2f(0,0); glVertex3f(x, y, z+d);
	glTexCoord2f(0,1); glVertex3f(x, y+h, z+d);
	glTexCoord2f(1,1); glVertex3f(x+w, y+h, z+d);
	glTexCoord2f(1,0); glVertex3f(x+w, y, z+d);
	//down
	glTexCoord2f(0,0); glVertex3f(x, y, z+d);
	glTexCoord2f(0,1); glVertex3f(x+w, y, z+d);
	glTexCoord2f(1,1); glVertex3f(x+w, y, z);
	glTexCoord2f(1,0); glVertex3f(x, y, z);
	//up
	glTexCoord2f(0,0); glVertex3f(x, y+h, z+d);
	glTexCoord2f(0,1); glVertex3f(x+w, y+h, z+d);
	glTexCoord2f(1,1); glVertex3f(x+w, y+h, z);
	glTexCoord2f(1,0); glVertex3f(x, y+h, z);
	//left
	glTexCoord2f(0,0); glVertex3f(x, y, z+d);
	glTexCoord2f(0,1); glVertex3f(x, y, z);
	glTexCoord2f(1,1); glVertex3f(x, y+h, z);
	glTexCoord2f(1,0); glVertex3f(x, y+h, z+d);
	//right
	glTexCoord2f(0,0); glVertex3f(x+w, y, z+d);
	glTexCoord2f(0,1); glVertex3f(x+w, y, z);
	glTexCoord2f(1,1); glVertex3f(x+w, y+h, z);
	glTexCoord2f(1,0); glVertex3f(x+w, y+h, z+d);
	glEnd();
}
