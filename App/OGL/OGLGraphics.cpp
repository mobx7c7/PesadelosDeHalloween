/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-21
***********************************************************************/
#include "OGLGraphics.h"
#include "gl_includes.h"

OGLGraphics::OGLGraphics()
{
    canvas          = CanvasInstance::getInstance();
    effect          = EffectManager::getInstance()->getDefault();
    Window* window  = WindowManager::getInstance()->getDefaultWindow();
    res             = glm::vec2(window->getWidth(), window->getHeight());
    textRenderer    = OGLTextRenderer::getInstance();
    temp_reloadShaders();
}

OGLGraphics::~OGLGraphics()
{
    OGLTextRenderer::destroyInstance();
    delete solidShader;
}

void OGLGraphics::temp_reloadShaders()
{
    if(!solidShader)
    {
        solidShader = new Shader();
    }
    else
    {
        cout << "temp_reloadShaders()" << endl;
        solidShader->clear();
    }
    solidShader->loadShaderFile("res/Shaders/solid.vert.glsl", ShaderType::Vertex);
    solidShader->loadShaderFile("res/Shaders/solid.frag.glsl", ShaderType::Fragment);
    solidShader->link();
}

void OGLGraphics::clearFramebuffer(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OGLGraphics::setColor(float r, float g, float b, float a)
{
	glColor4f(r, g, b, a);
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;
}

void OGLGraphics::setFramebuffer(Framebuffer* framebuffer)
{
//    if(this->framebuffer != framebuffer)
//    {
//        if(framebuffer) // é framebuffer
//        {
//            framebuffer->bind();
//            res = glm::vec2(framebuffer->getWidth(), framebuffer->getHeight());
//        }
//        else
//        {
//            this->framebuffer->unbind();
//            Window* window = WindowManager::getInstance()->getDefaultWindow();
//            res = glm::vec2(window->getWidth(), window->getHeight());
//        }
//        this->framebuffer = framebuffer;
//    }

    if(!framebuffer)
    {
        if(this->framebuffer)
        {
            this->framebuffer->unbind();
            this->framebuffer = 0;
        }
        Window* window = WindowManager::getInstance()->getDefaultWindow();
        res = glm::vec2(window->getWidth(), window->getHeight());
    }
    else if(this->framebuffer)
    {
        if(this->framebuffer != framebuffer)
        {
            this->framebuffer = framebuffer;
            this->framebuffer->bind();
            res = glm::vec2(framebuffer->getWidth(), framebuffer->getHeight());
        }
    }
}

void OGLGraphics::setEffect(Effect* effect)
{
    if(this->effect != effect)
    {
        if(effect)
        {
            this->effect = effect;
        }
        else
        {
            this->effect = EffectManager::getInstance()->getDefault();
        }
    }
}

//void OGLGraphics::setFont(Font* font)
//{
//
//}
//
//void OGLGraphics::setTexture(Texture* texture)
//{
//
//}

void OGLGraphics::getPixel(int x, int y, float* pixel)
{
    glReadPixels(x, res.y-y, 1, 1, GL_RGBA, GL_FLOAT, pixel);
}

void OGLGraphics::drawText(string text, double x, double y)
{
    textRenderer->drawText(text, x, y, this);
}

void OGLGraphics::drawRect(double x, double y, double width, double height)
{
	using namespace glm;

//    m_src = ortho(0.0f, res.x, res.y, 0.0f, 0.0f, 1.0f); // sem framebuffer
    m_src = ortho(0.0f, res.x, 0.0f, res.y, 0.0f, 1.0f); // com framebuffer
    m_src = translate(m_src, vec3(x, y, 0));
    m_src = scale(m_src, vec3(width, height, 0));

    glViewport(0, 0, res.x, res.y);

    // Nota: solução para gl_fragCoord
//    y = (res.y - height) + (-1.0 * y);

    solidShader->bind();
    solidShader->setUniform4fv("color", 1, &color[0]);
    solidShader->setUniformMatrix4f("m_src", 1, &m_src[0][0]);
    solidShader->setUniform1f("rect[0].left",   (float)x);
    solidShader->setUniform1f("rect[0].top",    (float)y);
    solidShader->setUniform1f("rect[0].right",  (float)(x+width));
    solidShader->setUniform1f("rect[0].bottom", (float)(y+height));
    canvas->draw();
    solidShader->unbind();
}

void OGLGraphics::drawTexture(Texture* texture, float x, float y)
{
	drawTexture(texture,x,y,texture->getWidth(),texture->getHeight(),0,0,texture->getWidth(),texture->getHeight());
}

void OGLGraphics::drawTexture(Texture* texture, float srcx, float srcy, float srcw, float srch)
{
    drawTexture(texture,srcx,srcy,srcw,srch,0,0,texture->getWidth(),texture->getHeight());
}

void OGLGraphics::drawTexture(Texture* texture, float srcx, float srcy, float srcw, float srch, float dstx, float dsty, float dstw, float dsth)
{
    if(!texture) return;

	using namespace glm;

	int currentFramebuffer;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFramebuffer);

//     Não precisa ajustar novamente!
//    if(currentFramebuffer == lastFramebuffer)
//    {
//        return;
//    }

    // FIXME: Colocar em um método de checagem para framebuffer
    if(currentFramebuffer == 0) // framebuffer padrão
    {
        Window* window = WindowManager::getInstance()->getDefaultWindow();
        res     = vec2(window->getWidth(), window->getHeight());
        m_src   = ortho(0.0f, res.x, res.y, 0.0f, 0.0f, 1.0f); // sem framebuffer
    }
    else
    {
        int fbuf_width = 0, fbuf_height = 0;
        glGetFramebufferParameteriv(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, &fbuf_width);
        glGetFramebufferParameteriv(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, &fbuf_height);
        res     = vec2(fbuf_width, fbuf_height);
        m_src   = ortho(0.0f, res.x, 0.0f, res.y, 0.0f, 1.0f); // com framebuffer
    }

    m_src = translate(m_src, vec3(srcx, srcy, 0));
    m_src = scale(m_src, vec3(srcw, srch, 0));

    m_dst = mat4(1);
    m_dst = translate(m_dst, vec3(dstx, dsty, 0) / vec3(texture->getWidth(), texture->getHeight(), 1));
    m_dst = scale(m_dst, vec3(dstw, dsth, 0) / vec3(texture->getWidth(), texture->getHeight(), 1));

    glViewport(0, 0, res.x, res.y);
    glActiveTexture(GL_TEXTURE0);
    texture->bind();
        // FIXME: Remover efeito e substituir por programa shader básico
        effect->setOpacity(color[3]);
        effect->setSurfaceMatrix(m_src);
        effect->setTextureMatrix(m_dst);
        effect->bind();
        //canvas->draw();
        canvas->draw(effect->getShaderProgram());
        effect->unbind();
	texture->unbind();
}
