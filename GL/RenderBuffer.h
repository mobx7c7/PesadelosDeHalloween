/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2014-11-28
***********************************************************************/
#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include "GLObject.h"

class Renderbuffer : public GLObject
{
	private:

		static Renderbuffer* placeholder;

	protected:

		unsigned    _width  = 0;
		unsigned    _height = 0;
		unsigned    _target = 0;


	public:

		Renderbuffer(unsigned width, unsigned height, unsigned internalFormat);
		Renderbuffer(unsigned width, unsigned height);
		Renderbuffer();
		virtual ~Renderbuffer();

//		static Renderbuffer*    getPlaceholder();
		unsigned                getWidth();
		unsigned                getHeight();
		unsigned                getTarget();
		void                    bind();
		void                    unbind();
};

#endif // RENDERBUFFER_H
