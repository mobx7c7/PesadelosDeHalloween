/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2014-11-28
***********************************************************************/
#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "GLObject.h"
#include <vector>
#include <cstdint>

enum VertexBufferTarget
{
	ArrayBuffer,
	ElementBuffer,
};

enum VertexBufferUsage
{
	DynamicDraw,
	DynamicRead,
	DynamicCopy,
	StaticDraw,
	StaticRead,
	StaticCopy,
	StreamDraw,
	StreamRead,
	StreamCopy,
};

enum VertexBufferMapAccess
{
	Read,
	Write,
	ReadAndWrite,
};

unsigned toGLEnumVertexBufferTarget(VertexBufferTarget);
unsigned toGLEnumVertexBufferUsage(VertexBufferUsage);
unsigned toGLEnumVertexBufferMapAccess(VertexBufferMapAccess);

class VertexBuffer : public GLObject
{
	protected:

		unsigned _target;

	public:

		VertexBuffer(VertexBufferTarget);
		virtual ~VertexBuffer();

		void        bufferData(unsigned, const void*, VertexBufferUsage);
		void        bufferSubData(unsigned, unsigned, const void*);
		unsigned    getTarget();
		char*       map(VertexBufferMapAccess);
		void        unmap();
		void        bind();
		void        unbind();
};


#endif // VERTEXBUFFER_H
