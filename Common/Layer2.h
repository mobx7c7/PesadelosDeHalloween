/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-06-07
***********************************************************************/
#ifndef LAYER2_H
#define LAYER2_H

#include "Common\Canvas.h"
#include "Scene.h"
#include "GL\Shader.h"
#include "GL\Framebuffer.h"
#include "GL\Texture.h"
#include <vector>

class Layer2;

typedef std::map<unsigned, Drawable&>             LayerMap;
typedef std::map<unsigned, Drawable&>::iterator   LayerMapIterator;
typedef std::pair<unsigned, Drawable&>            LayerMapPair;

class Layer2 : public Drawable
{
    protected:

        Shader*         prog = 0;
        Framebuffer2*   fbuf = 0;
        Texture*        tex_input = 0;
        Texture*        tex_output = 0;
        Texture*        tex_shading = 0;
        Drawable*       dw = 0;

        int width, height;

    public:

        Layer2(Object* parent) : Drawable("Layer", parent)
        {
            WindowManager* windowMan = WindowManager::getInstance();

            width = 1024;//windowMan->getDefaultWindow()->getWidth();
            height = 512;//windowMan->getDefaultWindow()->getHeight();

            tex_input = new Texture(width, height, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 0);
            tex_output = new Texture(width, height, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 0);
            tex_shading = new Texture(width, height, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 0);

            fbuf = new Framebuffer2(GL_DRAW_FRAMEBUFFER, width, height);
            fbuf->bind();
            fbuf->attachTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex_input);
            fbuf->attachTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, tex_output);
            fbuf->attachTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, tex_shading);
            fbuf->unbind();

            prog = new Shader();
            prog->loadShaderFile("res\\Shaders\\transition.vert.glsl", ShaderType::Vertex);
            prog->loadShaderFile("res\\Shaders\\transition.frag.glsl", ShaderType::Fragment);
            prog->link();

            setFramebuffer(fbuf);
        }

        Layer2(Drawable* scene, Object* parent) : Layer2(parent)
        {
            dw = scene;
            if(dw) dw->setParent(this);
        }

        virtual ~Layer2()
        {
            delete tex_input;
            delete tex_output;
            delete tex_shading;
            delete fbuf;
            delete prog;
        }

        virtual void process(double deltaTime)
        {
            if(dw)
            {
                dw->process(deltaTime);
            }
        }

        virtual void render(Graphics* g)
        {
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbuf->getObjectID());

            if(true)
            {
                glDrawBuffer(GL_COLOR_ATTACHMENT0); // tex_input
                glClearColor(1,0,0,0);
                glClear(GL_COLOR_BUFFER_BIT);
                if(dw)
                {
                    dw->render(g);
                }
            }

            if(true) // Nota: espaço para processar efeitos
            {
                glDrawBuffer(GL_COLOR_ATTACHMENT1); // tex_output
                glClearColor(0,0,0,1);
                glClear(GL_COLOR_BUFFER_BIT);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(tex_input->getTarget(), tex_input->getObjectID());
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(tex_input->getTarget(), tex_input->getObjectID());

                using namespace glm;
                mat4 m_src;
                mat4 m_dst;

                m_src = ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 1.0f);
                m_src = scale(m_src, vec3((float)width, (float)height, 0));

                m_dst = mat4(1);

                prog->bind();
                prog->setUniformMatrix4f("m_src", 1, &m_src[0][0]);
                prog->setUniformMatrix4f("m_dst", 1, &m_dst[0][0]);
                prog->setUniform1i("frameA", 0);
                prog->setUniform1i("frameB", 1);

                static float fader = 0;
                fader = fmod(fader+0.01, 1.0f);
                prog->setUniform1f("fader", 0.5+0.5*sin(fader * 6.28318530718));

                glViewport(0, 0, width, height);

                OGLCanvasInstance::getInstance()->draw();

                glUseProgram(0);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, 0);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, 0);
            }

            Framebuffer2* parentFbuf = getParent() ? ((Drawable*)getParent())->getFramebuffer() : 0;
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, parentFbuf ? parentFbuf->getObjectID() : 0);

            g->drawTexture(tex_input,0,0);
        }
};


class Composition : public Layer2
{
protected:

    LayerMap        layers;

public:

    Composition() : Layer2(0){}


//        void insert(Drawable* scene)
//        {
//            if(!scene) return;
//            scene->setParent(this);
//            layers.insert(LayerMapPair(scene->getIdent(), *scene));
//        }

//        void process(double deltaTime)
//        {
//            LayerMapIterator layer;
//            for(layer = layers.begin(); layer != layers.end(); layer++)
//            {
//                layer->second.process(deltaTime);
//            }
//        }
//        void render(Graphics* g)
//        {
//            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbuf->getObjectID());
//            glDrawBuffer(GL_COLOR_ATTACHMENT0);
//            glClearColor(0,0,0,0);
//            glClear(GL_COLOR_BUFFER_BIT);
//
//            LayerMapIterator layer;
//            for(layer = layers.begin(); layer != layers.end(); layer++)
//            {
//                 layer->second.render(g);
//            }
//
//            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
//
//            g->drawTexture(tex_input,10,10);
//        }
};

#endif // LAYER2_H
