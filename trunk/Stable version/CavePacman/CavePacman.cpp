#include <GL/glew.h>
#include "CavePacman.h"
#include <CaveLib/texture.h>
#include <cavelib/model.h>
#include <cavelib/Shader.h>

#include <fstream>
#include <iostream>

const int LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4;



CavePacman::CavePacman(void)
{
}

CavePacman::~CavePacman(void)
{

}

void CavePacman::init()
{
	useWand = true;

	wand.init("VJWand");
	keyboard.init("VJKeyboard");
	TextureLoadOptions* t = new TextureLoadOptions();
	t->sampler = TextureLoadOptions::CLOSEST;
	texture = CaveLib::loadTexture("Images/grid.jpg", t);
	sounds[0].Load("Sounds/pacman_beginning.wav");
	sounds[1].Load("Sounds/pacman_chomp.wav");
	sounds[2].Load("Sounds/pacman_death.wav");
	sounds[3].Load("Sounds/pacman_eatghost.wav");
	sounds[4].Load("Sounds/jump.wav");

	direction = UP;
	pacman = new Pacman(130.0f, 130.0f);
	for(int x = 0; x < 17; x++)
	{
		for(int z = 0; z < 18; z++)
		{
			grid[x][z] = false;
		}
	}

	loadWall();

	//for(int z = 0; z < 10; z++)
	//{
	//	addBlock(0, z);
	//	addBlock(2, z);
	//}
	loadLevel();
	loadOrbs();
	loadWayPoints();

	sounds[0].Play();
}

void CavePacman::loadWall()
{
	
}

void CavePacman::loadLevel()
{
	int coord[] = {13, 12, 13, 11, 13, 10, 14, 10,
		15, 10, 12, 10, 11, 10, 9, 12,
		10, 12, 11, 12, 17, 12, 16, 12,
		15, 12, 13, 16, 13, 15, 13, 14,
		14, 14, 15, 14, 12, 14, 11, 14,
		6, 12, 7, 12, 7, 13, 7, 14, 20,
		12, 19, 12, 19, 13, 19, 14, 17,
		14, 17, 15, 15, 16, 16, 16, 17,
		16, 18, 16, 19, 16, 20, 16, 9,
		14, 9, 15, 11, 16, 10, 16, 9,
		16, 8, 16, 7, 16, 6, 16, 21,
		14, 5, 14, 17, 10, 17, 9, 9,
		10, 9, 9, 17, 7, 17, 6, 17,
		5, 16, 5, 15, 5, 17, 4, 17,
		3, 9, 7, 9, 6, 9, 5, 10, 5,
		11, 5, 9, 4, 9, 3, 13, 5,
		13, 4, 13, 3, 14, 3, 15, 3,
		12, 3, 11, 3, 7, 3, 6, 3,
		19, 3, 20, 3, 7, 1, 6, 1,
		19, 1, 20, 1, 17, 1, 9, 1,
		16, 1, 10, 1, 15, 1, 11, 1,
		13, 1, 13, 0,
		
		5, 10,
		6, 10,
		7, 10,
		7, 9,
		7, 8,
		7, 7,
		7, 6,
		7, 5, 
		5, 5,
		6, 5,

		21, 10,
		20, 10, 
		19, 10,
		19, 9,
		19, 8,
		19, 7, 
		19, 6,
		19, 5,
		21, 5,
		20, 5,

		11, 8, 
		12, 8,
		13, 8,
		14, 8, 
		15, 8,
		15, 7,
		14, 7,
		11, 7,
		12, 7
	};

	for(int i = 0; i < 232; i+=2)
	{
		int x = coord[i] - 5;
		int z = coord[i+1];
		addBlock(x, z);
		std::cout << "Block: " << x << ", " << z << std::endl;
	}
	std::cout << "Finished" << std::endl;
}

