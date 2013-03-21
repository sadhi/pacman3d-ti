#include "Orb.h"


Orb::Orb(int x, int z)
{
}

bool Orb:: contains(float x2, float y2, float z2)
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

void Orb:: update()
{
}

void Orb::draw()
{
}

void Orb:: drawSphere(double r, int lats, int longs) 
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

