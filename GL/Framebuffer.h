/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2014-11-28
***********************************************************************/
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "GLObject.h"
#include "Texture.h"
#include "Renderbuffer.h"

class Framebuffer : public GLObject
{
//    private:
//
//        static Framebuffer* placeholder;

	protected:

		Texture*        _texture        = 0;
		Renderbuffer*   _renderbuffer   = 0;
		unsigned        _target         = 0;
		unsigned        _width          = 0;
		unsigned        _height         = 0;
		unsigned        _attachment     = 0;
//        Framebuffer();

	public:
//
		Framebuffer(unsigned width, unsigned height, unsigned textureFormat, unsigned pixelFormat, DataType dataType);
		Framebuffer(unsigned width, unsigned height);

		virtual             ~Framebuffer();
//		static Framebuffer* getPlaceholder();
		Texture*            getTexture() const;
		Renderbuffer*       getRenderbuffer() const;
		unsigned            getWidth();
		unsigned            getHeight();
		unsigned            getAttachment();
		unsigned            getTarget();
		void                bind();
		void                unbind();

		Framebuffer()
		{

		}
		Framebuffer(unsigned target)
		{
			glGenFramebuffers(1, &objectID);
			_target = target;
		}
		void attachTexture(Texture* texture, int attachment_point)
		{
			//bind();
			glFramebufferTexture2D(_target, attachment_point, texture->getTarget(), texture->getObjectID(), 0);
			//unbind();
		}
		void attachRenderbuffer(Renderbuffer* rb, int slot)
		{
			//bind();
			glFramebufferRenderbuffer(_target, slot, rb->getTarget(), rb->getObjectID());
			//unbind();
		}
		int getStatus()
		{
			bind();
			int status = glCheckFramebufferStatus(_target);
			unbind();
			return status;
		}
};

class Framebuffer2 : public GLObject
{
    protected:

        unsigned _target;

    public:

		Framebuffer2(unsigned target, unsigned default_width, unsigned default_height) : _target(target)
		{
			glGenFramebuffers(1, &objectID);
			bind();
            glFramebufferParameteri(target, GL_FRAMEBUFFER_DEFAULT_WIDTH, default_width);
            glFramebufferParameteri(target, GL_FRAMEBUFFER_DEFAULT_HEIGHT, default_height);
            unbind();
		}
		~Framebuffer2()
		{
            glDeleteFramebuffers(1, &objectID);
		}
		int getDefaultWidth()
		{
            int default_width;
            bind();
		    glGetFramebufferParameteriv(_target, GL_FRAMEBUFFER_DEFAULT_WIDTH, &default_width);
		    unbind();
		    return default_width;
		}
		int getDefaultHeight()
		{
		    int default_height;
		    bind();
		    glGetFramebufferParameteriv(_target, GL_FRAMEBUFFER_DEFAULT_HEIGHT, &default_height);
		    unbind();
		    return default_height;
		}
		void attachTexture(int target, int slot, Texture* texture)
		{
//			bind();
			glFramebufferTexture2D(target, slot, texture->getTarget(), texture->getObjectID(), 0); // 0 = nivel mipmap
//			unbind();
		}
		void attachRenderbuffer(int target, int slot, Renderbuffer* rbuf) // GL_DEPTH_
		{
//			bind();
			glFramebufferRenderbuffer(target, slot, rbuf->getTarget(), rbuf->getObjectID());
//			unbind();
		}
//		int getTarget()
//		{
//		    return _target;
//		}
//		int getStatus()
//		{
////			bind();
////			int status = glCheckFramebufferStatus(_target);
////			unbind();
////			return status;
//            return glCheckFramebufferStatus(_target)
//		}
		void bind()
        {
            glBindFramebuffer(_target, objectID);
        }
        void unbind()
        {
            glBindFramebuffer(_target, 0);
        }
};

//class FrameBufferManager
//{
//    static FrameBufferManager* instance
//};

#endif // FRAMEBUFFER_H
