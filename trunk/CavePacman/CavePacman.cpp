#include <GL/glew.h>
#include "CavePacman.h"
#include <gl\GL.h>
#include "glut.h"
#include <CaveLib/texture.h>
#include <cavelib/model.h>
#include <cavelib/Shader.h>

#include <fstream>
#include <iostream>

const int LEFT = 300, RIGHT = 301, UP = 302, DOWN = 303;
//cavegame
float Gspeed=0.02, G1x=0, G1y=0, G2x=0, G2y=0, G3x=0, G3y=0, G4x=0, G4y=0;
int G1dir=0, G2dir=0, G3dir=0, G4dir=0;
int lastwpG1=0, lastwpG2=0, lastwpG3=0, lastwpG4=0;
int wpcount=0;

CavePacman::CavePacman(void)
{
}

CavePacman::~CavePacman(void)
{

}

void CavePacman::init()
{
	wand.init("VJWand");
	mLeftButton.init("VJButton0");
	mRightButton.init("VJButton1");
	keyboard.init("VJKeyboard");
	TextureLoadOptions* t = new TextureLoadOptions();
	t->sampler = TextureLoadOptions::CLOSEST;
	texture = CaveLib::loadTexture("Images/grid.jpg", t);

	direction = 0;
	pacman = new Pacman(130.0f, 130.0f);
	for(int x = 0; x < 24; x++)
	{
		for(int y = 0; y < 24; y++)
		{
			grid[x][y] = false;
		}
	}

	Json::Reader reader;
	std::ifstream pFile("data/models/lol/models.json__", std::ios_base::in);
	if(!reader.parse(pFile, models))
	{
		printf("Json Read Error: %s", reader.getFormatedErrorMessages().c_str());
	}
	rotate = 0;

	//for(int z = 0; z < 10; z++)
	//{
	//	addBlock(0, z);
	//	addBlock(2, z);
	//}
	loadLevel();
}

void CavePacman::placeWayPoints()
{
	//from top left to bottom right
	//x y up down left right id
	//line 1
	drawWaypoint(5,5,false, true, false,true, 1);
	drawWaypoint(35,5,false, true, true,true, 2);
	drawWaypoint(75,5,false, true, true,false, 3);
	drawWaypoint(95,5,false, true, false,true, 4);
	drawWaypoint(135,5,false, true, true,true, 5);
	drawWaypoint(165,5,false, true, false,true, 6);

	//line 3
	drawWaypoint(5,25,true, true, false,true, 7);
	drawWaypoint(35,25,true, true, true,true, 8);
	drawWaypoint(55,25,false, true, true,true, 9);
	drawWaypoint(75,25,true, false, true,true, 10);
	drawWaypoint(95,25,true, false, true,true, 11);
	drawWaypoint(115,25,false, true, true,true, 12);
	drawWaypoint(135,25,true, true, true,true, 13);
	drawWaypoint(165,25,true, true, true,false, 14);

	//line 5
	drawWaypoint(5,45,true, false, false,true, 15);
	drawWaypoint(35,45,true, true, true,false, 16);
	drawWaypoint(55,45,true, false, false,true, 17);
	drawWaypoint(75,45,false, true, true,false, 18);
	drawWaypoint(95,45,false, true, true,false, 19);
	drawWaypoint(115,45,true, false, true,false, 20);
	drawWaypoint(135,45,true, true, false,true, 21);
	drawWaypoint(165,45,true, false, true,false, 22);

	//line 7
	drawWaypoint(55,65,false, true, false,true, 23);
	drawWaypoint(75,65,true, false, true,true, 24);
	drawWaypoint(95,65,true, false, true,true, 25);
	drawWaypoint(115,65,false, true, true,false, 26);

	//line 9
	drawWaypoint(35,85,true, true, false,true, 27);
	drawWaypoint(55,85,true, true, true,false, 28);
	drawWaypoint(115,85,true, true, false,true, 29);
	drawWaypoint(135,85,true, true, true,false, 30);
	
	//line 10
	drawWaypoint(55,95,true, true, false,true, 31);
	drawWaypoint(115,95,true, true, true,false, 32);

	//line 12
	drawWaypoint(5,115,false, true, false,true, 33);
	drawWaypoint(35,115,true, true, true,true, 34);
	drawWaypoint(55,115,true, false, true,true, 35);
	drawWaypoint(75,115,false, true, true,false, 36);
	drawWaypoint(95,115,false, true, false,true, 37);
	drawWaypoint(115,115,true, false, true,true, 38);
	drawWaypoint(135,115,true, true, true,true, 39);
	drawWaypoint(165,115,false, true, true,false, 40);

	//line 14
	drawWaypoint(5,135,true, false, false,true, 41);
	drawWaypoint(15,135,false, true, true,false, 42);
	drawWaypoint(35,135,true, true, false,true, 43);
	drawWaypoint(55,135,false, true, true,true, 44);
	drawWaypoint(75,135,true, false, true,true, 45);
	drawWaypoint(95,135,true, false, true,true, 46);
	drawWaypoint(115,135,false, true, true,true, 47);
	drawWaypoint(135,135,true, true, true,false, 48);
	drawWaypoint(155,135,false, true, false,true, 49);
	drawWaypoint(165,135,true, false, true,false, 50);

	//line 16
	drawWaypoint(5,135,true, false, false,true, 41);
	drawWaypoint(15,135,false, true, true,false, 42);
	drawWaypoint(35,135,true, true, false,true, 43);
	drawWaypoint(55,135,false, true, true,true, 44);
	drawWaypoint(75,135,true, false, true,true, 45);
	drawWaypoint(95,135,true, false, true,true, 46);
	drawWaypoint(115,135,false, true, true,true, 47);
	drawWaypoint(135,135,true, true, true,false, 48);
	drawWaypoint(155,135,false, true, false,true, 49);
	drawWaypoint(165,135,true, false, true,false, 50);
}

