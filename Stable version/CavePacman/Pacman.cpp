#include "Pacman.h"
const int LEFT = 300, RIGHT = 301, UP = 302, DOWN = 303;

Pacman::Pacman(float x, float z)
{
	this->x = x;
	this->y = 0.0f;
	this->z = z;
	this->w = 10.0f;
	this->h = 10.0f;
	this->d = 10.0f;
	this->jumpSpeed = 0.0f;
	this->rotation = 0.0f;
	this->direction = UP;
}

int Pacman::getXGrid()
{
	return (int)((x+5.0f)/10);
}

int Pacman::getZGrid()
{
	return (int)((z+5.0f)/10);
}

int Pacman::determineXGridLeft(float amount)
{
	return (int)((x+0.0f+amount)/10);
}

int Pacman::determineXGridRight(float amount)
{
	return (int)((x+10.0f+amount)/10);
}

int Pacman::determineZGridUp(float amount)
{
	return (int)((z+0.0f+amount)/10);
}

int Pacman::determineZGridDown(float amount)
{
	return (int)((z+10.0f+amount)/10);
}

void Pacman::setX(float x)
{
	this->x = x;
}
	
void Pacman::setY(float y)
{
	this->y = y;
}
	
void Pacman::setZ(float z)
{
	this->z = z;
}

void Pacman::moveX(float amount)
{
	this->x += amount;
}
	
void Pacman::moveZ(float amount)
{
	this->z += amount;
}

void Pacman::rotate(float amount)
{
	this->rotation += amount;
	if(rotation > 0.0f)
	{
		rotation += 360.0f;
	}
	else if(rotation < 360.0f)
	{
		rotation -= 360.0f;
	}
}

void Pacman::jump()
{
	if(jumpSpeed==0.0f && y==0.0f)
	{
		jumpSpeed = 2.0f;
		update();
	}
}

void Pacman::update()
{
	if(jumpSpeed!=0.0f)
	{
		y += jumpSpeed;
		if(jumpSpeed > 0)
		{
			jumpSpeed -= (jumpSpeed/10.0f);
		}
		else
		{
			jumpSpeed += (jumpSpeed/10.0f);
		}
		if(jumpSpeed > 0.0f && jumpSpeed <= 0.1f)
		{
			jumpSpeed = -jumpSpeed;
		}
		else if(y <= 0.0f)
		{
			y = 0.0f;
			jumpSpeed = 0.0f;
		}
	}
}

void Pacman::draw()
{

}

