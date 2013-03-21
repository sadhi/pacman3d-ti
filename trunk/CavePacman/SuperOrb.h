#ifndef SUPERORB_H
#define SUPERORB_H
#include "orb.h"
class SuperOrb :public Orb
{
public:
	SuperOrb(int x, int z);
	virtual void update();
	virtual void draw();
};
#endif

