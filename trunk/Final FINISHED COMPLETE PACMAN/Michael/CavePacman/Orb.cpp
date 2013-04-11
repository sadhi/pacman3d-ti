#include "Orb.h"


Orb::Orb(int x, int z): Sprite(x, z)
{
	this->type = ORB;
}

bool Orb::intersects(float x2, float z2)
{
	float aX = x + 10.0f-radius;
	float aZ = z +10.0f-radius;
	float aX2 = aX + (radius*2);
	float aZ2 = aZ + (radius*2);
	float bX = x2;
	float bZ = z2;
	float bX2 = x2+5.0f;
	float bZ2 = z2+5.0f;

	if(min(aX2, bX2) > max(aX, bX) && min(aZ2, bZ2) > max(aZ, bZ))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Orb::initSphere(float radius, unsigned int rings, unsigned int sectors)
    {
		double M_PI = 3.14159265358979323846;
		double M_PI_2 = 1.57079632679489661923;

        float const R = 1./(float)(rings-1);
        float const S = 1./(float)(sectors-1);
        int r, s;

        vertices.resize(rings * sectors * 3);
        normals.resize(rings * sectors * 3);
        texcoords.resize(rings * sectors * 2);
        std::vector<GLfloat>::iterator v = vertices.begin();
        std::vector<GLfloat>::iterator n = normals.begin();
        std::vector<GLfloat>::iterator t = texcoords.begin();
        for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
                float const y = sin( -M_PI_2 + M_PI * r * R );
                float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
                float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

                *t++ = s*S;
                *t++ = r*R;

                *v++ = x * radius;
                *v++ = y * radius;
                *v++ = z * radius;

                *n++ = x;
                *n++ = y;
                *n++ = z;
        }

        indices.resize(rings * sectors * 4);
        std::vector<GLushort>::iterator i = indices.begin();
        for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
                *i++ = r * sectors + s;
                *i++ = r * sectors + (s+1);
                *i++ = (r+1) * sectors + (s+1);
                *i++ = (r+1) * sectors + s;
        }
    }

void Orb::drawSphere()
{
	glEnable (GL_LIGHTING);
	 glEnableClientState(GL_VERTEX_ARRAY);
     glEnableClientState(GL_NORMAL_ARRAY);
     glEnableClientState(GL_TEXTURE_COORD_ARRAY);
 
     glVertexPointer(3, GL_FLOAT, 0, vertices.data());
     glNormalPointer(GL_FLOAT, 0, normals.data());
     glTexCoordPointer(2, GL_FLOAT, 0, texcoords.data());
     glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, indices.data());

	 glDisableClientState(GL_VERTEX_ARRAY);
     glDisableClientState(GL_NORMAL_ARRAY);
     glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	 glDisable (GL_LIGHTING);
}
