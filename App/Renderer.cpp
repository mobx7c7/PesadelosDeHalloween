/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-13
***********************************************************************/
#include "Renderer.h"
#include "OGL/OGLRenderer.h"

GraphicsRenderer* GraphicsRenderer::instance = 0;

GraphicsRenderer::GraphicsRenderer(){}

GraphicsRenderer::~GraphicsRenderer(){}

GraphicsRenderer* GraphicsRenderer::getInstance()
{
	if(!instance) instance = new OGLRenderer();
	return instance;
}
void GraphicsRenderer::destroyInstance()
{
	if(instance) delete instance;
}
