/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-16
***********************************************************************/
#include "Graphics.h"
#include "OGLGraphics.h"

Graphics* Graphics::instance = 0;

Graphics::Graphics(){}

Graphics::~Graphics(){}

Graphics* Graphics::getInstance()
{
	if(!instance) instance = new OGLGraphics();
	return instance;
}

void Graphics::destroyInstance()
{
	if(instance) delete instance;
}