void CavePacman::loadOrbs()
{
	//line 1
	addDefaultOrb(0, 0);
	addDefaultOrb(1, 0);
	addDefaultOrb(2, 0);
	addDefaultOrb(3, 0);
	addDefaultOrb(4, 0);
	addDefaultOrb(5, 0);
	addDefaultOrb(6, 0);
	addDefaultOrb(7, 0);
	addDefaultOrb(9, 0);
	addDefaultOrb(10, 0);
	addDefaultOrb(11, 0);
	addDefaultOrb(12, 0);
	addDefaultOrb(13, 0);
	addDefaultOrb(14, 0);
	addDefaultOrb(15, 0);
	addDefaultOrb(16, 0);

	//line 2
	addSuperOrb(0, 1);
	addDefaultOrb(3, 1);
	addDefaultOrb(7, 1);
	addDefaultOrb(9, 1);
	addDefaultOrb(13, 1);
	addSuperOrb(16, 1);

	//line 3
	addDefaultOrb(0, 2);
	addDefaultOrb(1, 2);
	addDefaultOrb(2, 2);
	addDefaultOrb(3, 2);
	addDefaultOrb(4, 2);
	addDefaultOrb(5, 2);
	addDefaultOrb(6, 2);
	addDefaultOrb(7, 2);
	addDefaultOrb(8, 2);
	addDefaultOrb(9, 2);
	addDefaultOrb(10, 2);
	addDefaultOrb(11, 2);
	addDefaultOrb(12, 2);
	addDefaultOrb(13, 2);
	addDefaultOrb(14, 2);
	addDefaultOrb(15, 2);
	addDefaultOrb(16, 2);

	//line 4
	addDefaultOrb(0, 3);
	addDefaultOrb(3, 3);
	addDefaultOrb(5, 3);
	addDefaultOrb(11, 3);
	addDefaultOrb(13, 3);
	addDefaultOrb(16, 3);

	//line 5
	addDefaultOrb(0, 4);
	addDefaultOrb(1, 4);
	addDefaultOrb(2, 4);
	addDefaultOrb(3, 4);
	addDefaultOrb(5, 4);
	addDefaultOrb(6, 4);
	addDefaultOrb(7, 4);
	addDefaultOrb(9, 4);
	addDefaultOrb(10, 4);
	addDefaultOrb(11, 4);
	addDefaultOrb(13, 4);
	addDefaultOrb(14, 4);
	addDefaultOrb(15, 4);
	addDefaultOrb(16, 4);

	//line 6
	addDefaultOrb(3, 5);
	addDefaultOrb(7, 5);
	addDefaultOrb(9, 5);
	addDefaultOrb(13, 5);

	//line 7
	addDefaultOrb(3, 6);
	addDefaultOrb(5, 6);
	addDefaultOrb(6, 6);
	addDefaultOrb(7, 6);
	addDefaultOrb(8, 6);
	addDefaultOrb(9, 6);
	addDefaultOrb(10, 6);
	addDefaultOrb(11, 6);
	addDefaultOrb(13, 6);

	//line 8
	addDefaultOrb(3, 7);
	addDefaultOrb(5, 7);
	addDefaultOrb(11, 7);
	addDefaultOrb(13, 7);

	//line 9
	addDefaultOrb(3, 8);
	addDefaultOrb(4, 8);
	addDefaultOrb(5, 8);
	addDefaultOrb(11, 8);
	addDefaultOrb(12, 8);
	addDefaultOrb(13, 8);

	//line 10
	addDefaultOrb(3, 9);
	addDefaultOrb(5, 9);
	addDefaultOrb(6, 9);
	addDefaultOrb(7, 9);
	addDefaultOrb(8, 9);
	addDefaultOrb(9, 9);
	addDefaultOrb(10, 9);
	addDefaultOrb(11, 9);
	addDefaultOrb(13, 9);

	//line 11
	addDefaultOrb(3, 10);
	addDefaultOrb(5, 10);
	addDefaultOrb(11, 10);
	addDefaultOrb(13, 10);

	//line 12
	addDefaultOrb(0, 11);
	addDefaultOrb(1, 11);
	addDefaultOrb(2, 11);
	addDefaultOrb(3, 11);
	addDefaultOrb(4, 11);
	addDefaultOrb(5, 11);
	addDefaultOrb(6, 11);
	addDefaultOrb(7, 11);
	addDefaultOrb(9, 11);
	addDefaultOrb(10, 11);
	addDefaultOrb(11, 11);
	addDefaultOrb(12, 11);
	addDefaultOrb(13, 11);
	addDefaultOrb(14, 11);
	addDefaultOrb(15, 11);
	addDefaultOrb(16, 11);

	//line 13
	addDefaultOrb(0, 12);
	addDefaultOrb(3, 12);
	addDefaultOrb(7, 12);
	addDefaultOrb(9, 12);
	addDefaultOrb(13, 12);
	addDefaultOrb(16, 12);

	//line 14
	addSuperOrb(0, 13);
	addDefaultOrb(1, 13);
	addDefaultOrb(3, 13);
	addDefaultOrb(4, 13);
	addDefaultOrb(5, 13);
	addDefaultOrb(6, 13);
	addDefaultOrb(7, 13);
	addDefaultOrb(8, 13);
	addDefaultOrb(9, 13);
	addDefaultOrb(10, 13);
	addDefaultOrb(11, 13);
	addDefaultOrb(12, 13);
	addDefaultOrb(13, 13);
	addDefaultOrb(15, 13);
	addSuperOrb(16, 13);

	//line 15
	addDefaultOrb(1, 14);
	addDefaultOrb(3, 14);
	addDefaultOrb(5, 14);
	addDefaultOrb(11, 14);
	addDefaultOrb(13, 14);
	addDefaultOrb(15, 14);

	//line 16
	addDefaultOrb(0, 15);
	addDefaultOrb(1, 15);
	addDefaultOrb(2, 15);
	addDefaultOrb(3, 15);
	addDefaultOrb(5, 15);
	addDefaultOrb(6, 15);
	addDefaultOrb(7, 15);
	addDefaultOrb(9, 15);
	addDefaultOrb(10, 15);
	addDefaultOrb(11, 15);
	addDefaultOrb(13, 15);
	addDefaultOrb(14, 15);
	addDefaultOrb(15, 15);
	addDefaultOrb(16, 15);

	//line 17
	addDefaultOrb(0, 16);
	addDefaultOrb(7, 16);
	addDefaultOrb(9, 16);
	addDefaultOrb(16, 16);

	//line 18
	addDefaultOrb(0, 17);
	addDefaultOrb(1, 17);
	addDefaultOrb(2, 17);
	addDefaultOrb(3, 17);
	addDefaultOrb(4, 17);
	addDefaultOrb(5, 17);
	addDefaultOrb(6, 17);
	addDefaultOrb(7, 17);
	addDefaultOrb(8, 17);
	addDefaultOrb(9, 17);
	addDefaultOrb(10, 17);
	addDefaultOrb(11, 17);
	addDefaultOrb(12, 17);
	addDefaultOrb(13, 17);
	addDefaultOrb(14, 17);
	addDefaultOrb(15, 17);
	addDefaultOrb(16, 17);
}


