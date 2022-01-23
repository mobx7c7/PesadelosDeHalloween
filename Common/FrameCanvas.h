/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-19
***********************************************************************/
#ifndef FRAMECANVAS_H
#define FRAMECANVAS_H

#include "App/Window.h"
#include "GL/Shader.h"
#include "GL/Texture.h"
#include "GL/FrameBuffer.h"
#include "Common/Rect.h"

class FrameCanvas
{
private:

    static FrameCanvas* instance;
    FrameCanvas();
    ~FrameCanvas();

    Shader          *shader;
    FrameBuffer*    *framebuffer;
    Rect            *canvas;

    unsigned width, height;

public:

    static FrameCanvas* getInstance();
//    void                setFramebuffer(FrameBuffer*);
    void                setWidth(unsigned);
    void                setHeight(unsigned);
    void                display(Texture*, float, float);
    void                display(Texture*, float, float, float, float);
    void                display(Texture*, float, float, float, float, float, float);
    void                display(Texture*, float, float, float, float, float, float, float, float);
};

#endif // FRAMECANVAS_H
