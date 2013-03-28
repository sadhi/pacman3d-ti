#include <GL/glew.h>
#include "CavePacman.h"
#include <CaveLib/texture.h>
#include <cavelib/model.h>
#include <cavelib/Shader.h>

#include <fstream>
#include <iostream>

const int LEFT = 300, RIGHT = 301, UP = 302, DOWN = 303;

CavePacman::CavePacman(void)
{
}

CavePacman::~CavePacman(void)
{

}

void CavePacman::init()
{
	wand.init("VJWand");
	keyboard.init("VJKeyboard");
	TextureLoadOptions* t = new TextureLoadOptions();
	t->sampler = TextureLoadOptions::CLOSEST;
	texture = CaveLib::loadTexture("Images/grid.jpg", t);

	direction = 0;
	pacman = new Pacman(130.0f, 130.0f);
	for(int x = 0; x < 17; x++)
	{
		for(int z = 0; z < 18; z++)
		{
			grid[x][z] = false;
		}
	}

	Json::Reader reader;
	std::ifstream pFile("data/models/lol/models.json__", std::ios_base::in);
	if(!reader.parse(pFile, models))
	{
		printf("Json Read Error: %s", reader.getFormatedErrorMessages().c_str());
	}

	//for(int z = 0; z < 10; z++)
	//{
	//	addBlock(0, z);
	//	addBlock(2, z);
	//}
	loadLevel();
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

	//Test
	addDefaultOrb(13, 11);
	addSuperOrb(13, 10);
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

	Ghost* ghost = new Ghost(13, 12);
	ghosts.push_back(ghost);
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
	checkInput();
	updateMovement();
	pacman->update();
	for(int i = 0; i < ghosts.size(); i++)
	{
		//ghosts[i]->move();
	}
	//Update blocks
	//updateTargets();

	//Check block hit
	//for(int i = 0; i < blocks.size(); i++)
	//{
	//	if(currentWallNr==0 && blocks[i].contains(wallPointLeft[0], wallPointLeft[1], wallPointLeft[2]))
	//	{
	//		std::cout << "HIT LEFT" << std::endl;
	//		blocks.erase(blocks.begin()+i);
	//		break;
	//	}
	//	else if(currentWallNr==1 && blocks[i].contains(wallPointForward[0], wallPointForward[1], wallPointForward[2]))
	//	{
	//		std::cout << "HIT FORWARD" << std::endl;
	//		blocks.erase(blocks.begin()+i);
	//		break;
	//	}
	//	else if(currentWallNr==2 && blocks[i].contains(wallPointRight[0], wallPointRight[1], wallPointRight[2]))
	//	{
	//		std::cout << "HIT RIGHT" << std::endl;
	//		blocks.erase(blocks.begin()+i);
	//		break;
	//	}
	//}
	
	frames++;
	if(frames==10000)
	{
		frames = 0;
	}
}

void CavePacman::checkInput()
{
	wand->updateData();
	gmtl::Matrix44f wandMatrix = wand->getData();
	wandOrigin = wandMatrix * gmtl::Vec4f(0,0,0,1);
	wandForward = wandMatrix * gmtl::Vec4f(0,0,1,1);

	//Wall forward
	gmtl::Planef planeForward(gmtl::Vec3f(0,0,-1), -5);
	wallPointForward = collisionLinePlane(gmtl::Vec3f(wandOrigin[0], wandOrigin[1], wandOrigin[2]),
	gmtl::Vec3f(wandForward[0], wandForward[1], wandForward[2]), planeForward);
	if(wallPointForward[0] >= -5.0f && wallPointForward[0] <= 5.0f)
	{
		currentWallNr = 1;
		//std::cout << "WALL FORWARD" << std::endl;
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
				//std::cout << "WALL LEFT" << std::endl;
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
				//std::cout << "WALL RIGHT" << std::endl;
			}
			else
			{
				//No collision with wall
				currentWallNr = -1;
			}
		}
	}

	//For Testing, keyboard events
	//Check key events every 30 frames
	if(frames%5==0)
	{
		//Check W
		if(GetAsyncKeyState(87)!=0)
		{
			//std::cout << "UP" << std::endl;
			direction = UP;
		}
		//Check A
		else if(GetAsyncKeyState(65)!=0)
		{
			//std::cout << "LEFT" << std::endl;
			direction = LEFT;
		}
		//Check D
		else if(GetAsyncKeyState(68)!=0)
		{
			//std::cout << "RIGHT" << std::endl;
			direction = RIGHT;
		}
		//Check S
		else if(GetAsyncKeyState(83)!=0)
		{
			//std::cout << "DOWN" << std::endl;
			direction = DOWN;
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
	}

	//Check K
	if(GetAsyncKeyState(75)!=0)
	{
		pacman->rotate(-5.0f);
	}
	//Check L
	else if(GetAsyncKeyState(76)!=0)
	{
		pacman->rotate(5.0f);
	}
}

