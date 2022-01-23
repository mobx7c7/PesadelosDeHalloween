/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2014-11-28
***********************************************************************/
#include "Renderbuffer.h"
#include "gl_includes.h"

Renderbuffer* Renderbuffer::placeholder = 0;

Renderbuffer::Renderbuffer(unsigned width, unsigned height, unsigned internalFormat)
{
	_width  = width;
	_height = height;
	_target = GL_RENDERBUFFER;

    glGenRenderbuffers(1, &objectID);
    bind();
    glRenderbufferStorage(_target, internalFormat, width, height);
    unbind();
}
Renderbuffer::Renderbuffer(unsigned width, unsigned height) :
    Renderbuffer(width, height, GL_DEPTH_COMPONENT)
{

}

Renderbuffer::Renderbuffer()
{

}

Renderbuffer::~Renderbuffer()
{
    glDeleteRenderbuffers(1, &objectID);
}

//Renderbuffer* Renderbuffer::getPlaceholder()
//{
//    if(placeholder) placeholder = new Renderbuffer();
//    return placeholder;
//}

unsigned Renderbuffer::getWidth()
{
	return _width;
}

unsigned Renderbuffer::getHeight()
{
	return _height;
}

unsigned Renderbuffer::getTarget()
{
	return _target;
}

void Renderbuffer::bind()
{
    glBindRenderbuffer(_target, objectID);
}

void Renderbuffer::unbind()
{
	glBindRenderbuffer(_target, 0);
}



