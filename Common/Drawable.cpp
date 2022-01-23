/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-19
***********************************************************************/
#include "Drawable.h"

Drawable::Drawable(std::string name, Object* parent) :
	Object(name, parent),
	tfm(new Transform2())
{

}

Drawable::~Drawable()
{
	delete tfm;
}

Transform2& Drawable::getTransform()
{
	return *tfm;
}

void Drawable::setFramebuffer(Framebuffer2* fbuf)
{
	if(fbuf)
	{
		currentFramebuffer = fbuf;
	}
	else
	{
		currentFramebuffer = sceneFramebuffer;
	}
}
Framebuffer2* Drawable::getFramebuffer()
{
	if(currentFramebuffer)
	{
		return currentFramebuffer;
	}
	else if(getParent())
	{
		return ((Drawable*)getParent())->getFramebuffer();
	}
	else
	{
		return 0;
	}
}

void Drawable::process(double deltaTime) {}

void Drawable::render(Graphics* g) {}

void Drawable::keyPressed(int key) {}

void Drawable::keyReleased(int key) {}

void Drawable::mouseMoved(int x, int y) {}

void Drawable::mouseDragged(int x, int y, int button) {}

void Drawable::mousePressed(int x, int y, int button) {}

void Drawable::mouseReleased(int x, int y, int button) {}

void Drawable::windowResized(int w, int h) {}

