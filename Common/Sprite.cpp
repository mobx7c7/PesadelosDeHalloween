/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-19
***********************************************************************/
#include "Sprite.h"

Sprite::Sprite(Texture* texture, unsigned imgw, unsigned imgh, unsigned tilew, unsigned tileh) :
    Drawable("Sprite", 0),
    texture(texture),
    tilex(0),
	tiley(0),
    tilew(tilew),
	tileh(tileh),
    sprw(imgw/tilew),
    sprh(imgh/tileh)
{
//    width   = sprw;
//	height  = sprh;

    Transform2& t = getTransform();
    t.width   = sprw;
	t.height  = sprh;
}

Sprite::Sprite(Texture* texture, unsigned tilew, unsigned tileh) :
    Sprite(texture, texture->getWidth(), texture->getHeight(), tilew, tileh){}

Sprite::Sprite(Texture* texture) :
    Sprite(texture, texture->getWidth(), texture->getHeight(), 1, 1){}

Sprite::Sprite() : Drawable("Sprite", 0){}

Sprite::~Sprite(){}

void Sprite::setTexturePtr(Texture* texture)
{
    this->texture = texture;
}

void Sprite::process(double deltaTime){}

void Sprite::render(Graphics* g)
{
    Transform2& t = getTransform();
    g->drawTexture(texture,
                   t.posx,
                   t.posy,
                   t.width,
                   t.height,
                   t.width * tilex,
                   t.height * tiley,
                   texture->getWidth(),
                   texture->getHeight());
}



