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
#include <vector>
#include <json/json.h>
#include "block.h"
#include "Orb.h"
#include "SuperOrb.h"
#include "DefaultOrb.h"
#include "Coordinate.h"
#include "Pacman.h"
#include "Ghost.h"



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
	void drawTextured3DRectangle(const float x1, const float y1, const float z1, const float w1, const float h1, const float d1);
	void draw3DRectangleWithoutTop(const float x1, const float y1, const float z1, const float w1, const float h1, const float d1);
	void drawSphere(double r, int lats, int longs) ;

	void addBlock(int x, int z);
	void addOrb(int x, int z);
	void loadLevel();
	void checkInput();
	void checkCollision();
	void updateMovement();
	

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
	bool grid[24][24];
	Block* objects[24][24];
	std::vector<Coordinate*> coordinates;

	bool orbGrid[24][24];
	Orb* orbs[24][24];
	std::vector<Coordinate*> orbCoordinates;

	Pacman* pacman;
	std::vector<Ghost*> ghosts;
	Json::Value models;
};

