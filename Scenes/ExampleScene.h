/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-16
***********************************************************************/
#ifndef EXAMPLESCENE_H
#define EXAMPLESCENE_H

#include "App/Window.h"
#include "App/Serial.h"
#include "App/Renderer.h"
#include "Common/Scene.h"
#include "Common/Sprite.h"
#include "Common/AnimatedSprite.h"
#include "Common/Effect.h"
#include "Common/Mesh.h"
#include "GL/Texture.h"
#include "GL/Framebuffer.h"
#include "Common/Text.h"
#include "Common/Transition.h"
#include "Common/Button.h"
#include "Common/Blending.h"
#include "Common/Sound/Loader.h"
#include "Common/Sound/Manager.h"
#include "Common/Sound/Sampler.h"
#include "Characters/Jogador.h"
#include "Characters/Inimigo.h"
#include "Characters/Tiro.h"
#include "Characters/Drop.h"
#include "MusicGenerator.h"
#include "TextureSynth.h"

class ExampleScene : public Scene
{
    protected:

        static ExampleScene*    instance;

        vector<Drop*>           listaDrop;
        vector<Drop*>           listaInvetario;
        vector<Sound::Sampler*> sndsamples;
        vector<Texture*>        backgrounds;


        map<unsigned, Sound::Sampler*> sfx;

        TextureSynth*           textureSynth                = 0;
        bool                    mapa_gerar                  = false;

        bool                    background_mixar_ativo      = 0;
        float                   background_mixar_fator      = 0;
        int                     background_atual_a          = 0;
        int                     background_atual_b          = 1;
        int                     background_troca_prox       = 3;// na wave 1
        int                     background_troca_passo      = 3;// na wave 1

        int                     wndwidth                    = 0;
        int                     wndheight                   = 0;
        double                  mouseX                      = 0;
        double                  mouseY                      = 0;

        double                  multiplicador_tempo         = 1;

        bool                    mouseBotao1                 = false;
        bool                    pause                       = false;

        int                     wave_atual                  = 1;
        double                  wave_tempo                  = 0;
        double                  wave_intervalo              = 3;

        double                  tiro_tempo                  = 0;
        double                  tiro_intervalo              = 1;

        double                  spawn_intervalo             = 10;
        double                  spawn_tempo                 = 0;

        int                     padrao_inimigo_vel_atual    = 50;
        int                     padrao_inimigo_vel_incr     = 10;
        int                     padrao_inimigo_qtd_atual    = 5;
        int                     padrao_inimigo_qtd_incr     = 1;

        ExampleScene();
        ~ExampleScene();


        bool reiniciar = false;

        void limpaListaDrop();
        void reiniciarJogo();

    public:

        static ExampleScene*    getInstance();
        static void             destroyInstance();

        // Nota: Funções sobrescritas
        void                    process(double deltaTime);
        void                    render(Graphics* g);
        void                    mouseMoved(int x, int y);
        void                    mousePressed(int x, int y, int button);
        void                    mouseReleased(int x, int y, int button);
        void                    keyPressed(int key);
        void                    keyReleased(int key);
        void                    windowResized(int w, int h);

};

#endif // EXAMPLESCENE_H
