#ifndef GHOST_H
#define GHOST_H
#include <vrj/Draw/OpenGL/App.h>
#include <gl/GL.h>
#include <gmtl/Math.h>
class Ghost
{
public:
	Ghost(float x, float z);
	void drawSphere(double r, int lats, int longs);
	void move();
	void update();
	void draw();

private:
	float x, y, z, w, h, d;
	float red, green, blue;
};
#endif

