#pragma once

#include <windows.h>
#include <gl/GL.h>
#include <string>

class WayPoint
{
public:
	WayPoint();
	WayPoint(float Corx, float Cory, bool up, bool down, bool left, bool right);
	~WayPoint(void);
	void init(float Corx, float Cory, bool up, bool down, bool left, bool right);
	void draw();


};

