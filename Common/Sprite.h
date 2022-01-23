/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-19
***********************************************************************/
#ifndef SPRITE_H
#define SPRITE_H

#include "Drawable.h"
#include "GL/Texture.h"

class Sprite : public Drawable
{
protected:

    Texture*    texture;
    unsigned    tilew;
    unsigned    tileh;
    unsigned    tilex;
    unsigned    tiley;
    unsigned    sprw;
    unsigned    sprh;
    Sprite();

public:

    Sprite(Texture* texture, unsigned imgw, unsigned imgh, unsigned tilew, unsigned tileh);
    Sprite(Texture* texture, unsigned tilew, unsigned tileh);
    Sprite(Texture* texture);
    virtual ~Sprite();

    void            setTexturePtr(Texture*);

    virtual void    process(double);
    virtual void    render(Graphics*);

};

#endif // SPRITE_H
