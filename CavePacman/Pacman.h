#ifndef PACMAN_H
#define PACMAN_H
#include <vrj/Draw/OpenGL/App.h>
#include <gl/GL.h>
class Pacman
{
public:
	Pacman(float x, float z);
	float getX()const{return x;}
	float getY()const{return y;}
	float getZ()const{return z;}
	float getRotation()const{return rotation;}
	int getXGrid()const{return (int)(x/10);}
	int getZGrid()const{return (int)(z/10);}
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void moveX(float amount);
	void moveZ(float amount);
	void rotate(float amount);
	void jump();
	void update();
	void draw();

private:
	float x, y, z, w, h, d;
	float jumpSpeed;
	float rotation;
	int direction;
};
#endif

