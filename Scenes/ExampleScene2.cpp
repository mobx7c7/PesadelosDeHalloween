/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-16
***********************************************************************/
#include "ExampleScene2.h"

ExampleScene2* ExampleScene2::instance = 0;

ExampleScene2* ExampleScene2::getInstance()
{
    if(!instance) instance = new ExampleScene2();
    return instance;
}
void ExampleScene2::destroyInstance()
{
    if(instance) delete instance;
    instance = 0;
}

ExampleScene2::ExampleScene2() : Scene("Example scene 2")
{
    Window* window  = WindowManager::getInstance()->getDefaultWindow();
	wndwidth        = window->getWidth();
	wndheight       = window->getHeight();

	waves = EffectManager::getInstance()->get("Waves");

    TextureManager* textureMan = TextureManager::getInstance();
    textureMan->insert("msg_atlas", TextureLoader::getInstance()->loadFile("res//game//msg_atlas.png"));
    textureMan->insert("menu_bg", TextureLoader::getInstance()->loadFile("res//game//bg//menu_bg.jpg"));
    msg_atlas   = textureMan->get("msg_atlas");
    menu_bg     = textureMan->get("menu_bg");

    botao_jogar = new Button((wndwidth-170)/2, (wndheight-70)/2 + 130, 170, 70, 0);
    botao_sair  = new Button((wndwidth-105)/2, (wndheight-70)/2 + 200, 105, 70, 0);

    drawables.push_back(botao_jogar);
    drawables.push_back(botao_sair);

    Sound::Loader* sndloader = Sound::Loader::getInstance();

    sndloader->setCurrentPath("res//game//sounds//");
    sndloader->loadFileRAW("click.raw", 2, 22050, 16, true);

//    Sound::Manager* sndman  = Sound::Manager::getInstance();

    click = new Sound::Sampler("click");
    click->loadWave("click.raw");
    click->setGain(1);
    click->setMaxPolyphony(2);
//    sndman->insert(click);
}

ExampleScene2::~ExampleScene2()
{

}

void ExampleScene2::process(double deltaTime)
{
    Transition* t = Transition::getInstance();

    if(!t->isFading())
    {
        if(iniciar_jogo)
        {
            t->clearSceneSlotA();
            t->setSceneSlotB(ExampleScene::getInstance());
            t->start();
        }
        if(botao_jogar->isPressed() && !iniciar_jogo)
        {
            iniciar_jogo = true;
            click->play();
            t->start();
        }
        if(botao_sair->isPressed() && !sair_jogo)
        {
            sair_jogo = true;
            click->play();
            GraphicsRenderer::getInstance()->stop();
        }
    }
}

void ExampleScene2::render(Graphics* g)
{
    Framebuffer2* currentFbuf = getFramebuffer();
    glBindFramebuffer(GL_FRAMEBUFFER, currentFbuf ? currentFbuf->getObjectID() : 0);

    float x1, y1, w1, h1, x2, y2, w2, h2;

    g->setEffect(waves);

    g->setColor(0,0,0,1);
    g->drawTexture(menu_bg, 0,0,wndwidth,wndheight);

//    g->setColor(0.5f,0,0,1);
//    g->drawRect(0,0,wndwidth,wndheight);

    g->setEffect(0);

    x1 = (wndwidth-512)/2;
    y1 = (wndheight-256)/2;
    w1 = 512;
    h1 = 256;
    x2 = 0;
    y2 = 256;
    w2 = 512;
    h2 = 256;

    g->drawTexture(msg_atlas, x1, y1, w1, h1, x2, y2, w2, h2);

    if(!Transition::getInstance()->isFading())
    {
        x1 = (wndwidth-170)/2;
        y1 = (wndheight-70)/2 + 130;
        w1 = 170;
        h1 = 70;
        x2 = 0;
        y2 = 0;
        w2 = 170;
        h2 = 70;

        g->drawTexture(msg_atlas, x1, y1, w1, h1, x2, y2, w2, h2);

        x1 = (wndwidth-105)/2;
        y1 = (wndheight-70)/2 + 200;
        w1 = 105;
        h1 = 70;
        x2 = 180;
        y2 = 0;
        w2 = 105;
        h2 = 70;

        g->drawTexture(msg_atlas, x1, y1, w1, h1, x2, y2, w2, h2);
    }

    g->setEffect(0);

//    g->setEffect(0);
//    OGLTestCube3D::getInstance()->draw();
    Framebuffer2* parentFbuf = getParent() ? ((Drawable*)getParent())->getFramebuffer() : 0;
    glBindFramebuffer(GL_FRAMEBUFFER, parentFbuf ? parentFbuf->getObjectID() : 0);
}

void ExampleScene2::windowResized(int w, int h)
{
    Scene::windowResized(w, h);

    wndwidth    = w;
    wndheight   = h;

    Transform2& t1 = botao_jogar->getTransform();
    t1.posx = (wndwidth-t1.width)/2;
    t1.posy = (wndheight-t1.height)/2 + 130;

    Transform2& t2 = botao_sair->getTransform();
    t2.posx = (wndwidth-t2.width)/2;
    t2.posy = (wndheight-t2.height)/2 + 200;
}
