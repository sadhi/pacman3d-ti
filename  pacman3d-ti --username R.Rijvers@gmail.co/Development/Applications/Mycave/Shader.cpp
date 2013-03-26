#include <gl/glew.h>
#include "Shader.h"
#include <fstream>


void printShaderInfoLog(std::string fileName, GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;
		
	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
		
	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		if(infoLog[0] != '\0')
		{
			printf("%s\n", fileName.c_str());
			printf("%s\n",infoLog);
			//getchar();
		}
		free(infoLog);
	}
}
void printProgramInfoLog(std::string fileName, GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;
		
	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
		
	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		if(infoLog[0] != '\0')
		{
			printf("%s\n", fileName.c_str());
			printf("%s\n",infoLog);
			//getchar();
		}
		free(infoLog);
	}
}


ShaderProgram::ShaderProgram(std::string vertShader, std::string fragShader)
{
	programId = glCreateProgram();
	addVertexShader(vertShader);
	addFragmentShader(fragShader);
}

ShaderProgram::~ShaderProgram(void)
{
}

void ShaderProgram::bindAttributeLocation(std::string name, int position)
{
    glBindAttribLocation(programId, position, name.c_str());
}

void ShaderProgram::bindFragLocation( std::string name, int position )
{
	glBindFragDataLocation(getUniformLocation(name), position, name.c_str());
}

void ShaderProgram::link()
{
	glLinkProgram(programId);
}

void ShaderProgram::use()
{
	glUseProgram(programId);
}

void ShaderProgram::addVertexShader( std::string filename )
{
	Shader* s = new Shader(filename, GL_VERTEX_SHADER);
	shaders.push_back(s);
	glAttachShader(programId, s->shaderId);
}

void ShaderProgram::addFragmentShader( std::string filename )
{
	Shader* s = new Shader(filename, GL_FRAGMENT_SHADER);
	shaders.push_back(s);
	glAttachShader(programId, s->shaderId);
}

void ShaderProgram::setUniformMatrix4(std::string name, gmtl::Matrix44f matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, 0, matrix.getData());
}

void ShaderProgram::setUniformMatrix3(std::string name, gmtl::Matrix33f matrix)
{
	glUniformMatrix3fv(getUniformLocation(name), 1, 0, matrix.getData());
}

void ShaderProgram::setUniformInt(std::string name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}


GLuint ShaderProgram::getUniformLocation(std::string name)
{
	if(uniformLocations.find(name) == uniformLocations.end())
		uniformLocations[name] = glGetUniformLocation(programId, name.c_str());
	return uniformLocations[name];
}







ShaderProgram::Shader::Shader( std::string fileName, GLenum type )
{
	std::string data = "";
	std::string line;
	std::ifstream pFile(fileName);
	while(!pFile.eof() && pFile.good())
	{
		std::getline(pFile, line);
		data += line + "\n";
	}

	shaderId = glCreateShader(type);
	const char* d2 = data.c_str();
	glShaderSource(shaderId, 1, &d2,NULL);
	glCompileShader(shaderId);
	printShaderInfoLog(fileName, shaderId);
}
