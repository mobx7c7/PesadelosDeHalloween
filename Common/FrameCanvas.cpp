/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-19
***********************************************************************/
#include "FrameCanvas.h"

FrameCanvas* FrameCanvas::instance = 0;

FrameCanvas::FrameCanvas()
{
    Window* window = WindowManager::getInstance()->getDefaultWindow();

    width   = window->getWidth();
    height  = window->getHeight();

    canvas  = Rect::getInstance();

	shader  = new Shader();
	shader->loadShaderFile("res\\plane.vert", ShaderType::Vertex);
	shader->loadShaderFile("res\\plane.frag", ShaderType::Fragment);
	shader->link();
}

FrameCanvas::~FrameCanvas()
{
	delete shader;
//	delete vbo;
//	delete ibo;
//	delete vao;
}

FrameCanvas* FrameCanvas::getInstance()
{
    if(!instance) instance = new FrameCanvas();
    return instance;
}

//void FrameCanvas::setFramebuffer(FrameBuffer* fbo)
//{
//    this->fbo = fbo;
//}

void FrameCanvas::setWidth(unsigned width)
{
    this->width = width;
}

void FrameCanvas::setHeight(unsigned height)
{
    this->height = height;
}

void FrameCanvas::display(Texture* texture, float x, float y)
{
    display(texture, x, y, texture->getWidth(), texture->getHeight(), 0, 0, texture->getWidth(), texture->getHeight());
}

void FrameCanvas::display(Texture* texture, float x, float y, float w, float h)
{
    //display(texture, x, y, w, h, 0, 0, w, h);
}

void FrameCanvas::display(Texture* texture, float srcx, float srcy, float srcw, float srch, float dstx, float dsty, float dstw, float dsth)
{
using namespace glm;

	vec2 fbo_res = vec2(width, height);
	mat4 m_src;
	mat4 m_dst;

//	if(fbo)
//		fbo_res = vec2(fbo->getWidth(), fbo->getHeight());
//	else
//		fbo_res = vec2(window->getWidth(), window->getHeight());

	texture->bind();
        shader->bind();

            //TODO: Colocar shader personalizado em sua própria classe;
            //TODO: Colocar todos os parâmetros do shader no bind();
            m_src = ortho(0.0f, fbo_res.x, fbo_res.y, 0.0f);
            m_src = translate(m_src, vec3(srcx, srcy, 0));
            m_src = scale(m_src, vec3(srcw, srch, 0));
            //m_dst = ortho(0.0f, srcw, srch, 0.0f);
            m_dst = mat4(1);
//            m_dst = translate(m_src, vec3(dstx/srcw, dsty/srch, 0));
//            m_dst = scale(m_src, vec3(dstw/srcw, dsth/srch, 0));
            shader->setUniformMatrix4f("m_src", 1, &m_src[0][0]);
            shader->setUniformMatrix4f("m_dst", 1, &m_dst[0][0]);
            shader->setUniform1i("texture", 0);

            canvas->draw();

        shader->unbind();
	texture->unbind();
}
