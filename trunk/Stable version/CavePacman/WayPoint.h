#ifndef WAYPOINT_H
#define WAYPOINT_H
#include <stdlib.h>

class WayPoint
{
	public:
	static const int LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4;
	WayPoint(int x, int z, bool up, bool down, bool left, bool right);
	int WayPoint:: getX()const{return x;}
	int WayPoint:: getZ()const{return z;}
	int getNewDirection(int currentDirection);

	private:
	int x, z;
	bool left, right, up, down;

};
#endif

