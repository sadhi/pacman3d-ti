#pragma once

#include <windows.h>
#include <gl/GL.h>

#include <string>
#include <vector>
#include <map>
#include <gmtl/Matrix.h>


class ShaderProgram
{
	class Shader
	{
	public:
		GLuint shaderId;
		Shader(std::string fileName, GLenum type);
	};


	GLuint programId;
	std::vector<Shader*> shaders;
	
	std::map<std::string, int> uniformLocations;

public:
	ShaderProgram(std::string vertShader, std::string fragShader);
	~ShaderProgram();

	void addVertexShader(std::string filename);
	void addFragmentShader(std::string filename);

//attributes
	void bindAttributeLocation(std::string name, int position);
	void bindFragLocation( std::string name, int position );
//uniforms
	GLuint getUniformLocation(std::string);
	void setUniformMatrix4(std::string name, gmtl::Matrix44f matrix);
	void setUniformMatrix3(std::string name, gmtl::Matrix33f matrix);
	void setUniformInt(std::string name, int value);
	



	void link();
	void use();
};

