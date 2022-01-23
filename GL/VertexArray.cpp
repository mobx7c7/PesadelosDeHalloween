/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2014-11-28
***********************************************************************/
#include "VertexArray.h"
#include "gl_includes.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &objectID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &objectID);
}

void VertexArray::enableVertexAttribPointer(unsigned loc)
{
	glEnableVertexAttribArray(loc);
}

void VertexArray::disableVertexAttribPointer(unsigned loc)
{
	glDisableVertexAttribArray(loc);
}

void VertexArray::setVertexAttribPointer(unsigned loc, unsigned size, DataType type, bool normalized, unsigned stride, const void* ptr)
{
	glVertexAttribPointer(loc, size, toGLEnumDataType(type), normalized, stride, ptr);
}

void VertexArray::bind()
{
	glBindVertexArray(objectID);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}
