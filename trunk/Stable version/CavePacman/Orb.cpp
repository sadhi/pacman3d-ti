#include "Orb.h"


Orb::Orb(int x, int z): Sprite(x, z)
{
	this->type = ORB;
}

bool Orb::intersects(float x2, float z2)
{
	float aX = x + 10.0f-radius;
	float aZ = z +10.0f-radius;
	float aX2 = aX + (radius*2);
	float aZ2 = aZ + (radius*2);
	float bX = x2;
	float bZ = z2;
	float bX2 = x2+5.0f;
	float bZ2 = z2+5.0f;

	if(min(aX2, bX2) > max(aX, bX) && min(aZ2, bZ2) > max(aZ, bZ))
	{
		return true;
	}
	else
	{
		return false;
	}
}
