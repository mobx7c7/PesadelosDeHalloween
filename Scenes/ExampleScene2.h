/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-16
***********************************************************************/
#ifndef EXAMPLESCENE2_H
#define EXAMPLESCENE2_H

#include "App/Renderer.h"
#include "Common/Sound/Sampler.h"
#include "Common/Transition.h"
#include "Common/Button.h"
#include "Common/Scene.h"
#include "Common/Mesh.h"
#include "GL/Texture.h"
#include "Scenes/ExampleScene.h"

class ExampleScene2 : public Scene
{
protected:

    static ExampleScene2*   instance;

    Sound::Sampler*         click           = 0;
    Effect*                 waves           = 0;
    Texture*                msg_atlas       = 0;
    Texture*                menu_bg         = 0;
    int                     wndwidth        = 0;
    int                     wndheight       = 0;

    Button*                 botao_jogar     = 0;
    Button*                 botao_sair      = 0;

    bool                    iniciar_jogo    = false;
    bool                    sair_jogo       = false;

    ExampleScene2();
    ~ExampleScene2();

public:

    static ExampleScene2*   getInstance();
    static void             destroyInstance();

    void    process(double deltaTime);
    void    render(Graphics* g);
    void    windowResized(int w, int h);

};


#endif // EXAMPLESCENE2_H
