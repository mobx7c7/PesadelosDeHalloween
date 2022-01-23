/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2014-11-28
***********************************************************************/
#ifndef SHADER_H
#define SHADER_H

#include "GLObject.h"
#include <string>

using std::string;

enum ShaderType
{
	Vertex,
	Fragment,
	Geometry,
	Compute,
};

unsigned toGLEnumShaderType(ShaderType type);

class Shader : public GLObject
{
	protected:

		bool    _linked = false;
		string  log;

	public:

		Shader();
		virtual ~Shader();

		int 		loadShaderFile(string, ShaderType);
		int 		loadShaderData(string, ShaderType);
		int  		link();
		int         clear();
		bool 		isLinked();
		string      getLog();

		unsigned 	getAtrributeLocation(string) const;
		unsigned 	getUniformLocation(string) const;

		void        enableVertexAttribArray(string);
		void        disableVertexAttribArray(string);
		void        setVertexAttribPointer(string, unsigned, unsigned, bool, unsigned, const void*);
		void        setVertexAttribIPointer(string, unsigned, unsigned, unsigned, const void*);

		//incluir funções que, no lugar de string, será um location
		//#define SHADER_UNIFORM_FUNCTIONS_HAVE_LOCATION

		void 		setUniform1i(string, int);
		void 		setUniform2i(string, int, int);
		void 		setUniform3i(string, int, int, int);
		void 		setUniform4i(string, int, int, int, int);

		void 		setUniform1f(string, float);
		void 		setUniform2f(string, float, float);
		void 		setUniform3f(string, float, float, float);
		void 		setUniform4f(string, float, float, float, float);

		void        setUniform1d(string, double);
        void        setUniform2d(string, double, double);
        void        setUniform3d(string, double, double, double);
        void        setUniform4d(string, double, double, double, double);

		void 		setUniform1iv(string, int, int*);
		void 		setUniform2iv(string, int, int*);
		void 		setUniform3iv(string, int, int*);
		void 		setUniform4iv(string, int, int*);

		void 		setUniform1fv(string, int, float*);
		void 		setUniform2fv(string, int, float*);
		void 		setUniform3fv(string, int, float*);
		void 		setUniform4fv(string, int, float*);

		void 		setUniform1dv(string, int, double*);
		void 		setUniform2dv(string, int, double*);
		void 		setUniform3dv(string, int, double*);
		void 		setUniform4dv(string, int, double*);

		void 		setUniformMatrix2f(string, int, float*);
		void 		setUniformMatrix3f(string, int, float*);
		void 		setUniformMatrix4f(string, int, float*);

		void 		bind();
		void 		unbind();
};

#endif // SHADER_H