void CavePacman::updateMovement()
{
	int x = pacman->getXGrid();
	int z = pacman->getZGrid();
	int xGrid = x;
	int zGrid = z;
	switch(direction)
	{
		case LEFT: xGrid = pacman->determineXGridLeft(-0.2f); break;
		case RIGHT: xGrid = pacman->determineXGridRight(0.2f); break;
		case UP: zGrid = pacman->determineZGridUp(-0.2f); break;
		case DOWN: zGrid = pacman->determineZGridDown(0.2f); break;
	}
	if(xGrid >= 0 && xGrid < 17 && zGrid >= 0 && zGrid < 18)
	{
		if(grid[xGrid][zGrid]==false)
		{
			switch(direction)
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
				switch(direction)
				{
					case LEFT: pacman->moveX(-0.2f); break;
					case RIGHT: pacman->moveX(0.2f); break;
					case UP: pacman->moveZ(-0.2f); break;
					case DOWN: pacman->moveZ(0.2f); break;
				}
				//Check collision
				if(((Orb*)sprite)->intersects(pacman->getX()+2.5f, pacman->getZ())+2.5f)
				{
					clearLocation(xGrid, zGrid);
				}
			}
		}
	}
	else
	{
		direction = 0;
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

void CavePacman::bufferPreDraw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void CavePacman::draw()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//glBegin(GL_LINES);
	//glColor3f(0.0f, 1.0f, 1.0f);
	//glVertex4f(wandOrigin[0], wandOrigin[1], wandOrigin[2], wandOrigin[3]);
	//glVertex4f(wandForward[0], wandForward[1], wandForward[2], wandForward[3]);
	//glEnd();

	//glColor3f(1.0f, 0.0f, 0.0f);
	//drawSphere(5.0f, 100, 100);

	//Move environment
	glPushMatrix();
	glRotatef(pacman->getRotation(), 0.0f, 1.0f, 0.0f);
	glTranslatef(-pacman->getX(), -pacman->getY(), -pacman->getZ());
	

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->tid());

	//glColor3f(0.0f, 0.0f, 1.0f);
	//drawTextured3DRectangle(wandOrigin[0]-0.05f, wandOrigin[1]-0.05f, wandOrigin[2]-0.05f, 0.1f, 0.1f, 0.1f);

	//glColor3f(0.0f, 0.0f, 1.0f);
	//drawTextured3DRectangle(wandForward[0]-0.05f, wandForward[1]-0.05f, wandForward[2]-0.05f, 0.1f, 0.1f, 0.1f);


	//glColor3f(1.0f, 0.0f, 0.0f);
	//switch(currentWallNr)
	//{
	//	case 0: draw3DRectangle(wallPointLeft[0]-0.05f, wallPointLeft[1]-0.05f, wallPointLeft[2]-0.05f, 0.1f, 0.1f, 0.1f); break;
	//	case 1: draw3DRectangle(wallPointForward[0]-0.05f, wallPointForward[1]-0.05f, wallPointForward[2]-0.05f, 0.1f, 0.1f, 0.1f); break;
	//	case 2: draw3DRectangle(wallPointRight[0]-0.05f, wallPointRight[1]-0.05f, wallPointRight[2]-0.05f, 0.1f, 0.1f, 0.1f); break;
	//}

	//Draw objects
	for(int i = 0; i < coordinates.size(); i++)
	{
		Coordinate* c = coordinates[i];
		sprites[c->x][c->z]->draw();
	}
	glDisable(GL_TEXTURE_2D);

	for(int i = 0; i < ghosts.size(); i++)
	{
		ghosts[i]->draw();
	}

	//Test
	int xGrid = pacman->getXGrid();
	int zGrid = pacman->getZGrid();
	glColor3f(1.0f, 0.0f, 0.0f);
	draw3DRectangle(-5.0f+(xGrid*10.0f), -5.0f, -5.0f+(zGrid*10.0f), 10.0f, 0.1f, 10.0f);
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

	//Draw border
	draw3DRectangleWithoutTop(-5, -5, -5, 170, 10, 180);

	//Move to old location
	glPopMatrix();
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

