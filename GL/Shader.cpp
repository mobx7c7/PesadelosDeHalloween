/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2014-11-28
***********************************************************************/
#include "Shader.h"
#include "gl_includes.h"
#include <fstream>
#include <iostream>
#include <sstream>

unsigned toGLEnumShaderType(ShaderType type)
{
	switch(type)
	{
		case ShaderType::Vertex:
			return GL_VERTEX_SHADER;
		case ShaderType::Fragment:
			return GL_FRAGMENT_SHADER;
        case ShaderType::Geometry:
			return GL_GEOMETRY_SHADER;
        case ShaderType::Compute:
			return GL_COMPUTE_SHADER;
		default:
			return 0;
	}
}

Shader::Shader()
{

}

Shader::~Shader()
{
	clear();
}

int Shader::loadShaderFile(string file, ShaderType type)
{
	ifstream f(file, ifstream::binary);

	if(!f)
	{
		cerr << "[Shader] Impossível abrir o arquivo \"" << file << "\""<< endl;
		return -1;
	}

	stringstream data;
	data << f.rdbuf();

	f.close();

	cout << "[Shader] Carregando arquivo \"" << file << "\"" <<  endl;

	return loadShaderData(data.str(), type);
}

int Shader::loadShaderData(string data, ShaderType type)
{
	if(!glIsProgram(objectID))
	{
		objectID = glCreateProgram();
	}

	GLuint shader = glCreateShader(toGLEnumShaderType(type));

	const char* c_str = data.c_str();
	glShaderSource(shader, 1, &c_str, NULL);

	glCompileShader(shader);

	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if(result == GL_FALSE)
	{
		int length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		if(length > 0)
		{
			char* log = new char[length];
			int written = 0;
			glGetShaderInfoLog(shader, length, &written, log);
			this->log = log;
			cerr << log << endl;
			delete[] log;
		}
		return -1;
	}
	glAttachShader(objectID, shader);
	return 0;
}

int Shader::clear()
{
	if(!glIsProgram(objectID))
	{
		cerr << "[Shader] Impossível limpar programa" << endl;
		return -1;
	}
	// Query the number of attached shaders
	int shadersAttached = 0;
	glGetProgramiv(objectID, GL_ATTACHED_SHADERS, &shadersAttached);
	// Get the shader names
	unsigned* shaderNames = new unsigned[shadersAttached];
	glGetAttachedShaders(objectID, shadersAttached, NULL, shaderNames);
	// Delete the shaders
	for (int i = 0; i < shadersAttached; i++)
	{
		glDeleteShader(shaderNames[i]);
	}
	// Delete the program
	glDeleteProgram (objectID);
	delete[] shaderNames;

	_linked = false;

	return 0;
}

int Shader::link()
{
	if(_linked)
	{
		cerr << "[Shader] Impossível ligar programa (link)" << endl;
		return -1;
	}

	glLinkProgram(objectID);

	int status = 0;
	glGetProgramiv(objectID, GL_LINK_STATUS, &status);
	if(GL_FALSE == status)
	{
		int length = 0;
		glGetProgramiv(objectID, GL_INFO_LOG_LENGTH, &length);
		if(length > 0)
		{
			char* log = new char[length];
			int written = 0;
			glGetProgramInfoLog(objectID, length, &written, log);
			this->log = log;
			cerr << log << endl;
			delete[] log;
		}
		return -1;
	}

	_linked = true;

	return 0;
}

bool Shader::isLinked()
{
	return _linked;
}

unsigned Shader::getAtrributeLocation(string name) const
{
	return glGetAttribLocation(objectID, name.c_str());
}

unsigned Shader::getUniformLocation(string name) const
{
	return glGetUniformLocation(objectID, name.c_str());
}

void Shader::enableVertexAttribArray(string name)
{
	glEnableVertexAttribArray(getAtrributeLocation(name));
}

void Shader::disableVertexAttribArray(string name)
{
	glDisableVertexAttribArray(getAtrributeLocation(name));
}

void Shader::setVertexAttribPointer(string name, unsigned size, unsigned type, bool normalized, unsigned stride, const void* ptr)
{
	glVertexAttribPointer(getAtrributeLocation(name), size, type, normalized, stride, ptr);
}

