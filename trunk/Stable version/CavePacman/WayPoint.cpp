#include "WayPoint.h"


WayPoint::WayPoint(int x, int z, bool up, bool down, bool left, bool right)
{
	this->x = x;
	this->z = z;
	this->left = left;
	this->right = right;
	this->up = up;
	this->down = down;
}

int WayPoint::getNewDirection(int currentDirection)
{
	int direction = -1;
	while(direction==-1)
	{
		switch(rand()%4)
		{
			case 0: if(left==true && currentDirection!=RIGHT){direction=LEFT;} break;
			case 1: if(right==true && currentDirection!=LEFT){direction=RIGHT;} break;
			case 2: if(up==true && currentDirection!=DOWN){direction=UP;} break;
			case 3: if(down==true && currentDirection!=UP){direction=DOWN;} break;
		}
	}
	return direction;
}