void CavePacman:: drawTextured3DRectangle(const float x1, const float y1, const float z1, const float w1, const float h1, const float d1)
{
	glNormal3d(0, 0, 1);
	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0,0); glVertex3f(x1, y1, z1);
	glTexCoord2f(0,1); glVertex3f(x1, y1+h1, z1);
	glTexCoord2f(1,1); glVertex3f(x1+w1, y1+h1, z1);
	glTexCoord2f(1,0); glVertex3f(x1+w1, y1, z1);
	//front
	glTexCoord2f(0,0); glVertex3f(x1, y1, z1+d1);
	glTexCoord2f(0,1); glVertex3f(x1, y1+h1, z1+d1);
	glTexCoord2f(1,1); glVertex3f(x1+w1, y1+h1, z1+d1);
	glTexCoord2f(1,0); glVertex3f(x1+w1, y1, z1+d1);
	//down
	glTexCoord2f(0,0); glVertex3f(x1, y1, z1+d1);
	glTexCoord2f(0,1); glVertex3f(x1+w1, y1, z1+d1);
	glTexCoord2f(1,1); glVertex3f(x1+w1, y1, z1);
	glTexCoord2f(1,0); glVertex3f(x1, y1, z1);
	//up
	glTexCoord2f(0,0); glVertex3f(x1, y1+h1, z1+d1);
	glTexCoord2f(0,1); glVertex3f(x1+w1, y1+h1, z1+d1);
	glTexCoord2f(1,1); glVertex3f(x1+w1, y1+h1, z1);
	glTexCoord2f(1,0); glVertex3f(x1, y1+h1, z1);
	//left
	glTexCoord2f(0,0); glVertex3f(x1, y1, z1+d1);
	glTexCoord2f(0,1); glVertex3f(x1, y1, z1);
	glTexCoord2f(1,1); glVertex3f(x1, y1+h1, z1);
	glTexCoord2f(1,0); glVertex3f(x1, y1+h1, z1+d1);
	//right
	glTexCoord2f(0,0); glVertex3f(x1+w1, y1, z1+d1);
	glTexCoord2f(0,1); glVertex3f(x1+w1, y1, z1);
	glTexCoord2f(1,1); glVertex3f(x1+w1, y1+h1, z1);
	glTexCoord2f(1,0); glVertex3f(x1+w1, y1+h1, z1+d1);
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

void CavePacman:: drawSphere(double r, int lats, int longs) 
{
	float M_PI = 3.14159265359f;
      int i, j;
      for(i = 0; i <= lats; i++) {
            double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
           double z0  = sin(lat0);
          double zr0 =  cos(lat0);
    
          double lat1 = M_PI * (-0.5 + (double) i / lats);
           double z1 = sin(lat1);
          double zr1 = cos(lat1);
    
          glBegin(GL_QUAD_STRIP);
           for(j = 0; j <= longs; j++) {
              double lng = 2 * M_PI * (double) (j - 1) / longs;
              double x = cos(lng);
               double y = sin(lng);
    
              glNormal3f(x * zr0, y * zr0, z0);
               glVertex3f(x * zr0, y * zr0, z0);
             glNormal3f(x * zr1, y * zr1, z1);
              glVertex3f(x * zr1, y * zr1, z1);
           }
           glEnd();
       }
}
