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

float Headx=5, Heady=5, Headz=5;

float CFcubesize=1.0, CFdensity=1.0; //for complete fill and no overlap make them the same
int CFdimension=10;

//gavegame
float G1x=0, G1y=1;
int G1dir=1;
//std::vector<WayPoint> WayPoints();
std::vector<std::string> WayPoints;

//quick and dirty

Mycave::Mycave(void)
{
	
}

Mycave::~Mycave(void)
{
}


void Mycave::init()
{

	/*
	WayPoints.push_back(new WayPoints[0].init(-5,-5, false, true, false,true));

	for (int i = 0; i < WayPoints.size(); i++)
	{
   sum = sum + WayPoints[i];
	}
	*/
	placeWayPoint();

}

void Mycave::contextInit()
{
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
	updatePathfindingdemo();
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
	glPopMatrix();
}

void Mycave::updatePathfindingdemo()
{
	SetGhostStep();
}

void Mycave::SetGhostStep()
{
		 srand(time(0));
	if(G1dir==0){
		 G1dir = (rand()%4)+1; 
	}
	if(G1dir==1){
		G1y-=0.001;
	}else if(G1dir==2){
		G1x+=0.001;
	}else if(G1dir==3){
		G1y+=0.001;
	}else if(G1dir==4){
		G1x-=0.001;
	}
	
}

void Mycave::placeWayPoint()
{
	drawWaypoint(-5,-5,false, true, false,true);
	drawWaypoint(0,-5,false, true, true,true);
	drawWaypoint(5,-5,false, true, true,false);
	drawWaypoint(-5,0,true, true, false,true);
	drawWaypoint(0,0,true, true, true,true);
	drawWaypoint(5,0,true, true, true,false);
	drawWaypoint(-5,5,true, false, false,true);
	drawWaypoint(0,5,true, false, true,true);
	drawWaypoint(5,5,true, false, true,false);
}

void Mycave::drawWaypoint(float Corx, float Cory, bool up, bool down, bool left, bool right)
{
	CheckDir( Corx,  Cory, G1x, G1y,  up,  down,  left,  right);
	glPushMatrix();
	glTranslatef(Corx,0,Cory);
	glutSolidSphere(0.3,16,16);
	if(down){
		glutSolidCone(0.3,1.0,8,8);
	}
	if(up){
		glRotatef(180,0,1,0);
			glutSolidCone(0.3,1.0,8,8);
		glRotatef(-180,0,1,0);
	}
	if(right){
		glRotatef(90,0,1,0);
		glutSolidCone(0.3,1.0,8,8);
		glRotatef(-90,0,1,0);
	}
	if(left){
		glRotatef(270,0,1,0);
		glutSolidCone(0.3,1.0,8,8);
		glRotatef(-270,0,1,0);
	}
	glPopMatrix();
}

void Mycave::CheckDir(float Corx, float Cory, float G1X, float G1Y, bool up, bool down, bool left, bool right)
{
	if(
		sqrt(abs((Corx-G1X)*(Corx-G1X)) + abs((Cory-G1Y)*(Cory-G1Y)))<0.1
		)
	{
		if(G1dir==1){
			up=false;
		}else if(G1dir==2){
			right=false;
		}else if(G1dir==3){
			down=false;
		}else if(G1dir==4){
			left=false;
		}
		
		int rotation = rand();
		 std::cout<<rotation<<std::endl;
		if(rotation%2==0){
			rotation=1;
		}else{
			rotation=-1;}
		
		 G1dir = CheckDir( rotation,  up,  down,  left,  right);
		std::cout<<G1dir<<std::endl;
	}
}

int Mycave::CheckDir(int rotation, bool up, bool down, bool left, bool right)
{
	std::cout<<G1dir<<std::endl;
	std::cout<<"###"<<std::endl;
	std::cout<<up<<std::endl;
	std::cout<<right<<std::endl;
	std::cout<<down<<std::endl;
	std::cout<<left<<std::endl;
	std::cout<<"---"<<std::endl;

	if(G1dir==1){up=false;}
	if(G1dir==2){right=false;}
	if(G1dir==3){down=false;}
	if(G1dir==4){left=false;}

	int upr, leftr, downr, rightr;

	if(up){upr=rand(); G1dir=1;}
	else{upr=0;}
	if(left){leftr=rand(); 
		if(leftr>upr)
		{G1dir=2;}}
	else{leftr=0;}
	if(down){downr=rand();
		if(downr>leftr && downr>upr)
		{G1dir=3;}}
	else{downr=0;}
	if(right){rightr=rand();
		if(rightr>downr && rightr>leftr && rightr>upr)
		{G1dir=3;}}
	else{rightr=0;}

	return G1dir;
	std::cout<<"---"<<std::endl;
	std::cout<<upr<<std::endl;
	std::cout<<leftr<<std::endl;
	std::cout<<downr<<std::endl;
	std::cout<<rightr<<std::endl;
	std::cout<<"###"<<std::endl;
	std::cout<<G1dir<<std::endl;

	/*
		int checkpath=G1dir+rotation;
		if(checkpath<=0){
			checkpath=4;
		}else if(checkpath>=5){
			checkpath=1;
		}

		if(checkpath==1){
			if(up){
				return checkpath;
			}else{
				return CheckDir( rotation,  G1dir, up,  down,  left,  right);
			}
		}else if(checkpath==2){
			if(right){
				return checkpath;
			}else{
				return CheckDir( rotation,  G1dir, up,  down,  left,  right);
			}
		}else if(checkpath==3){
			if(down){
				return checkpath;
			}else{
				return CheckDir( rotation,  G1dir, up,  down,  left,  right);
			}
		}else if(checkpath==4){
			if(left){
				return checkpath;
			}else{
				return CheckDir( rotation,  G1dir, up,  down,  left,  right);
			}
		}
	*/	
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