void CavePacman::loadWayPoints()
{
	//from top left to bottom right
	//x y up down left right id
	//line 1
	wayPoints.push_back(new WayPoint(0,0,false, true, false,true));
	wayPoints.push_back(new WayPoint(30,0,false, true, true,true));
	wayPoints.push_back(new WayPoint(70,0,false, true, true,false));
	wayPoints.push_back(new WayPoint(90,0,false, true, false,true));
	wayPoints.push_back(new WayPoint(130,0,false, true, true,true));
	wayPoints.push_back(new WayPoint(160,0,false, true, true,false));

	//line 3
	wayPoints.push_back(new WayPoint(0,20,true, true, false,true));
	wayPoints.push_back(new WayPoint(30,20,true, true, true,true));
	wayPoints.push_back(new WayPoint(50,20,false, true, true,true));
	wayPoints.push_back(new WayPoint(70,20,true, false, true,true));
	wayPoints.push_back(new WayPoint(90,20,true, false, true,true));
	wayPoints.push_back(new WayPoint(110,20,false, true, true,true));
	wayPoints.push_back(new WayPoint(130,20,true, true, true,true));
	wayPoints.push_back(new WayPoint(160,20,true, true, true,false));

	//line 5
	wayPoints.push_back(new WayPoint(0,40,true, false, false,true));
	wayPoints.push_back(new WayPoint(30,40,true, true, true,false));
	wayPoints.push_back(new WayPoint(50,40,true, false, false,true));
	wayPoints.push_back(new WayPoint(70,40,false, true, true,false));
	wayPoints.push_back(new WayPoint(90,40,false, true, false,true));
	wayPoints.push_back(new WayPoint(110,40,true, false, true,false));
	wayPoints.push_back(new WayPoint(130,40,true, true, false,true));
	wayPoints.push_back(new WayPoint(160,40,true, false, true,false));

	//line 7
	wayPoints.push_back(new WayPoint(50,60,false, true, false,true));
	wayPoints.push_back(new WayPoint(70,60,true, false, true,true));
	wayPoints.push_back(new WayPoint(80,60,false, false, true,true));
	wayPoints.push_back(new WayPoint(90,60,true, false, true,true));
	wayPoints.push_back(new WayPoint(110,60,false, true, true,false));

	//line 9
	wayPoints.push_back(new WayPoint(30,80,true, true, false,true));
	wayPoints.push_back(new WayPoint(50,80,true, true, true,false));
	wayPoints.push_back(new WayPoint(110,80,true, true, false,true));
	wayPoints.push_back(new WayPoint(130,80,true, true, true,false));
	
	//line 10
	wayPoints.push_back(new WayPoint(50,90,true, true, false,true));
	wayPoints.push_back(new WayPoint(110,90,true, true, true,false));

	//line 12
	wayPoints.push_back(new WayPoint(0,110,false, true, false,true));
	wayPoints.push_back(new WayPoint(30,110,true, true, true,true));
	wayPoints.push_back(new WayPoint(50,110,true, false, true,true));
	wayPoints.push_back(new WayPoint(70,110,false, true, true,false));
	wayPoints.push_back(new WayPoint(90,110,false, true, false,true));
	wayPoints.push_back(new WayPoint(110,110,true, false, true,true));
	wayPoints.push_back(new WayPoint(130,110,true, true, true,true));
	wayPoints.push_back(new WayPoint(160,110,false, true, true,false));

	//line 14
	wayPoints.push_back(new WayPoint(0,130,true, false, false,true));
	wayPoints.push_back(new WayPoint(10,130,false, true, true,false));
	wayPoints.push_back(new WayPoint(30,130,true, true, false,true));
	wayPoints.push_back(new WayPoint(50,130,false, true, true,true));
	wayPoints.push_back(new WayPoint(70,130,true, false, true,true));
	wayPoints.push_back(new WayPoint(90,130,true, false, true,true));
	wayPoints.push_back(new WayPoint(110,130,false, true, true,true));
	wayPoints.push_back(new WayPoint(130,130,true, true, true,false));
	wayPoints.push_back(new WayPoint(150,130,false, true, false,true));
	wayPoints.push_back(new WayPoint(160,130,true, false, true,false));

	//line 16
	wayPoints.push_back(new WayPoint(0,150,false, true, false,true));
	wayPoints.push_back(new WayPoint(10,150,true, false, true,true));
	wayPoints.push_back(new WayPoint(30,150,true, false, true,false));
	wayPoints.push_back(new WayPoint(50,150,true, false, false,true));
	wayPoints.push_back(new WayPoint(70,150,false, true, true,false));
	wayPoints.push_back(new WayPoint(90,150,false, true, false,true));
	wayPoints.push_back(new WayPoint(110,150,true, false, true,false));
	wayPoints.push_back(new WayPoint(130,150,true, false, false,true));
	wayPoints.push_back(new WayPoint(150,150,true, false, true,true));
	wayPoints.push_back(new WayPoint(160,150,false, true, true,false));

	//line 18
	wayPoints.push_back(new WayPoint(0,170,true, false, false,true));
	wayPoints.push_back(new WayPoint(70,170,true, false, true,true));
	wayPoints.push_back(new WayPoint(90,170,true, false, true,true));
	wayPoints.push_back(new WayPoint(160,170,true, false, true,false));
}