void CavePacman::drawWaypoint(float Corx, float Cory, bool up, bool down, bool left, bool right, int WPnr)
{
	if(WPnr!=lastwpG1){
		CheckDir( Corx,  Cory, G1x, G1y,  up,  down,  left,  right, WPnr, 1);}
	if(WPnr!=lastwpG2){
		CheckDir( Corx,  Cory, G2x, G2y,  up,  down,  left,  right, WPnr, 2);}
	if(WPnr!=lastwpG3){
		CheckDir( Corx,  Cory, G3x, G3y,  up,  down,  left,  right, WPnr, 3);}
	if(WPnr!=lastwpG4){
		CheckDir( Corx,  Cory, G4x, G4y,  up,  down,  left,  right, WPnr, 4);}

	glPushMatrix();
	glTranslatef(Corx,0,Cory);
	glutSolidSphere(0.3,16,16);
	if(down){
		glutSolidCone(0.2,1.0,8,8);
	}
	if(up){
		glRotatef(180,0,1,0);
			glutSolidCone(0.2,1.0,8,8);
		glRotatef(-180,0,1,0);
	}
	if(right){
		glRotatef(90,0,1,0);
		glutSolidCone(0.15,1.0,8,8);
		glRotatef(-90,0,1,0);
	}
	if(left){
		glRotatef(270,0,1,0);
		glutSolidCone(0.15,1.0,8,8);
		glRotatef(-270,0,1,0);
	}
	glPopMatrix();
}

void CavePacman::CheckDir(float Corx, float Cory, float GX, float GY, bool up, bool down, bool left, bool right, int WPnr, int Gnr)
{
	if(
		sqrt(abs((Corx-GX)*(Corx-GX)) + abs((Cory-GY)*(Cory-GY)))<0.5 
		)
	{
		wpcount++;
		std::cout<<"["<<std::endl;
		std::cout<<wpcount<<std::endl;
		std::cout<<WPnr<<std::endl;
		std::cout<<sqrt(abs((Corx-GX)*(Corx-GX)) + abs((Cory-GY)*(Cory-GY)))<<std::endl;
		if(Gnr==1){
			G1dir = CheckDir( up,  down,  left,  right, WPnr, Gnr);}
		else if(Gnr==2){
			G2dir = CheckDir( up,  down,  left,  right, WPnr, Gnr);
		}
		else if(Gnr==3){
			G3dir = CheckDir( up,  down,  left,  right, WPnr, Gnr);
		}
		else if(Gnr==4){
			G4dir = CheckDir( up,  down,  left,  right, WPnr, Gnr);
		}
		std::cout<<G1dir<<std::endl;
	}
}

