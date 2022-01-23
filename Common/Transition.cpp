/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-06-05
***********************************************************************/
#include "Transition.h"

Transition* Transition::instance = 0;

Transition::Transition() : Drawable("Transition", 0)
{
	windowMan = WindowManager::getInstance();

	//window_w = 512;
	//window_h = 512;
	window_w    = windowMan->getDefaultWindow()->getWidth();
	window_h    = windowMan->getDefaultWindow()->getHeight();

	sceneTexA   = new Texture(window_w, window_h, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	sceneTexB   = new Texture(window_w, window_h, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	sceneTexC   = new Texture(window_w, window_h, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	fbuf = new Framebuffer2(GL_FRAMEBUFFER, window_w, window_h);
	fbuf->bind();
	fbuf->attachTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, sceneTexA);
	fbuf->attachTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, sceneTexB);
	fbuf->attachTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, sceneTexC);
	fbuf->unbind();

	prog = new Shader();
	prog->loadShaderFile("res\\Shaders\\transition.vert.glsl", ShaderType::Vertex);
	prog->loadShaderFile("res\\Shaders\\transition.frag.glsl", ShaderType::Fragment);
	prog->link();

	this->setFramebuffer(fbuf);
}

Transition::~Transition()
{
	delete sceneTexA;
	delete sceneTexB;
	delete sceneTexC;
	delete fbuf;
	delete prog;
//	if(sceneA) delete sceneA;
//	if(sceneB) delete sceneB;
}

Transition* Transition::getInstance()
{
    if(!instance) instance = new Transition();
    return instance;
}

void Transition::destroyInstance()
{
    if(instance) delete instance;
    instance = 0;
}

void Transition::setSceneSlotA(Scene* scene)
{
	if(!scene) return;
	sceneA = scene;
	scene->setParent(this);
}

void Transition::setSceneSlotB(Scene* scene)
{
	if(!scene) return;
	sceneB = scene;
	scene->setParent(this);
}

void Transition::clearSceneSlotA()
{
	if(!sceneA) return;
//	delete sceneA;
	sceneA = 0;
}

void Transition::clearSceneSlotB()
{
	if(!sceneB) return;
//	delete sceneB;
	sceneB = 0;
}

void Transition::process(double deltaTime)
{
	if(sceneA)
	{
		sceneA->process(deltaTime);
	}
	if(sceneB)
	{
		sceneB->process(deltaTime);
	}

    if(fading)
    {
        // Nota: valor de tempo
        if(fader_delay > 0.5)
        {
            // Nota: valor de progresso
            if(fader_ctrl > 1.0)
            {
                Scene* tmp  = sceneB;
                sceneB      = sceneA;
                sceneA      = tmp;
                fading      = false;
                fader_ctrl  = 0;
                fader_delay = 0;
            }
            else
            {
                fader_ctrl += deltaTime * 0.5;  // 2 segundos
            }
        }
        else
        {
            fader_delay += deltaTime;
        }
    }
}

void Transition::start()
{
    fading = true;
}

bool Transition::isFading()
{
    return fading;
}

void Transition::render(Graphics* g)
{
	// Significados targets framebuffer:
	// GL_DRAW_FRAMEBUFFER: somente comandos de escrita estarão disponíveis
	// GL_READ_FRAMEBUFFER: somente comandos de leitura estarão disponíveis
	// GL_FRAMEBUFFER     : ambos comandos de leitura e escrita estarão disponíveis.

	// Nota: Evita mudança de endereço durante a renderização.
	Scene* currentSceneA = sceneA;
	Scene* currentSceneB = sceneB;

	//------------------------------------------------------------//

	glBindFramebuffer(GL_FRAMEBUFFER, fbuf->getObjectID());
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(!glIsEnabled(GL_BLEND))
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

	if(sceneA)
	{
		sceneA->render(g);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, fbuf->getObjectID());
	glDrawBuffer(GL_COLOR_ATTACHMENT1);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!glIsEnabled(GL_BLEND))
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

	if(sceneB)
	{
		sceneB->render(g);
	}

	//------------------------------------------------------------//

    if(true)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbuf->getObjectID());
        glDrawBuffer(GL_COLOR_ATTACHMENT2);
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(sceneTexA->getTarget(), sceneTexA->getObjectID());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(sceneTexB->getTarget(), sceneTexB->getObjectID());

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
        prog->setUniform2f("resolution", window_w, window_h);
        prog->setUniform1f("time", glfwGetTime());
        prog->setUniform1f("fader", 0.5+0.5*cos(fader_ctrl * 3.14159265359 + 3.14159265359));
        //OGLCanvasInstance::getInstance()->draw();
        OGLCanvasInstance::getInstance()->draw(prog);
        prog->unbind();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