void CavePacman::addBlock(int x, int z)
{
	grid[x][z] = true;
	sprites[x][z] = new Block(x, z);
	coordinates.push_back(new Coordinate(x, z));
}

void CavePacman::addDefaultOrb(int x, int z)
{
	grid[x][z] = true;
	sprites[x][z] = new DefaultOrb(x, z);
	coordinates.push_back(new Coordinate(x, z));
}

void CavePacman::addSuperOrb(int x, int z)
{
	grid[x][z] = true;
	sprites[x][z] = new SuperOrb(x, z);
	coordinates.push_back(new Coordinate(x, z));
}

void CavePacman::clearLocation(int x, int z)
{
	grid[x][z] = false;
	sprites[x][z] = NULL;
	int index = 0;
	for(int i = 0; i < coordinates.size(); i++)
	{
		if(coordinates[i]->x==x && coordinates[i]->z==z)
		{
			index = i;
			break;
		}
	}
	coordinates.erase(coordinates.begin()+index);
}

void CavePacman::contextInit()
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	Ghost* ghost = new Ghost(8, 7, 1);
	Ghost* ghost2 = new Ghost(8, 7, 2);
	Ghost* ghost3 = new Ghost(8, 7, 3);
	Ghost* ghost4 = new Ghost(8, 7, 4);
	ghosts.push_back(ghost);
	ghosts.push_back(ghost2);
	ghosts.push_back(ghost3);
	ghosts.push_back(ghost4);
}

gmtl::Vec4f CavePacman::collisionLinePlane(gmtl::Vec3f A, gmtl::Vec3f B, gmtl::Planef plane)
{
    gmtl::Vec3f AB = A - B;
    float denominator = gmtl::dot(AB, plane.getNormal());
    if(denominator == 0)
    	return gmtl::Vec4f(0,0,0, -1);
    float numerator = gmtl::dot(A, plane.getNormal()) + plane.getOffset();

    float t = - numerator / denominator;
    gmtl::normalize(AB);
    gmtl::Vec3f point = A + t*AB;
    return gmtl::Vec4f(point[0], point[1], point[2], t); 
}



void CavePacman::preFrame()
{
	//Sleep(100);
	checkInput();
	updateMovement();
	pacman->update();
	updateGhosts();
	
	frames++;
	if(frames==10000)
	{
		frames = 0;
	}
}

