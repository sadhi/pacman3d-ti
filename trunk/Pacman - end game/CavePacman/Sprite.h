#ifndef SPRITE_H
#define SPRITE_H
#include <vrj/Draw/OpenGL/App.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <gmtl/Xforms.h>
#include <gmtl/Ray.h>
#include <gmtl/VecOps.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Math.h>

class Sprite
{
public:
	static const int BLOCK = 1, ORB = 2, SUPERORB = 3, DEFAULTORB = 4;
	Sprite(int x, int z);
	bool Sprite:: contains(float x2, float y2, float z2);
	int Sprite:: getType()const{return type;}
	bool Sprite:: isType(int type);
	float Sprite:: getX()const{return x;}
	float Sprite:: getZ()const{return z;}
	void Sprite:: setX(float x){this->x = x;}
	void Sprite:: setZ(float z){this->z = z;}
	virtual void update();
	virtual void draw();
	void drawSphere(double radius, int nSlice, int nStack);
	void draw3DRectangle(const float x1, const float y1, const float z1, const float w1, const float h1, const float d1);

protected:
	float x, y, z, w, h, d;
	int type;
};
#endif

