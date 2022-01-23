/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-06-07
***********************************************************************/
#include "Blending.h"

Blending* Blending::instance = 0;

Blending::Blending() : Drawable("Blending", 0)
{
	windowMan = WindowManager::getInstance();

	window_w    = windowMan->getDefaultWindow()->getWidth();
	window_h    = windowMan->getDefaultWindow()->getHeight();

	prog = new Shader();
	prog->loadShaderFile("res\\Shaders\\blending.vert.glsl", ShaderType::Vertex);
	prog->loadShaderFile("res\\Shaders\\blending.frag.glsl", ShaderType::Fragment);
	prog->link();
}

Blending::~Blending()
{
	delete prog;
}

Blending* Blending::getInstance()
{
    if(!instance) instance = new Blending();
    return instance;
}

void Blending::destroyInstance()
{
    if(instance) delete instance;
    instance = 0;
}

void Blending::setFrameA(Texture* frame)
{
	if(!frame) return;
	frameA = frame;
}

void Blending::setFrameB(Texture* frame)
{
	if(!frame) return;
	frameB = frame;
}

void Blending::clearFrameA()
{
	if(!frameA) return;
	frameA = 0;
}

void Blending::clearFrameB()
{
	if(!frameB) return;
	frameB = 0;
}

void Blending::setMix(float mix)
{
    this->mix = mix;
}

void Blending::render(Graphics* g)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(frameA->getTarget(), frameA->getObjectID());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(frameB->getTarget(), frameB->getObjectID());

    glViewport(0, 0, window_w, window_h);

    using namespace glm;
    mat4 m_src;
    mat4 m_dst;

    m_src = ortho(0.0f, (float)window_w, 0.0f, (float)window_h, 0.0f, 1.0f); // com framebuffer
    m_src = translate(m_src, vec3(0, 0, 0));
    m_src = scale(m_src, vec3((float)window_w, (float)window_h, 0));
    m_dst = mat4(1);

    prog->bind();
        prog->setUniformMatrix4f("m_src", 1, &m_src[0][0]);
        prog->setUniformMatrix4f("m_dst", 1, &m_dst[0][0]);
        prog->setUniform1i("frameA", 0);
        prog->setUniform1i("frameB", 1);
        prog->setUniform1f("mix", mix);
        OGLCanvasInstance::getInstance()->draw(prog);
    prog->unbind();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(frameA->getTarget(), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(frameB->getTarget(), 0);
}

void Blending::keyPressed(int key)
{
    if(key == GLFW_KEY_F3)
    {
        prog->clear();
        prog->loadShaderFile("res\\Shaders\\blending.vert.glsl", ShaderType::Vertex);
        prog->loadShaderFile("res\\Shaders\\blending.frag.glsl", ShaderType::Fragment);
        prog->link();
    }
}

void Blending::windowResized(int w, int h)
{
    window_w  = w;
	window_h  = h;
}