void CavePacman::checkInput()
{
	if(useWand==true)
	{
		checkWand();
	}
	else
	{
		checkKeyboard();
	}
}

void CavePacman::checkWand()
{
	wand->updateData();
	gmtl::Matrix44f wandMatrix = wand->getData();
	wandOrigin = wandMatrix * gmtl::Vec4f(0,0,0,1);
	wandForward = wandMatrix * gmtl::Vec4f(0,0,1,1);
	int currentDirection = pacman->getDirection();
	//Wall forward
	gmtl::Planef planeForward(gmtl::Vec3f(0,0,-1), -5);
	wallPointForward = collisionLinePlane(gmtl::Vec3f(wandOrigin[0], wandOrigin[1], wandOrigin[2]),
	gmtl::Vec3f(wandForward[0], wandForward[1], wandForward[2]), planeForward);
	if(wallPointForward[0] >= -5.0f && wallPointForward[0] <= 5.0f)
	{
		currentWallNr = 1;
		if(wallPointForward[1] > 5.0f)
		{
			std::cout << "WALL UP" << std::endl;
			pacman->jump();
			sounds[4].Play();
		}
		else if(wallPointForward[1] < -5.0f)
		{
			std::cout << "WALL DOWN" << std::endl;
			//Turn Back
			switch(currentDirection)
			{
				case LEFT: direction = RIGHT; break;
				case RIGHT: direction = LEFT; break;
				case UP: direction = DOWN; break;
				case DOWN: direction = UP; break;
			}
		}
		else
		{
			std::cout << "WALL FORWARD" << std::endl;
			//Go forward
			//Direction is up so keep current direction
			direction = currentDirection;
		}
	}
	else
	{
		if(wandForward[0] < 0.0f)
		{
			//Wall left
			gmtl::Planef planeLeft(gmtl::Vec3f(-1,0,0), -5);
			wallPointLeft = collisionLinePlane(gmtl::Vec3f(wandOrigin[0], wandOrigin[1], wandOrigin[2]),
			gmtl::Vec3f(wandForward[0], wandForward[1], wandForward[2]), planeLeft);
			if(wallPointLeft[2] >= -5.0f && wallPointLeft[2] <= 5.0f && wallPointLeft[0] < 0.0f)
			{
				currentWallNr = 0;
				std::cout << "WALL LEFT" << std::endl;
				//Turn LEFT
				switch(currentDirection)
				{
					case LEFT: direction = DOWN; break;
					case RIGHT: direction = UP; break;
					case UP: direction = LEFT; break;
					case DOWN: direction = RIGHT; break;
				}
			}
			else
			{
				//No collision with wall
				currentWallNr = -1;
			}
		}
		else
		{
			//Wall right
			gmtl::Planef planeRight(gmtl::Vec3f(1,0,0), -5);
			wallPointRight = collisionLinePlane(gmtl::Vec3f(wandOrigin[0], wandOrigin[1], wandOrigin[2]),
			gmtl::Vec3f(wandForward[0], wandForward[1], wandForward[2]), planeRight);
			if(wallPointRight[2] >= -5.0f && wallPointRight[2] <= 5.0f && wallPointRight[0] > 0.0f)
			{
				currentWallNr = 2;
				std::cout << "WALL RIGHT" << std::endl;
				//Turn Right
				switch(currentDirection)
				{
					case LEFT: direction = UP; break;
					case RIGHT: direction = DOWN; break;
					case UP: direction = RIGHT; break;
					case DOWN: direction = LEFT; break;
				}
			}
			else
			{
				//No collision with wall
				currentWallNr = -1;
			}
		}
	}
}

void CavePacman::checkKeyboard()
{
		//For Testing, keyboard events
	//Check key events every 5 frames
	if(frames%5==0)
	{
		int currentDirection = pacman->getDirection();
		//Check W
		if(GetAsyncKeyState(87)!=0)
		{
			//std::cout << "UP" << std::endl;
			//direction = UP;
			//Go forward
			//Direction is up so keep current direction
			direction = currentDirection;
		}
		//Check A
		else if(GetAsyncKeyState(65)!=0)
		{
			//std::cout << "LEFT" << std::endl;
			//direction = LEFT;
			//Turn LEFT
			switch(currentDirection)
			{
				case LEFT: direction = DOWN; break;
				case RIGHT: direction = UP; break;
				case UP: direction = LEFT; break;
				case DOWN: direction = RIGHT; break;
			}
		}
		//Check D
		else if(GetAsyncKeyState(68)!=0)
		{
			//std::cout << "RIGHT" << std::endl;
			//direction = RIGHT;
			//Turn Right
			switch(currentDirection)
			{
				case LEFT: direction = UP; break;
				case RIGHT: direction = DOWN; break;
				case UP: direction = RIGHT; break;
				case DOWN: direction = LEFT; break;
			}
		}
		//Check S
		else if(GetAsyncKeyState(83)!=0)
		{
			//std::cout << "DOWN" << std::endl;
			//direction = DOWN;
			//Turn Back
			switch(currentDirection)
			{
				case LEFT: direction = RIGHT; break;
				case RIGHT: direction = LEFT; break;
				case UP: direction = DOWN; break;
				case DOWN: direction = UP; break;
			}
		}
		else
		{
			//direction = 0;
		}
	}
	//Check J
	if(GetAsyncKeyState(74)!=0)
	{
		pacman->jump();
		sounds[4].Play();
	}
}

