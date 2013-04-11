#pragma once

#include <vrj/Draw/OpenGL/App.h>
#include <gadget/Type/PositionInterface.h>

class Mycave : public vrj::opengl::App
{
public:
	Mycave(void);
	~Mycave(void);

	void init();
	void contextInit();

	void preFrame();
	void bufferPreDraw();
	void draw();

	//homemade
	void drawCF();
	void CFLights();
	bool CFFarAwayFromHead(float X1, float Y1, float Z1, float X2, float Y2, float Z2);
	float CFDistanceFromHead(float X1, float Y1, float Z1, float X2, float Y2, float Z2);

	void drawCC();

	//cavegame
	void SetGhostStep();
	void placeWayPoint();
	void drawpathfindingdemo();
	void drawWaypoint(float Corx, float Cory, bool up, bool down, bool left, bool right, int WPnr);
	void CheckDir(float Corx, float Cory, float GX, float GY, bool up, bool down, bool left, bool right, int WPnr, int Gnr);
	int CheckDir(bool up, bool down, bool left, bool right, int WPnr, int Gnr);
};
