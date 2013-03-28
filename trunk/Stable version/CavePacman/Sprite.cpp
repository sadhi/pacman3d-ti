#include "Sprite.h"


Sprite::Sprite(int x, int z)
{
}

bool Sprite:: contains(float x2, float y2, float z2)
{
	//std::cout << x2 << ", " << y2 << ", " << z2 << std::endl;
	if(x2 >= x && x2 <= x+w && y2 >= y && y2 <= y+h && z2 >= z && z2 <= z+d)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Sprite:: update()
{
}

void Sprite::draw()
{
}

void Sprite:: drawSphere(double radius, int nSlice, int nStack) 
{
	double M_PI = 3.14159265359;
	int i, j;
    double phi; //
    double theta; //long
	float p[31][31][3]; //Vertex
    float *p1,*p2,*p3,*p4;

    if(nSlice > 30) nSlice = 30;
    if(nStack > 30) nStack = 30;

    //Vertex
    for(i = 0;i <= nSlice;i++)
    {   
		phi = 2.0 * M_PI * (double)i / (double)nSlice;
        for(j = 0;j <= nStack;j++)
        {   
			theta = M_PI * (double)j / (double)nStack;
            p[i][j][0] = (float)(radius * sin(theta) * cos(phi));//x
            p[i][j][1] = (float)(radius * sin(theta) * sin(phi));//y
            p[i][j][2] = (float)(radius * cos(theta));           //z
		}
	}

	//Top(j=0)
	for(i = 0;i < nSlice; i++)
	{
		p1 = p[i][0];     p2 = p[i][1];
        p3 = p[i+1][1]; 
		glBegin(GL_TRIANGLES);
        glNormal3fv(p1); glVertex3fv(p1);
        glNormal3fv(p2); glVertex3fv(p2);
        glNormal3fv(p3); glVertex3fv(p3);
        glEnd();
	}
    //Bottom
    j=nStack-1;
    for(i = 0;i < nSlice; i++)
    {
		p1 = p[i][j];     p2 = p[i][j+1];
        p3 = p[i+1][j]; 
		glBegin(GL_TRIANGLES);
        glNormal3fv(p1); glVertex3fv(p1);
        glNormal3fv(p2); glVertex3fv(p2);
        glNormal3fv(p3); glVertex3fv(p3);
        glEnd();
	}

	for(i = 0;i < nSlice;i++)
	{
		for(j = 1;j < nStack-1; j++)
		{
			p1 = p[i][j];     p2 = p[i][j+1];
			p3 = p[i+1][j+1]; p4 = p[i+1][j];
            glBegin(GL_QUADS);
            glNormal3fv(p1); glVertex3fv(p1);
            glNormal3fv(p2); glVertex3fv(p2);
            glNormal3fv(p3); glVertex3fv(p3);
            glNormal3fv(p4); glVertex3fv(p4);
			glEnd();
		}
	}
}

void Sprite:: draw3DRectangle(const float x1, const float y1, const float z1, const float w1, const float h1, const float d1)
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

