/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2014-11-28
***********************************************************************/
#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "GLObject.h"

class VertexArray : public GLObject
{
	public:
		VertexArray();
		virtual     ~VertexArray();
		void        enableVertexAttribPointer(unsigned);
		void        disableVertexAttribPointer(unsigned);
		void        setVertexAttribPointer(unsigned, unsigned, DataType, bool, unsigned, const void*);
		void        bind();
		void        unbind();
};

#endif // VERTEXARRAY_H