void CavePacman::updateMovement()
{
	//True, when user has to make choose a other direction than forward
	bool freeze = false;

	bool checkWayPoints = false;
	int x2 = 0;
	int z2 = 0;
	float modX = fmodf(pacman->getX(), 10.0f);
	float modZ = fmodf(pacman->getZ(), 10.0f);
	//std::cout << "X: " << modX << std::endl;
	//std::cout << "Z: " <<  modZ << std::endl;
	if(modX >= 9.9f || modX <= 0.1f)
	{
		if(modX >= 9.9f)
		{
			x2 = (int)(pacman->getX()-modX+10.0f);
		}
		else
		{
			x2 = (int)(pacman->getX()-modX);
		}
		if(modZ >= 9.9f || modZ <= 0.1f)
		{
			if(modZ >= 9.9f)
			{
				z2 = (int)(pacman->getZ()-modZ+10.0f);
			}
			else
			{
				z2 = (int)(pacman->getZ()-modZ);
			}
			checkWayPoints = true;
		}
	}
	if(checkWayPoints==true)
	{
		//std::cout << "MOVE: " << x2 << ", " << z2 << std::endl;
		pacman->setX(x2);
		pacman->setZ(z2);

		for(int w = 0; w < wayPoints.size(); w++)
		{
			if(x2 == wayPoints[w]->getX() && z2 == wayPoints[w]->getZ())
			{
				if(wayPoints[w]->canGo(direction)==true)
				{
					pacman->setDirection(direction);
				}
				else if(wayPoints[w]->getAmountOfChoices()==2)
				{
					//Automatically make choice
					direction = wayPoints[w]->getNewDirection(pacman->getDirection());
					pacman->setDirection(direction);
				}
				else
				{
					//std::cout << "FREEZE: " << x2 << ", " << z2 << std::endl;
					freeze = true;
				}
				//std::cout << "CHANGE DIRECTION: " << direction << std::endl;

				break;
			}
		}
	}
	else if(pacman->isRotating()==false)
	{
		//Always be able to turn back
		int currentDirection = pacman->getDirection();
		if(currentDirection==LEFT && direction==RIGHT)
		{
			pacman->setDirection(RIGHT);
		}
		else if(currentDirection==RIGHT && direction==LEFT)
		{
			pacman->setDirection(LEFT);
		}
		else if(currentDirection==UP && direction==DOWN)
		{
			pacman->setDirection(DOWN);
		}
		else if(currentDirection==DOWN && direction==UP)
		{
			pacman->setDirection(UP);
		}
	}
	if(freeze==false)
	{
		//General movement
		int currentDirection = pacman->getDirection();
		//std::cout << "CURRENT DIRECTION: " << currentDirection << std::endl;
		int x = pacman->getXGrid();
		int z = pacman->getZGrid();
		int xGrid = x;
		int zGrid = z;
		if(xGrid >= 0 && xGrid < 17 && zGrid >= 0 && zGrid < 18)
		{
			if(grid[xGrid][zGrid]==false)
			{
				switch(currentDirection)
				{
					case LEFT: pacman->moveX(-0.2f); break;
					case RIGHT: pacman->moveX(0.2f); break;
					case UP: pacman->moveZ(-0.2f); break;
					case DOWN: pacman->moveZ(0.2f); break;
				}
			}
			else
			{
				//Check object
				Sprite* sprite = sprites[xGrid][zGrid];
				if(sprite->getType()!=sprite->BLOCK)
				{
					switch(currentDirection)
					{
						case LEFT: pacman->moveX(-0.2f); break;
						case RIGHT: pacman->moveX(0.2f); break;
						case UP: pacman->moveZ(-0.2f); break;
						case DOWN: pacman->moveZ(0.2f); break;
					}
					//Check collision
					if(((Orb*)sprite)->intersects(pacman->getX()+3.33f, pacman->getZ()+3.33f))
					{
						clearLocation(xGrid, zGrid);
						sounds[1].Play();
					}
				}
			}
		}
		else
		{
			//direction = 0;
		}
		if(pacman->getX() < 0.0f)
		{
			pacman->setX(0.0f);
		}
		if(pacman->getZ() < 0.0f)
		{
			pacman->setZ(0.0f);
		}
	}
}

