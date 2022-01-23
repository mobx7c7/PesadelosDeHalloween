/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-19
***********************************************************************/
#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "App/Graphics.h"
#include "Object.h"
#include "Transform.h"
#include "GL/Framebuffer.h"
#include <memory> // shared_ptr

class Drawable : public Object
{
	protected:

		Framebuffer2*       currentFramebuffer = 0;
		Framebuffer2*       sceneFramebuffer = 0;
		Transform2*         tfm;
		Drawable(std::string name, Object* parent);

	public:

		virtual             ~Drawable();
		Transform2&         getTransform();

		void                setFramebuffer(Framebuffer2* fbuf);
		Framebuffer2*       getFramebuffer();

		virtual void        process(double);
		virtual void        render(Graphics*);

		virtual void        keyPressed(int key);
		virtual void        keyReleased(int key);
		virtual void        mouseMoved(int x, int y);
		virtual void        mouseDragged(int x, int y, int button);
		virtual void        mousePressed(int x, int y, int button);
		virtual void        mouseReleased(int x, int y, int button);
		virtual void        windowResized(int w, int h);
};

typedef shared_ptr<Drawable> DrawablePtr;

#endif // DRAWABLE_H
