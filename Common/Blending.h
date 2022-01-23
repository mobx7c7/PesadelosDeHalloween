/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-06-07
***********************************************************************/
#ifndef BLENDING_H
#define BLENDING_H

#include "App\Window.h"
#include "GL\Texture.h"
#include "Common\Drawable.h"
#include "Common\Canvas.h"

class Blending : public Drawable
{
    protected:

        static Blending* instance;

        WindowManager*  windowMan;
        int             window_w    = 0;
        int             window_h    = 0;
        Texture*        frameA      = 0;
        Texture*        frameB      = 0;
        float           mix         = 0.5f;
        Shader*         prog        = 0;

        Blending();

        ~Blending();

    public:

        static Blending* getInstance();

        static void destroyInstance();

        void setFrameA(Texture*);

        void setFrameB(Texture*);

        void clearFrameA();

        void clearFrameB();

        void setMix(float mix);

        void render(Graphics* g);

        //--------------------------------------------------//

        void keyPressed(int key);

        void windowResized(int w, int h);
};

#endif // BLENDING_H