int CavePacman::CheckDir( bool up, bool down, bool left, bool right, int WPnr, int Gnr)
{
	if(Gnr==1){
	if(G1dir==1){down=false;}
	if(G1dir==2){left=false;}
	if(G1dir==3){up=false;}
	if(G1dir==4){right=false;}
	}else if(Gnr==2){
		if(G2dir==1){down=false;}
		if(G2dir==2){left=false;}
		if(G2dir==3){up=false;}
		if(G2dir==4){right=false;}
	}else if(Gnr==3){
		if(G3dir==1){down=false;}
		if(G3dir==2){left=false;}
		if(G3dir==3){up=false;}
		if(G3dir==4){right=false;}
	}else if(Gnr==4){
		if(G4dir==1){down=false;}
		if(G4dir==2){left=false;}
		if(G4dir==3){up=false;}
		if(G4dir==4){right=false;}
	}

	std::cout<<"#*#"<<std::endl;
	std::cout<<G1dir<<std::endl;
	std::cout<<"###"<<std::endl;
	std::cout<<up<<std::endl;
	std::cout<<right<<std::endl;
	std::cout<<down<<std::endl;
	std::cout<<left<<std::endl;
	std::cout<<"---"<<std::endl;

	int upr, leftr, downr, rightr, Gdir;

	if(up){upr=rand(); Gdir=1;}
	else{upr=-1;}
	if(left){leftr=rand();
		if(leftr>upr)
		{Gdir=4;}}
	else{leftr=-1;}
	if(down){downr=rand();
		if(downr>leftr && downr>upr)
		{Gdir=3;}}
	else{downr=-1;}
	if(right){rightr=rand();
		if(rightr>downr && rightr>leftr && rightr>upr)
		{Gdir=2;}}
	else{rightr=-1;}

	std::cout<<"---"<<std::endl;
	std::cout<<upr<<std::endl;
	std::cout<<rightr<<std::endl;
	std::cout<<downr<<std::endl;
	std::cout<<leftr<<std::endl;
	std::cout<<"###"<<std::endl;
	std::cout<<G1dir<<std::endl;
	std::cout<<"#*#"<<std::endl;

	if(Gnr==1){
		lastwpG1=WPnr;
	}else if(Gnr==2){
		lastwpG2=WPnr;
	}else if(Gnr==3){
		lastwpG3=WPnr;
	}else if(Gnr==4){
		lastwpG4=WPnr;
	}
	
	return Gdir;
	
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
	addOrb(0, 0);
	placeWayPoints();
}

void CavePacman::addBlock(int x, int z)
{
	grid[x][z] = true;
	objects[x][z] = new Block(x, z);
	coordinates.push_back(new Coordinate(x, z));
}

void CavePacman::addOrb(int x, int z)
{
	orbGrid[x][z] = true;
	orbs[x][z] = new DefaultOrb(x, z);
	orbCoordinates.push_back(new Coordinate(x, z));
}

void CavePacman::contextInit()
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);


	Ghost* g = new Ghost("data/models/LoL/" + models[85]["dir"].asString() + "/" + models[85]["models"][1]["model"].asString());
	g->SetTexture("data/models/LoL/" + models[85]["dir"].asString() + "/" + models[85]["models"][1]["texture"].asString());
	ghosts.push_back(g);
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

	if(mRightButton->getData() == gadget::Digital::ON)
	{
		rotate +=1;
	}
	if(mLeftButton->getData() == gadget::Digital::ON)
	{
		rotate -=1;
	}
	
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
	//int xGrid2 = x;
	//int zGrid2 = z;
	switch(direction)
	{
		case LEFT: xGrid = pacman->determineXGridLeft(-0.2f); break;
		case RIGHT: xGrid = pacman->determineXGridRight(0.2f); break;
		case UP: zGrid = pacman->determineZGridUp(-0.2f); break;
		case DOWN: zGrid = pacman->determineZGridDown(0.2f); break;
	}
	if(xGrid >= 0 && xGrid < 24 && zGrid >= 0 && zGrid < 24 && grid[xGrid][zGrid]==false)
	{
		switch(direction)
		{
			case LEFT: pacman->moveX(-0.2f); break;
			case RIGHT: pacman->moveX(0.2f); break;
			case UP: pacman->moveZ(-0.2f); break;
			case DOWN: pacman->moveZ(0.2f); break;
		}
	}
	
	//checkCollision();
}

