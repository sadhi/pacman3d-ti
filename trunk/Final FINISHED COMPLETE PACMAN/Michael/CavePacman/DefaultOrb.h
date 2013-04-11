#ifndef DEFAULTORB_H
#define DEFAULTORB_H
#include "orb.h"
class DefaultOrb:public Orb
{
public:
	DefaultOrb(int x, int z);
	virtual void update();
	virtual void draw();
};
#endif