//    // Nota: Teste de cópia entre texturas usando "blitFramebuffer()"
//    if(false)
//    {
//        glBindFramebuffer(GL_FRAMEBUFFER, fbuf->getObjectID());
//        glDrawBuffer(GL_COLOR_ATTACHMENT2);
//        glClearColor(0,0,0,1);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        int meio_w = window_w/2;
//        // Sintaxe: glBlitFramebuffer(srcx1, srcy1, srcx2, srcy2, dstx1, dsty1, dstx2, dsty2, flag, filtro)
//        glReadBuffer(GL_COLOR_ATTACHMENT0);
//        glBlitFramebuffer(0, 0, window_w, window_h, meio_w*0.0f, 0, meio_w*1.0f, window_h, GL_COLOR_BUFFER_BIT, GL_LINEAR);
//        glReadBuffer(GL_COLOR_ATTACHMENT1);
//        glBlitFramebuffer(0, 0, window_w, window_h, meio_w*1.0f, 0, meio_w*2.0f, window_h, GL_COLOR_BUFFER_BIT, GL_LINEAR);
//    }

	//------------------------------------------------------------//

    // Nota: Restaura framebuffer anterior, relacionado ao pai
	Framebuffer2* parentFbuf = getParent() ? ((Drawable*)getParent())->getFramebuffer() : 0;
	glBindFramebuffer(GL_FRAMEBUFFER, parentFbuf ? parentFbuf->getObjectID() : 0);
	glActiveTexture(GL_TEXTURE0);
	g->drawTexture(sceneTexC, 0,0);
}

void Transition::keyPressed(int key)
{
    if(sceneA) sceneA->keyPressed(key);

    if(key == GLFW_KEY_F1)
    {
        prog->clear();
        prog->loadShaderFile("res\\Shaders\\transition.vert.glsl", ShaderType::Vertex);
        prog->loadShaderFile("res\\Shaders\\transition.frag.glsl", ShaderType::Fragment);
        prog->link();
    }
    else if(key == GLFW_KEY_F2)
    {
        start();
    }
}

void Transition::keyReleased(int key)
{
    if(sceneA) sceneA->keyReleased(key);
}

void Transition::mouseMoved(int x, int y)
{
    if(sceneA) sceneA->mouseMoved(x,y);

//    fader_ctrl = (float)x/window_w;
}

void Transition::mouseDragged(int x, int y, int button)
{
    if(sceneA) sceneA->mouseDragged(x,y,button);
}

void Transition::mousePressed(int x, int y, int button)
{
    if(sceneA) sceneA->mousePressed(x,y,button);
}

void Transition::mouseReleased(int x, int y, int button)
{
    if(sceneA) sceneA->mouseReleased(x,y,button);
}

void Transition::windowResized(int w, int h)
{
    if(sceneA) sceneA->windowResized(w,h);
    if(sceneB) sceneB->windowResized(w,h);

    // Nota: evita problema de concorrência, acho...
    Texture*        oldSceneTexA    = sceneTexA;
    Texture*        oldSceneTexB    = sceneTexB;
    Texture*        oldSceneTexC    = sceneTexC;
    Framebuffer2*   oldFbuf         = fbuf;
    int             oldw            = window_w;
    int             oldh            = window_h;

    //FIXME: deixar de deletar objetos para atualizar atributos!
	sceneTexA   = new Texture(w, h, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	sceneTexB   = new Texture(w, h, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	sceneTexC   = new Texture(w, h, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	fbuf        = new Framebuffer2(GL_FRAMEBUFFER, w, h);
	fbuf->bind();
	fbuf->attachTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, sceneTexA);
	fbuf->attachTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, sceneTexB);
	fbuf->attachTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, sceneTexC);
	fbuf->unbind();

	this->setFramebuffer(fbuf);

    window_w  = w;
	window_h  = h;
	delete oldFbuf;
	delete oldSceneTexA;
	delete oldSceneTexB;
	delete oldSceneTexC;
}
