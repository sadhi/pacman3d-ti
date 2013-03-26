#include "Mycave.h"
#include <GL/GL.h>
#include <glut.h>
#include "WayPoint.h"
#include <list>
#include <set>
#include <time.h>
#include <random>
#include <ctime>

float cnt=0;
int wpcount=0;
float Headx=5, Heady=5, Headz=5;

float CFcubesize=1.0, CFdensity=1.0; //for complete fill and no overlap make them the same
int CFdimension=10;

//gavegame
float Gspeed=0.02, G1x=0, G1y=0, G2x=0, G2y=0, G3x=0, G3y=0, G4x=0, G4y=0;
int G1dir=0, G2dir=0, G3dir=0, G4dir=0;
int lastwpG1=0, lastwpG2=0, lastwpG3=0, lastwpG4=0;

Mycave::Mycave(void)
{
	
}

Mycave::~Mycave(void)
{
}


void Mycave::init()
{
	placeWayPoint();
}

void Mycave::contextInit()
{
	srand(time(0));
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
}

void Mycave::preFrame()
{
	cnt++;
}

void Mycave::bufferPreDraw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Mycave::draw()
{
	CFLights();
//	drawCF();
//	drawCC();

	placeWayPoint();
	SetGhostStep();
	drawpathfindingdemo();

	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Mycave::drawpathfindingdemo()
{
	glPushMatrix();
	glTranslatef(G1x,0,G1y);
	glutSolidSphere(0.5,16,16);
	glTranslatef(-G1x,0,-G1y);

	glTranslatef(G2x,0,G2y);
	glutSolidSphere(0.5,16,16);
	glTranslatef(-G2x,0,-G2y);
	glPopMatrix();

	glTranslatef(G3x,0,G3y);
	glutSolidSphere(0.5,16,16);
	glTranslatef(-G3x,0,-G3y);
	glPopMatrix();

	glTranslatef(G4x,0,G4y);
	glutSolidSphere(0.5,16,16);
	glTranslatef(-G4x,0,-G4y);
	glPopMatrix();
}


void Mycave::SetGhostStep()
{
	if(G1dir==0){
		 G1dir = (rand()%4)+1; 
	}
	if(G1dir==1){
		G1y-=Gspeed;
	}else if(G1dir==2){
		G1x+=Gspeed;
	}else if(G1dir==3){
		G1y+=Gspeed;
	}else if(G1dir==4){
		G1x-=Gspeed;
	}

	if(G2dir==0){
		 G2dir = (rand()%4)+1; 
	}
	if(G2dir==1){
		G2y-=Gspeed;
	}else if(G2dir==2){
		G2x+=Gspeed;
	}else if(G2dir==3){
		G2y+=Gspeed;
	}else if(G2dir==4){
		G2x-=Gspeed;
	}

	if(G3dir==0){
		 G3dir = (rand()%4)+1; 
	}
	if(G3dir==1){
		G3y-=Gspeed;
	}else if(G3dir==2){
		G3x+=Gspeed;
	}else if(G3dir==3){
		G3y+=Gspeed;
	}else if(G3dir==4){
		G3x-=Gspeed;
	}

	if(G4dir==0){
		 G4dir = (rand()%4)+1; 
	}
	if(G4dir==1){
		G4y-=Gspeed;
	}else if(G4dir==2){
		G4x+=Gspeed;
	}else if(G4dir==3){
		G4y+=Gspeed;
	}else if(G4dir==4){
		G4x-=Gspeed;
	}
	
}

void Mycave::placeWayPoint()
{
	//x y up down left right id
	drawWaypoint(-5,-5,false, true, false,true, 1);
	drawWaypoint(0,-5,true, true, true,true, 2);
	drawWaypoint(5,-5,true, false, true,false, 3);
	drawWaypoint(-5,0,true, true, false,true, 4);
	drawWaypoint(0,0,true, true, true,false, 5);
	//drawWaypoint(5,0,true, true, true,false, 6);
	drawWaypoint(-5,5,true, false, false,true, 7);
	drawWaypoint(0,5,true, true, true,false, 8);
	//drawWaypoint(5,5,true, false, true,false, 9);
	drawWaypoint(0,-10,false, true, false,true, 10);
	drawWaypoint(5,-10,false, true, true,false, 11);
	drawWaypoint(0,10,true, false, false,true, 12);
	drawWaypoint(5,10,false, false, true,true, 13);
	drawWaypoint(10,-10,false, true, true,false, 14);
	drawWaypoint(10,-5,true, true, false,false, 15);
	drawWaypoint(10,0,true, true, false,true, 16);
	drawWaypoint(10,5,true, true, false,true, 17);
	drawWaypoint(10,10,true, false, true,false, 18);
	drawWaypoint(15,0,false, true, true,false, 19);
	drawWaypoint(15,5,true, false, true,false, 20);
}

void Mycave::drawWaypoint(float Corx, float Cory, bool up, bool down, bool left, bool right, int WPnr)
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

void Mycave::CheckDir(float Corx, float Cory, float GX, float GY, bool up, bool down, bool left, bool right, int WPnr, int Gnr)
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

int Mycave::CheckDir( bool up, bool down, bool left, bool right, int WPnr, int Gnr)
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

void Mycave::drawCF()
{
	
	glPushMatrix();
	glTranslatef(-(CFdimension/2),-(CFdimension/2),-(CFdimension/2));
	
	float Xsize=CFdimension, Ysize=CFdimension, Zsize=CFdimension;

	for ( float Z = 1; Z < Zsize; Z+=CFdensity )
	{
	for ( float X = 1; X < Xsize; X+=CFdensity )
	{
		for ( float Y = 1; Y < Ysize; Y+=CFdensity )
		{
			glTranslatef(X, Y, Z);
			float sincosdivider = ((cosf(cnt/70)/2)+0.5);
			glColor4f(1.0,1.0,1.0,0.1);

			glutSolidCube(((sincosdivider*((sinf(cnt/(50+Z+X+Y))/2)+0.5)+(abs(sincosdivider-1))*((cosf(cnt/(50-Z-X-Y))/2)+0.5))*CFcubesize)*(min(1,(CFDistanceFromHead(X, Y, Z, Headx, Heady, Headz)/2))));

			glTranslatef(-X, -Y, -Z);
		}
	}
	}
	glPopMatrix();
}

void Mycave::CFLights()
{
	//ambient
	GLfloat ambientColor[] = {0.1f, 0.1f, 0.1f, 0.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//positioned0
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 0.5f};
	GLfloat lightPos0[] = {0.0f, 0.0f, 0.0f, 1.0f}; 
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	 //spotlight1 (rotating)
    GLfloat lightColor1[] = {0.5f, 0.9f, 0.5f, 0.5f};
    GLfloat lightPos1[] = {sinf(cnt/30)*10, 0.0f, cosf(cnt/30)*10, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	
/*	
	glPushMatrix();
	glTranslatef(sinf(cnt/30)*15, 0.0f, cosf(cnt/30)*15);
	glutSolidCube(1);
	glPopMatrix();
*/
	//spotlight2 (rotating)
    GLfloat lightColor2[] = {0.5f, 0.5f, 0.9f, 0.5f};
    GLfloat lightPos2[] = {sinf(cnt/50)*10, cosf(cnt/50)*10, 0.0f, 0.0f};
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);

/*	
	glPushMatrix();
	glTranslatef(sinf(cnt/50)*15, cosf(cnt/50)*15, 0.0f);
	glutSolidCube(1);
	glPopMatrix();
*/

	//spotlight3 (rotating)
    GLfloat lightColor3[] = {0.9f, 0.5f, 0.0f, 0.5f};
    GLfloat lightPos3[] = {cosf(cnt/90)*10, sinf(cnt/215)*10, cosf(cnt/90)*10, 0.0f};
    glLightfv(GL_LIGHT3, GL_DIFFUSE, lightColor3);
    glLightfv(GL_LIGHT3, GL_POSITION, lightPos3);

/*		
	glPushMatrix();
	glTranslatef(cosf(cnt/90)*15, sinf(cnt/90)*15, cosf(cnt/90)*15);
	glutSolidCube(1);
	glPopMatrix();
*/
}

float Mycave::CFDistanceFromHead(float X1, float Y1, float Z1, float X2, float Y2, float Z2)
{
	 float d = sqrt((abs((X1-X2)*(X1-X2))) + (abs((Y1-Y2)*(Y1-Y2))) + (abs((Z1-Z2)*(Z1-Z2)))); 
	 return d;
}

bool Mycave::CFFarAwayFromHead(float X1, float Y1, float Z1, float X2, float Y2, float Z2)
{

	 float d = CFDistanceFromHead( X1,  Y1,  Z1,  X2,  Y2,  Z2);
	 if(d>0.5)
	 { 
		return true;
	 }
	 else
	 {
		return false;
	 }
}


void Mycave::drawCC()
{
	glPushMatrix();
	for ( float Circel = 0; Circel < 180; Circel+=20 )
	{
		glRotatef(Circel, 0, 0, 1);
	for ( float Ring = 0; Ring < 360; Ring+=10 )
	{
		glPushMatrix();
	glRotatef(Ring+cnt+sin(cnt/Ring)*20, 0, 1, 0);
	glTranslatef(0,0,10);
	glRotatef(sin(cnt/80)*20,1,1,1);
	glutSolidCube(CFcubesize);
		glPopMatrix();
	}
		glRotatef(-Circel, 0, 0, 1);
	}
	glPopMatrix();
}




