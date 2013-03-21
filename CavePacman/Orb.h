#ifndef ORB_H
#define ORB_H
#include <vrj/Draw/OpenGL/App.h>
#include <gl/GL.h>
#include <gmtl/Math.h>
class Orb
{
public:
	Orb(int x, int z);
	bool Orb:: contains(float x2, float y2, float z2);
	virtual void update();
	virtual void draw();
	void drawSphere(double r, int lats, int longs);

protected:
	float x, y, z, w, h, d;
};
#endif

