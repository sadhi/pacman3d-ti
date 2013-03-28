#ifndef ORB_H
#define ORB_H
#include "Sprite.h"

class Orb: public Sprite
{
public:
	Orb(int x, int z);
	bool intersects(float x2, float z2);

protected:
	float radius;
};
#endif

