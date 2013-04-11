#ifndef GHOST_H
#define GHOST_H
#include "Sprite.h"
#include <string>
#include <gmtl/Quat.h>
#include <gmtl/Vec.h>
//#include "CaveLib/CaveLib.h"

class cModel;
class cTexture;
class ShaderProgram;

class Ghost: public Sprite
{
public:
	static const int LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4;
	Ghost(int x, int z, int ghostNr);
	~Ghost(void);
	bool intersects(float x2, float y2, float z2);
	int Ghost:: getDirection()const{return direction;}
	void Ghost:: setDirection(float direction){this->direction = direction;}
	virtual void update();
	virtual void draw();
	void setrot(int rot);

private:
	cModel* model;
	cTexture* texture;
	std::string modelFile;
	gmtl::Vec3f position;

	float red, green, blue;
	int direction;
	int rotation;
};
#endif
