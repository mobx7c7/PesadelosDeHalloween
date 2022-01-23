/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-03
***********************************************************************/
#include "ExampleScene3.h"

ExampleScene3::ExampleScene3() : Scene("Example scene 3")
{
    Window* window  = WindowManager::getInstance()->getDefaultWindow();
	janela_largura        = window->getWidth();
	wndheight       = window->getHeight();

//	TextureManager* textureMan = TextureManager::getInstance();
//    textureMan->insert("background2", TextureLoader::getInstance()->loadFile("res//game//bg//cenario1.jpg"));

//    backimg = textureMan->get("background2");
//	backspr = new Sprite(backimg);


//    backspr->getTransform().width  = wndwidth;
//	backspr->getTransform().height = wndheight;
}

ExampleScene3::~ExampleScene3()
{
    delete backspr;
    delete backimg;
}

void ExampleScene3::process(double deltaTime)
{

}

void ExampleScene3::render(Graphics* g)
{
    Framebuffer2* selectedFbuf = getFramebuffer();
    glBindFramebuffer(GL_FRAMEBUFFER, selectedFbuf ? selectedFbuf->getObjectID() : 0);

//    backspr->render(g);

//    OGLConsole2* console = OGLConsole2::getInstance();
//
//    //console->print("Hello\nWorld\nFrom\nSky!");
//
//    console->print("When an unconfident young woman "
//                   "is cursed with an old body by a spiteful witch, "
//                   "her only chance of breaking the spell lies with a "
//                   "self-indulgent yet insecure young wizard "
//                   "and his companions in his legged, walking home.");
//
//    console->draw(0.0f, 0.0f, 1.0f, 1.0f);

    OGLTextRenderer* textRenderer = OGLTextRenderer::getInstance();
    static int i=0;
    stringstream ss;
    ss << "É fus-roh-dah\n e não fui rodar!!! " << i;
    textRenderer->drawText(ss.str(), 200, 200, g);
    i++;

    Framebuffer2* parentFbuf = getParent() ? ((Drawable*)getParent())->getFramebuffer() : 0;
    glBindFramebuffer(GL_FRAMEBUFFER, parentFbuf ? parentFbuf->getObjectID() : 0);
}

void ExampleScene3::windowResized(int w, int h)
{
    Scene::windowResized(w, h);
    janela_largura    = w;
    wndheight   = h;

	backspr->getTransform().width  = janela_largura;
	backspr->getTransform().height = wndheight;
}
