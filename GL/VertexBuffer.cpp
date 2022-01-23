/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2014-11-28
***********************************************************************/
#include "VertexBuffer.h"
#include "gl_includes.h"

#include <iostream>

unsigned toGLEnumVertexBufferTarget(VertexBufferTarget target)
{
	switch(target)
	{
		case VertexBufferTarget::ArrayBuffer:
			return GL_ARRAY_BUFFER;
		case VertexBufferTarget::ElementBuffer:
			return GL_ELEMENT_ARRAY_BUFFER;
		default:
			return 0;
	}
}

unsigned toGLEnumVertexBufferUsage(VertexBufferUsage usage)
{
	switch(usage)
	{
		case VertexBufferUsage::DynamicDraw:    return GL_DYNAMIC_DRAW;
		case VertexBufferUsage::DynamicRead:    return GL_DYNAMIC_READ;
		case VertexBufferUsage::DynamicCopy: 	return GL_DYNAMIC_COPY;
		case VertexBufferUsage::StaticDraw:     return GL_STATIC_DRAW;
		case VertexBufferUsage::StaticRead:     return GL_STATIC_READ;
		case VertexBufferUsage::StaticCopy:     return GL_STATIC_COPY;
		case VertexBufferUsage::StreamDraw:     return GL_STREAM_DRAW;
		case VertexBufferUsage::StreamRead:     return GL_STREAM_READ;
		case VertexBufferUsage::StreamCopy:     return GL_STREAM_COPY;
		default:                                return 0;
	}
}

unsigned toGLEnumVertexBufferMapAccess(VertexBufferMapAccess access)
{
	switch(access)
	{
		case VertexBufferMapAccess::Read:           return GL_MAP_READ_BIT;
		case VertexBufferMapAccess::Write:          return GL_MAP_WRITE_BIT;
		case VertexBufferMapAccess::ReadAndWrite:   return GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
		default:                                    return 0;
	}
}

VertexBuffer::VertexBuffer(VertexBufferTarget target)
{
	_target = toGLEnumVertexBufferTarget(target);
	glGenBuffers(1, &objectID);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &objectID);
}

void VertexBuffer::bufferData(unsigned size, const void* data, VertexBufferUsage usage)
{
	bind();
	glBufferData(_target, size, data, toGLEnumVertexBufferUsage(usage));
}

void VertexBuffer::bufferSubData(unsigned offset, unsigned size, const void* data)
{
	bind();
	glBufferSubData(_target, offset, size, data);
}

unsigned VertexBuffer::getTarget()
{
	return _target;
}

char* VertexBuffer::map(VertexBufferMapAccess access)
{
	bind();
	return reinterpret_cast<char*>(glMapBuffer(_target, toGLEnumVertexBufferMapAccess(access)));
}

void VertexBuffer::unmap()
{
	bind();
	if(!glUnmapBuffer(_target))
	{
		return;
	}
}

void VertexBuffer::bind()
{
	glBindBuffer(_target, objectID);
}

void VertexBuffer::unbind()
{
	glBindBuffer(_target, 0);
}