void CavePacman::checkCollision()
{
	int x = pacman->getXGrid();
	int z = pacman->getZGrid();
	std::cout << "X: " << x << ", Z: " << z << "OCCUPIED: " << grid[x][z] << std::endl;
	bool revert = false;
	if(grid[x][z]==true)
	{
		Block* block = objects[x][z];
		if(block->contains(x*10, 0, z*10) || block->contains((x+1)*10, 0, z*10) || block->contains(x*10, 0, (z+1)*10) || block->contains((x+1)*10, 0, (z+1)*10))
		{
			revert = true;
		}
	}
	if(grid[x+1][z]==true)
	{
		Block* block = objects[x+1][z];
		if(block->contains(x*10, 0, z*10) || block->contains((x+1)*10, 0, z*10) || block->contains(x*10, 0, (z+1)*10) || block->contains((x+1)*10, 0, (z+1)*10))
		{
			revert = true;
		}
	}
	if(grid[x][z+1]==true)
	{
		Block* block = objects[x][z+1];
		if(block->contains(x*10, 0, z*10) || block->contains((x+1)*10, 0, z*10) || block->contains(x*10, 0, (z+1)*10) || block->contains((x+1)*10, 0, (z+1)*10))
		{
			revert = true;
		}
	}if(grid[x+1][z+1]==true)
	{
		Block* block = objects[x+1][z+1];
		if(block->contains(x*10, 0, z*10) || block->contains((x+1)*10, 0, z*10) || block->contains(x*10, 0, (z+1)*10) || block->contains((x+1)*10, 0, (z+1)*10))
		{
			revert = true;
		}
	}

	if(revert==true)
	{
		//Revert movement
		switch(direction)
		{
			case LEFT: pacman->moveX(0.2f); break;
			case RIGHT: pacman->moveX(-0.2f); break;
			case UP: pacman->moveZ(0.2f); break;
			case DOWN: pacman->moveZ(-0.2f); break;
		}
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
		objects[c->x][c->z]->draw();
	}
	glDisable(GL_TEXTURE_2D);
	//Draw orbs
	for(int i = 0; i < orbCoordinates.size(); i++)
	{
		Coordinate* c = orbCoordinates[i];
		orbs[c->x][c->z]->draw();
	}

	for(int i = 0; i < ghosts.size(); i++)
	{
		ghosts[i]->Draw();
	}

	//Test
	int xGrid = pacman->getXGrid();
	int zGrid = pacman->getZGrid();
	glColor3f(1.0f, 0.0f, 0.0f);
	draw3DRectangle(-5.0f+(xGrid*10.0f), -5.0f, -5.0f+(zGrid*10.0f), 10.0f, 1.0f, 10.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	if(grid[xGrid+1][zGrid]==false)
	{
		draw3DRectangle(-5.0f+((xGrid+1)*10.0f), -5.0f, -5.0f+(zGrid*10.0f), 10.0f, 1.0f, 10.0f);
	}
	if(grid[xGrid-1][zGrid]==false)
	{
		draw3DRectangle(-5.0f+((xGrid-1)*10.0f), -5.0f, -5.0f+(zGrid*10.0f), 10.0f, 1.0f, 10.0f);
	}
	if(grid[xGrid][zGrid+1]==false)
	{
		draw3DRectangle(-5.0f+(xGrid*10.0f), -5.0f, -5.0f+((zGrid+1)*10.0f), 10.0f, 1.0f, 10.0f);
	}
	if(grid[xGrid][zGrid-1]==false)
	{
		draw3DRectangle(-5.0f+(xGrid*10.0f), -5.0f, -5.0f+((zGrid-1)*10.0f), 10.0f, 1.0f, 10.0f);
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
