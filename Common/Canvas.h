/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-19
***********************************************************************/
#ifndef CANVAS_H
#define CANVAS_H

#include "gl_includes.h"
#include "GL/VertexBuffer.h"
#include "GL/VertexArray.h"
#include "GL/Shader.h"
#include "GL/Texture.h"

class CanvasInstance
{
private:

    static CanvasInstance* instance;

protected:

    CanvasInstance();
    virtual ~CanvasInstance();

public:

    static CanvasInstance* getInstance();
    static void            destroyInstance();

    virtual void draw() = 0;
    virtual void draw(Shader* shader) = 0;

};

class OGLCanvasInstance : public CanvasInstance
{
private:

    VertexArray     *vao;
    VertexBuffer    *vbo;
    VertexBuffer    *ibo;
    unsigned        vertexCoordLoc;
    unsigned        textureCoordLoc;
    unsigned        normalCoordLoc;
    unsigned        colorLoc;

public:

    OGLCanvasInstance();
    ~OGLCanvasInstance();
    unsigned        getVertexCoordLoc();
    unsigned        getTextureCoordLoc();
    unsigned        getNormalCoordLoc();
    unsigned        getColorLoc();
    void            draw();
    void            draw(Shader* shader);
};



//class CanvasTest1
//{
//private:
//    static CanvasTest1* instance;
//protected:
//    CanvasTest1();
//    ~CanvasTest1();
//public:
//    static CanvasTest1* getInstance();
//    void setFrame(Framebuffer*);
//    void setTexture(unsigned slot, Texture*);
//    void setEffect(Effect*); // muda só o fragment
//    void setX(unsigned value);
//    void setY(unsigned value);
//    void setWidth(unsigned value);
//    void setHeight(unsigned value);
//    void render();
//};

#endif // CANVAS_H
