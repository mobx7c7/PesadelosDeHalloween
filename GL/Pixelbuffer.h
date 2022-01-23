/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-06-05
***********************************************************************/
#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include "GLObject.h"
#include "gl_includes.h"

class Pixelbuffer : public GLObject
{
    public:
        Pixelbuffer()
        {
            glGenBuffers(1, &objectID);
        }
        virtual ~Pixelbuffer()
        {
            glDeleteBuffers(1, &objectID);
        }
        void bind()
        {
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, objectID);
            //glBindBuffer(GL_PIXEL_PACK_BUFFER, &objectID);
        }
        void unbind()
        {
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
            //glBindBuffer(GL_PIXEL_PACK_BUFFER, 0)
        }
};

#endif // PIXELBUFFER_H
