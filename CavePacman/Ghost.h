#pragma once

#include <string>
#include <gmtl/Quat.h>
#include <gmtl/Vec.h>
//#include "CaveLib/CaveLib.h"

class cModel;
class cTexture;
class ShaderProgram;

class Ghost
{
public:
	Ghost(std::string);
	~Ghost(void);
	void Draw();
	void SetTexture(std::string);


private:
	cModel* model;
	cTexture* texture;
	std::string modelFile;
	gmtl::Vec3f position;
	gmtl::Quatf rotation;

};

