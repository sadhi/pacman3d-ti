#include "Ghost.h"
#include <gl/glew.h>
#include <CaveLib/texture.h>
#include <cavelib/model.h>
#include <cavelib/Shader.h>

#include <gmtl/Xforms.h>
#include <gmtl/Ray.h>
#include <gmtl/VecOps.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Math.h>


Ghost::Ghost(std::string modelFile)
{
	this->modelFile = modelFile;
	model = NULL;

	if(modelFile != "")
	{
		ModelLoadOptions* options = new ModelLoadOptions();
		options->scale = 5;
		model = CaveLib::loadModel(modelFile, options);
		position = gmtl::Vec3f(0, -5 - model->bbox.mMin[1], -4 - model->bbox.mMin[2]);
	}
}


Ghost::~Ghost(void)
{
}

void Ghost::SetTexture(std::string path)
{

	texture = CaveLib::loadTexture(path);

}

void Ghost::Draw()
{
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GEQUAL, 0.99);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	glPushMatrix();

	
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