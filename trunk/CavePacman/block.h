#ifndef BLOCK_H
#define BLOCK_H
#include <vrj/Draw/OpenGL/App.h>
#include <gl/GL.h>
#include <gmtl/Xforms.h>
#include <gmtl/Ray.h>
#include <gmtl/VecOps.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Math.h>

class Block
{
	protected:
	float x, y, z, w, h, d;
	float red, green, blue;
	float xSpeed, ySpeed, zSpeed;

	public:
	Block::Block();
	Block::Block(float x, float y, float z, float w, float h, float d, float xSpeed, float ySpeed, float zSpeed);
	Block::Block(float x, float z);

	float Block:: getX()const{return x;}
	float Block:: getY()const{return y;}
	float Block:: getZ()const{return z;}
	float Block:: getW()const{return w;}
	float Block:: getH()const{return h;}
	float Block:: getD()const{return d;}
	bool Block:: contains(float x2, float y2, float z2);
	void Block:: setColor(float red, float green, float blue);
	void Block:: update();
	void Block:: draw();
};

#endif