void CavePacman::updateGhosts()
{
	for(int i = 0; i < ghosts.size(); i++)
	{
		Ghost* ghost = ghosts[i];
		ghost->update();	
		bool checkWayPoints = false;
		int x2 = 0;
		int z2 = 0;
		float modX = fmodf(ghost->getX()+5, 10.0f);
		float modZ = fmodf(ghost->getZ()+5, 10.0f);

		if(modX >= 9.9f || modX <= 0.1f)
		{
			//std::cout << "X: " << ((int)(ghost->getX()+5)) << std::endl;
			if(modX >= 9.9f)
			{
				x2 = (int)((ghost->getX()+5)-modX+10.0f);
			}
			else
			{
				x2 = (int)((ghost->getX()+5)-modX);
			}
			//std::cout << "X2: " << x2 << std::endl;
			if(modZ >= 9.9f || modZ <= 0.1f)
			{
				//std::cout << "Z: " << ((int)(ghost->getZ()+5)) << std::endl;
				if(modZ >= 9.9f)
				{
					z2 = (int)((ghost->getZ()+5)-modZ+10.0f);
				}
				else
				{
					z2 = (int)((ghost->getZ()+5)-modZ);
				}
				//std::cout << "Z2: " << z2 << std::endl;
				checkWayPoints = true;
			}
		}
		if(checkWayPoints==true)
		{
			ghost->setX(x2-5);
			ghost->setZ(z2-5);

			for(int w = 0; w < wayPoints.size(); w++)
			{
				if(x2 == wayPoints[w]->getX() && z2 == wayPoints[w]->getZ())
				{
					//std::cout << "Old Direction: " << ghost->getDirection() << std::endl;
					int newDirection = wayPoints[w]->getNewDirection(ghost->getDirection());
					//std::cout << "New Direction: " << newDirection << std::endl;
					ghost->setDirection(newDirection);
					break;
				}
			}
		}
	}
}

