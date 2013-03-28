#include "Ghost.h"

#include <CaveLib/texture.h>
#include <cavelib/model.h>
#include <cavelib/Shader.h>

#include <gmtl/Xforms.h>
#include <gmtl/Ray.h>
#include <gmtl/VecOps.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Math.h>


Ghost::Ghost(int x, int z):Sprite(x, z)
{
	this->x = (x*10.0f)-5.0f;
	this->y = -5.0f;
	this->z = (z*10.0f)-5.0f;
	this->w = 10.0f;
	this->h = 10.0f;
	this->d = 10.0f;

	switch(rand()%7)
	{
		//Red
		case 0: red = 1.0f; green = 0.0f; blue = 0.0f; break;
		//Green
		case 1: red = 0.0f; green = 1.0f; blue = 0.0f; break;
		//Blue
		case 2: red = 0.0f; green = 0.0f; blue = 1.0f; break;
		//Yellow
		case 3: red = 1.0f; green = 1.0f; blue = 0.0f; break;
		//Cyan
		case 4: red = 0.0f; green = 1.0f; blue = 1.0f; break;
		//Magenta
		case 5: red = 1.0f; green = 0.0f; blue = 1.0f; break;
		//White
		case 6: red = 1.0f; green = 1.0f; blue = 1.0f; break;
	}

	//Load model
	std::string modelFile = "Data/Models/LoL/Kassadin/kassadin_darkblade.skn";
	std::string texturePath = "Data/Models/LoL/Kassadin/kassadin_darkblade_TX_CM.dds";

	this->modelFile = modelFile;
	model = NULL;

	if(modelFile != "")
	{
		ModelLoadOptions* options = new ModelLoadOptions();
		options->scale = 5;
		model = CaveLib::loadModel(modelFile, options);
		position = gmtl::Vec3f(0, -5 - model->bbox.mMin[1], -4 - model->bbox.mMin[2]);
	}
	texture = CaveLib::loadTexture(texturePath);
}


Ghost::~Ghost(void)
{
}

bool Ghost::intersects(float x2, float y2, float z2)
{
	double radius = 0.0f;
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

void Ghost::draw()
{
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GEQUAL, 0.99);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	glPushMatrix();
	glTranslatef(x + 5.0f, -5.0f, z + 5.0f);
	glColor4f(red, green, blue, 1.0f);
	std::cout << "Color: " << red << ", " << green << ", " << blue << std::endl;
	if(texture)
	glBindTexture(GL_TEXTURE_2D, texture->tid());
	else
		std::cout<<"No texture"<<std::endl;

	model->draw();

	glDisable(GL_TEXTURE_2D);
	/*glTranslatef(position[0], position[1], position[2]);
	gmtl::Matrix44f rot = gmtl::make<gmtl::Matrix44f>(rotation);
	glMultMatrixf(rot.mData);*/


	/*shader->use();
	gmtl::Matrix44f modelViewMatrix;
	gmtl::identity(modelViewMatrix);
	modelViewMatrix *= gmtl::makeTrans<gmtl::Matrix44f>(position);
	modelViewMatrix *= gmtl::make<gmtl::Matrix44f>(rotation);

	gmtl::Matrix33f normalMatrix;
	normalMatrix.set(modelViewMatrix[0][0], modelViewMatrix[0][1], modelViewMatrix[0][2],
		modelViewMatrix[1][0], modelViewMatrix[1][1], modelViewMatrix[1][2],
		modelViewMatrix[2][0], modelViewMatrix[2][1], modelViewMatrix[2][2]);
	normalMatrix = gmtl::transpose(gmtl::invert(normalMatrix));


	gmtl::Matrix44f projectionMatrix;
	glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix.mData);

	shader->setUniformBool("useLighting", true);
	shader->setUniformBool("useTexture", true);
	shader->setUniformInt("s_texture", 0);
	shader->setUniformVec3("lightPosition",gmtl::Vec3f(0, 0, 4));
	shader->setUniformVec3("BrickColor", gmtl::Vec3f(1, 0.3, 0.2));
	shader->setUniformVec3("MortarColor", gmtl::Vec3f(0.85, 0.86, 0.84));
	//shader->setUniformVec2("BrickSize", gmtl::Vec2f(1, 0.5));
	//shader->setUniformVec2("BrickPct", gmtl::Vec2f(0.9, 0.85));

	shader->setUniformMatrix3("normalMatrix", normalMatrix);
	shader->setUniformMatrix4("modelViewProjectionMatrix", projectionMatrix * modelViewMatrix);
	shader->setUniformMatrix4("modelViewMatrix", modelViewMatrix);*/

	//model->draw(shader);
	glPopMatrix();
}