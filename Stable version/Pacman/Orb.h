#ifndef ORB_H
#define ORB_H
#include "Sprite.h"

class Orb: public Sprite
{
public:
	Orb(int x, int z);
	bool intersects(float x2, float z2);
	void initSphere(float radius, unsigned int rings, unsigned int sectors);
	void drawSphere();

protected:
	float radius;

    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;
};
#endif