void CavePacman::bufferPreDraw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CavePacman::draw()
{
	glEnable (GL_DEPTH_TEST);
    

	//Move environment
	glPushMatrix();
	glRotatef(pacman->getRotation(), 0.0f, 1.0f, 0.0f);
	glTranslatef(-pacman->getX(), -pacman->getY(), -pacman->getZ());
	

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->tid());

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
	GLfloat lightpos[] = {1.0f, 1.0f, 1.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glEnable (GL_COLOR_MATERIAL);
    glShadeModel (GL_SMOOTH);

	//Draw objects
	for(int i = 0; i < coordinates.size(); i++)
	{
		Coordinate* c = coordinates[i];
		sprites[c->x][c->z]->draw();
	}
	glDisable (GL_LIGHTING);
    glDisable (GL_LIGHT0);
	glDisable (GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);

	for(int i = 0; i < ghosts.size(); i++)
	{
		ghosts[i]->draw();
	}

	//Test
	int xGrid = pacman->getXGrid();
	int zGrid = pacman->getZGrid();
	glColor3f(1.0f, 0.0f, 0.0f);
	draw3DRectangle(-5.0f+(xGrid*10.0f), -5.0f, -5.0f+(zGrid*10.0f), 10.0f, 0.3f, 10.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	if(xGrid+1 >= 0 && xGrid+1 < 17 && zGrid >= 0 && zGrid < 18 && grid[xGrid+1][zGrid]==false)
	{
		draw3DRectangle(-5.0f+((xGrid+1)*10.0f), -5.0f, -5.0f+(zGrid*10.0f), 10.0f, 0.1f, 10.0f);
	}
	if(xGrid-1 >= 0 && xGrid-1 < 17 && zGrid >= 0 && zGrid < 18 && grid[xGrid-1][zGrid]==false)
	{
		draw3DRectangle(-5.0f+((xGrid-1)*10.0f), -5.0f, -5.0f+(zGrid*10.0f), 10.0f, 0.1f, 10.0f);
	}
	if(xGrid >= 0 && xGrid < 17 && zGrid+1 >= 0 && zGrid+1 < 18 && grid[xGrid][zGrid+1]==false)
	{
		draw3DRectangle(-5.0f+(xGrid*10.0f), -5.0f, -5.0f+((zGrid+1)*10.0f), 10.0f, 0.1f, 10.0f);
	}
	if(xGrid >= 0 && xGrid < 17 && zGrid-1 >= 0 && zGrid-1 < 18 && grid[xGrid][zGrid-1]==false)
	{
		draw3DRectangle(-5.0f+(xGrid*10.0f), -5.0f, -5.0f+((zGrid-1)*10.0f), 10.0f, 0.1f, 10.0f);
	}

	//Debug Waypoints
	glColor3f(1.0f, 0.0f, 1.0f);
	for(int i = 0; i < wayPoints.size(); i++)
	{
		float x = wayPoints[i]->getX();
		float z = wayPoints[i]->getZ();
		draw3DRectangle(-5+x, -5, -5+z, 10.0f, 0.2f, 10.0f);
	}

	//Draw border
	draw3DRectangleWithoutTop(-5, -5, -5, 170, 10, 180);

	//Move to old location
	glPopMatrix();

	glColor3f(1.0f, 0.0f, 0.0f);
	switch(currentWallNr)
	{
		case 0: draw3DRectangle(wallPointLeft[0]-0.05f, wallPointLeft[1]-0.05f, wallPointLeft[2]-0.05f, 0.1f, 0.1f, 0.1f); break;
		case 1: draw3DRectangle(wallPointForward[0]-0.05f, wallPointForward[1]-0.05f, wallPointForward[2]-0.05f, 0.1f, 0.1f, 0.1f); break;
		case 2: draw3DRectangle(wallPointRight[0]-0.05f, wallPointRight[1]-0.05f, wallPointRight[2]-0.05f, 0.1f, 0.1f, 0.1f); break;
	}
}

void CavePacman:: draw3DRectangle(const float x1, const float y1, const float z1, const float w1, const float h1, const float d1)
{
	glNormal3d(0, 0, 1);
	glBegin(GL_QUADS);
	//back
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y1+h1, z1);
	glVertex3f(x1+w1, y1+h1, z1);
	glVertex3f(x1+w1, y1, z1);
	//front
	glVertex3f(x1, y1, z1+d1);
	glVertex3f(x1, y1+h1, z1+d1);
	glVertex3f(x1+w1, y1+h1, z1+d1);
	glVertex3f(x1+w1, y1, z1+d1);
	//down
	glVertex3f(x1, y1, z1+d1);
	glVertex3f(x1+w1, y1, z1+d1);
	glVertex3f(x1+w1, y1, z1);
	glVertex3f(x1, y1, z1);
	//up
	glVertex3f(x1, y1+h1, z1+d1);
	glVertex3f(x1+w1, y1+h1, z1+d1);
	glVertex3f(x1+w1, y1+h1, z1);
	glVertex3f(x1, y1+h1, z1);
	//left
	glVertex3f(x1, y1, z1+d1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y1+h1, z1);
	glVertex3f(x1, y1+h1, z1+d1);
	//right
	glVertex3f(x1+w1, y1, z1+d1);
	glVertex3f(x1+w1, y1, z1);
	glVertex3f(x1+w1, y1+h1, z1);
	glVertex3f(x1+w1, y1+h1, z1+d1);
	glEnd();
}

void CavePacman:: draw3DRectangleWithoutTop(const float x1, const float y1, const float z1, const float w1, const float h1, const float d1)
{
	glNormal3d(0, 0, 1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	//back
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y1+h1, z1);
	glVertex3f(x1+w1, y1+h1, z1);
	glVertex3f(x1+w1, y1, z1);
	//front
	glVertex3f(x1, y1, z1+d1);
	glVertex3f(x1, y1+h1, z1+d1);
	glVertex3f(x1+w1, y1+h1, z1+d1);
	glVertex3f(x1+w1, y1, z1+d1);
	//down
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(x1, y1, z1+d1);
	glVertex3f(x1+w1, y1, z1+d1);
	glVertex3f(x1+w1, y1, z1);
	glVertex3f(x1, y1, z1);
	glColor3f(0.0f, 1.0f, 0.0f);
	//up
	//glVertex3f(x1, y1+h1, z1+d1);
	//glVertex3f(x1+w1, y1+h1, z1+d1);
	//glVertex3f(x1+w1, y1+h1, z1);
	//glVertex3f(x1, y1+h1, z1);
	//left
	glVertex3f(x1, y1, z1+d1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y1+h1, z1);
	glVertex3f(x1, y1+h1, z1+d1);
	//right
	glVertex3f(x1+w1, y1, z1+d1);
	glVertex3f(x1+w1, y1, z1);
	glVertex3f(x1+w1, y1+h1, z1);
	glVertex3f(x1+w1, y1+h1, z1+d1);
	glEnd();
}

