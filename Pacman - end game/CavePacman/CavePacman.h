#pragma once

#include <vrj/Draw/OpenGL/App.h>
#include <Windows.h>
#include <gl/GL.h>
#include <gadget/Type/PositionInterface.h>
#include <gadget/Type/KeyboardMouseInterface.h>
#include <gadget/Type/KeyboardMouse/KeyEvent.h>
#include <gadget/Type/KeyboardMouse/MouseEvent.h>
#include <cavelib/cavelib.h>
#include <cavelib/texture.h>
#include <math.h>
#include <vector>
#include <json/json.h>
#include "block.h"
#include "Orb.h"
#include "SuperOrb.h"
#include "DefaultOrb.h"
#include "Coordinate.h"
#include "Pacman.h"
#include "Ghost.h"
#include "WayPoint.h"
#include "Wave.h"
#include <tchar.h>
#include <time.h>

#include <fstream>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <math.h>

class CavePacman :
	public vrj::opengl::App
{
public:
	CavePacman(void);
	~CavePacman(void);

	void init();
	void contextInit();
	gmtl::Vec4f collisionLinePlane(gmtl::Vec3f A, gmtl::Vec3f B, gmtl::Planef plane);
	void preFrame();
	void bufferPreDraw();
	void draw();
	void draw3DRectangle(const float x1, const float y1, const float z1, const float w1, const float h1, const float d1);
	void draw3DRectangleWithoutTop(const float x1, const float y1, const float z1, const float w1, const float h1, const float d1);

	void loadWall();
	void addBlock(int x, int z);
	void addDefaultOrb(int x, int z);
	void addSuperOrb(int x, int z);
	void loadLevel();
	void loadOrbs();
	void loadWayPoints();
	void checkInput();
	void updateMovement();
	void updateGhosts();
	void clearLocation(int x, int z);
	void checkWand();
	void checkKeyboard();
	void restart();
	void cntdown();
	void draw2DPacman();
	void draw2DHUD();
	void drawPowerTime(int time);

private:
	gadget::PositionInterface wand;
	gadget::KeyboardMouseInterface keyboard;
	gmtl::Vec4f wandPoint;
	gmtl::Vec4f wandOrigin;
	gmtl::Vec4f wandDiff;
	gmtl::Vec4f wandForward;
	gmtl::Vec4f wallPointLeft;
	gmtl::Vec4f wallPointRight;
	gmtl::Vec4f wallPointForward;
	int currentWallNr;
	cTexture* texture;
	std::vector<Block> blocks;
	int frames;
	int direction;
	bool grid[17][18];
	Sprite* sprites[17][18];
	std::vector<Coordinate*> coordinates;

	Pacman* pacman;
	std::vector<Ghost*> ghosts;
	std::vector<WayPoint*> wayPoints;
//	Json::Value models;
	CWave sounds[6];
	bool useWand;

	bool dead, poweredup;
	clock_t Powerupstart;
	float countdown;
};