void Shader::setVertexAttribIPointer(string name, unsigned size, unsigned type, unsigned stride, const void* ptr)
{
	glVertexAttribIPointer(getAtrributeLocation(name), size, type, stride, ptr);
}

void Shader::setUniform1i(string name, int v1)
{
	glUniform1i(getUniformLocation(name), v1);
}

void Shader::setUniform2i(string name, int v1, int v2)
{
	glUniform2i(getUniformLocation(name), v1, v2);
}

void Shader::setUniform3i(string name, int v1, int v2, int v3)
{
	glUniform3i(getUniformLocation(name), v1, v2, v3);
}

void Shader::setUniform4i(string name, int v1, int v2, int v3, int v4)
{
	glUniform4i(getUniformLocation(name), v1, v2, v3, v4);
}

void Shader::setUniform1f(string name, float v1)
{
	glUniform1f(getUniformLocation(name), v1);
}

void Shader::setUniform2f(string name, float v1, float v2)
{
	glUniform2f(getUniformLocation(name), v1, v2);
}

void Shader::setUniform3f(string name, float v1, float v2, float v3)
{
	glUniform3f(getUniformLocation(name), v1, v2, v3);
}

void Shader::setUniform4f(string name, float v1, float v2, float v3, float v4)
{
	glUniform4f(getUniformLocation(name), v1, v2, v3, v4);
}

void Shader::setUniform1d(string name, double v1)
{
	glUniform1d(getUniformLocation(name), v1);
}

void Shader::setUniform2d(string name, double v1, double v2)
{
	glUniform2d(getUniformLocation(name), v1, v2);
}

void Shader::setUniform3d(string name, double v1, double v2, double v3)
{
	glUniform3d(getUniformLocation(name), v1, v2, v3);
}

void Shader::setUniform4d(string name, double v1, double v2, double v3, double v4)
{
	glUniform4d(getUniformLocation(name), v1, v2, v3, v4);
}

void Shader::setUniform1iv(string name, int count, int* ptr)
{
	glUniform1iv(getUniformLocation(name), count, ptr);
}

void Shader::setUniform2iv(string name, int count, int* ptr)
{
	glUniform2iv(getUniformLocation(name), count, ptr);
}

void Shader::setUniform3iv(string name, int count, int* ptr)
{
	glUniform3iv(getUniformLocation(name), count, ptr);
}

void Shader::setUniform4iv(string name, int count, int* ptr)
{
	glUniform4iv(getUniformLocation(name), count, ptr);
}

void Shader::setUniform1fv(string name, int count, float* ptr)
{
	glUniform1fv(getUniformLocation(name), count, ptr);
}

void Shader::setUniform2fv(string name, int count, float* ptr)
{
	glUniform2fv(getUniformLocation(name), count, ptr);
}

void Shader::setUniform3fv(string name, int count, float* ptr)
{
	glUniform3fv(getUniformLocation(name), count, ptr);
}

void Shader::setUniform4fv(string name, int count, float* ptr)
{
	glUniform4fv(getUniformLocation(name), count, ptr);
}

void Shader::setUniform1dv(string name, int count, double* ptr)
{
	glUniform1dv(getUniformLocation(name), count, ptr);
}

void Shader::setUniform2dv(string name, int count, double* ptr)
{
	glUniform2dv(getUniformLocation(name), count, ptr);
}

void Shader::setUniform3dv(string name, int count, double* ptr)
{
	glUniform3dv(getUniformLocation(name), count, ptr);
}

void Shader::setUniform4dv(string name, int count, double* ptr)
{
	glUniform4dv(getUniformLocation(name), count, ptr);
}

void Shader::setUniformMatrix2f(string name, int count, float* ptr)
{
	glUniformMatrix2fv(getUniformLocation(name), count, false, ptr);
}

void Shader::setUniformMatrix3f(string name, int count, float* ptr)
{
	glUniformMatrix3fv(getUniformLocation(name), count, false, ptr);
}

void Shader::setUniformMatrix4f(string name, int count, float* ptr)
{
	glUniformMatrix4fv(getUniformLocation(name), count, false, ptr);
}

void Shader::bind()
{
    glUseProgram(objectID);
}

void Shader::unbind()
{
	glUseProgram(0);
}
