/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-03
***********************************************************************/
#ifndef EXAMPLESCENE3_H
#define EXAMPLESCENE3_H

#include "GL/Texture.h"
#include "Common/Sprite.h"
#include "Common/Scene.h"
#include "Common/Text.h"

class ExampleScene3 : public Scene
{
protected:

    Texture*    backimg;
    Sprite*     backspr;

    unsigned janela_largura;
    unsigned wndheight;

public:

    ExampleScene3();
    ~ExampleScene3();

    void    process(double deltaTime);
    void    render(Graphics* g);

    void    windowResized(int w, int h);
};

#endif // EXAMPLESCENE3_H
