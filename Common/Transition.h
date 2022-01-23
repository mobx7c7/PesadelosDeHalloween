/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-06-05
***********************************************************************/
#ifndef TRANSITION_H
#define TRANSITION_H

#include "GL\Texture.h"
#include "GL\Framebuffer.h"
#include "Common\Drawable.h"
#include "Common\Scene.h"
#include "Common\Canvas.h"
#include "App\Window.h"

class Transition : public Drawable
{
    protected:

        static Transition* instance;

        WindowManager*  windowMan;

        bool            fading      = false;
        float           fader_ctrl  = 0;
        float           fader_delay = 0;
        int             window_w    = 0;
        int             window_h    = 0;
        Scene*          sceneA      = 0;
        Scene*          sceneB      = 0;
        Texture*        sceneTexA   = 0;
        Texture*        sceneTexB   = 0;
        Texture*        sceneTexC   = 0;
        Framebuffer2*   fbuf        = 0;
        Shader*         prog        = 0;

        Transition();

        ~Transition();

    public:

        static Transition* getInstance();

        static void destroyInstance();

        void setSceneSlotA(Scene* scene);

        void setSceneSlotB(Scene* scene);

        void clearSceneSlotA();

        void clearSceneSlotB();

//        void setInputState(bool);
//
//        void setProgress(double progress);

        void process(double deltaTime);

        void render(Graphics* g);

        void start();

        bool isFading();

        //--------------------------------------------------//

        void keyPressed(int key);

        void keyReleased(int key);

        void mouseMoved(int x, int y);

        void mouseDragged(int x, int y, int button);

        void mousePressed(int x, int y, int button);

        void mouseReleased(int x, int y, int button);

        void windowResized(int w, int h);
};

#endif // TRANSITION_H
