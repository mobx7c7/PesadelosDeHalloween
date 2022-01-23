/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-19
***********************************************************************/
#include "Layer.h"
//#include "Effect.h"
//#include "Mesh.h"

/*

Layer::Layer(unsigned width, unsigned height, Layer* parent) : Drawable("Layer", 0)
{
	drawFramebuffer = new Framebuffer(width, height);
	copyFramebuffer = new Framebuffer(width, height);
	setParent(parent);

//	setWidth(width);
//	setHeight(height);

	Transform2& t = getTransform();
	t.width = width;
	t.height = height;

//	effects.push_back(EffectManager::getInstance()->get("Default"));
//	effects.push_back(EffectManager::getInstance()->get("Luma"));
	effects.push_back(EffectManager::getInstance()->get("Waves"));
}

Layer::~Layer()
{
	delete drawFramebuffer;
	delete copyFramebuffer;
	//FIXME: Ao remover, ajustar drawable pai para nenhum
	drawables.clear();
}

void Layer::addDrawable(Drawable* drawable)
{
	//FIXME: Ao adicionar novos objetos, ajustar drawable pai para este
	drawables.push_back(drawable);
}

Drawable* Layer::getDrawable(unsigned index)
{
	return drawables[index];
}

void Layer::setParent(Layer* parent)
{
	this->parent = parent;
}

Layer* Layer::getParent()
{
	return parent;
}

Framebuffer* Layer::getFramebuffer()
{
	return drawFramebuffer;
}

void Layer::process(double deltaTime)
{
	for(Drawable* drawable : drawables)
	{
		drawable->process(deltaTime);
	}
}

void Layer::render(Graphics* g)
{
    // Desenha objetos
    g->setFramebuffer(copyFramebuffer);
    g->clearFramebuffer(0.0f, 0.0f, 0.0f, 0.0f);

    for(Drawable* drawable : drawables)
    {
        // caso um objeto de um drawable invoque outro framebuffer...
        g->setFramebuffer(copyFramebuffer);
        g->setEffect(0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        drawable->render(g);
        glDisable(GL_BLEND);
    }

    // Aplica efeitos

    if(!effects.empty())
    {
        g->setFramebuffer(drawFramebuffer);
        g->clearFramebuffer(0.0f, 0.0f, 0.0f, 0.0f);

        for(Effect* selected : effects)
        {
            g->setFramebuffer(drawFramebuffer);
            g->setEffect(selected);
            g->drawTexture(copyFramebuffer->getTexture(), 0, 0);

            g->setFramebuffer(copyFramebuffer);
            g->drawTexture(drawFramebuffer->getTexture(), 0, 0);
        }
    }

    //*******************************************************

    // Desenha resultado final
    g->setFramebuffer(parent ? parent->getFramebuffer() : 0);
    g->setEffect(0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_ONE, GL_ONE);

    Transform2& t = getTransform();
    if(!effects.empty())
    {
        g->drawTexture(drawFramebuffer->getTexture(), t.posx, t.posy);
    }
    else
    {
        g->drawTexture(copyFramebuffer->getTexture(), t.posx, t.posy);
    }

    // NOTA: REMOVER "MESH.H" DEPOIS!
    //g->setEffect(0);
    //copyFramebuffer->getTexture()->bind();
    //OGLTestCube3D::getInstance()->draw();
    // copyFramebuffer->getTexture()->unbind();

    glDisable(GL_BLEND);
}















LayerPanel::LayerPanel() : AbstractDrawablePanel<Layer>("Layer panel")
{

}
LayerPanel::~LayerPanel()
{

}
void LayerPanel::process(double deltaTime)
{
	map<string, Layer*>::const_iterator it;
	for(it = elements.begin(); it != elements.end(); it++)
	{
		Layer* layer = it->second;
		layer->process(deltaTime);
	}
}
void LayerPanel::render(Graphics* g)
{
	map<string, Layer*>::iterator it;
	for(it = elements.begin(); it != elements.end(); it++)
	{
		Layer* layer = it->second;
		layer->render(g);
		//cout << "Camada: " << it->first << endl;
	}
	//cout << endl;
}


*/
