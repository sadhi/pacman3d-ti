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
	Ghost(int x, int z);
	~Ghost(void);
	bool intersects(float x2, float y2, float z2);
	virtual void draw();

private:
	cModel* model;
	cTexture* texture;
	std::string modelFile;
	gmtl::Vec3f position;
	gmtl::Quatf rotation;

	float red, green, blue;

};
#endif
