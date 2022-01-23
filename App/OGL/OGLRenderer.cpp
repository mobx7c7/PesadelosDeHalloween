/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-21
***********************************************************************/
#include "OGLRenderer.h"
#include "App/Monitor.h"
#include "App/Sound.h"
#include "GL/Texture.h" // TextureManager
#include "Common/Canvas.h"
#include "Common/Transition.h"
#include "Common/Blending.h"
#include "Common/Text.h"
#include "Common/Layer2.h"

#include <thread>
#include <chrono>
#include <sstream>
#include "Scenes/ExampleScene.h"
#include "Scenes/ExampleScene2.h"
#include "Scenes/ExampleScene3.h"

#define TITULO "Pesadelos de halloween" // OpenGL

void OGLRenderer::mouseCursorCallback(GLFWwindow* window, double x, double y)
{
    OGLRenderer* app = (OGLRenderer*)glfwGetWindowUserPointer(window);
    if(!app->mainScene) return;

    app->mainScene->mouseMoved(x, y);
    app->mousex = x;
    app->mousey = y;

    for(int i=0; i<8; i++)
    {
        if(app->mouseButtonState[i])
        {
            app->mainScene->mouseDragged(x,y,i);
        }
    }
}
void OGLRenderer::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    OGLRenderer* app = (OGLRenderer*)glfwGetWindowUserPointer(window);
    if(!app->mainScene) return;

    switch(action)
    {
        case GLFW_RELEASE:
            app->mouseButtonState[button] = false;
            app->mainScene->mouseReleased(app->mousex, app->mousey, button);
            break;
        case GLFW_PRESS:
            app->mouseButtonState[button] = true;
            app->mainScene->mousePressed(app->mousex, app->mousey, button);
            break;
    }
}
void OGLRenderer::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    OGLRenderer* app = (OGLRenderer*)glfwGetWindowUserPointer(window);

    if(!app->mainScene) return;

	switch(action)
	{
		case GLFW_RELEASE:
			app->mainScene->keyReleased(key);
			break;
		case GLFW_PRESS:
			app->mainScene->keyPressed(key);
			break;
	}
}
void OGLRenderer::windowResizedCallback(GLFWwindow* window, int width, int height)
{
    OGLRenderer* app = (OGLRenderer*)glfwGetWindowUserPointer(window);
    if(!app->mainScene) return;
    app->mainScene->windowResized(width, height);
}
void OGLRenderer::windowRefreshCallback(GLFWwindow* window)
{
    OGLRenderer* app = (OGLRenderer*)glfwGetWindowUserPointer(window);

    if(!app->mainScene) return;
    app->mainScene->render(Graphics::getInstance());
    glfwSwapBuffers(window);
}
void OGLRenderer::windowCloseCallback(GLFWwindow* window)
{
    OGLRenderer* app = (OGLRenderer*)glfwGetWindowUserPointer(window);
    app->stop();
}

/***************************************************************/

int OGLRenderer::init()
{
	if(!glfwInit())
    {
		cerr << "Error GLFW init" << endl;
		return 1;
	}

	MonitorManager* mMonitor    = MonitorManager::getInstance();
	WindowManager*  mWindow     = WindowManager::getInstance();
//	window = mWindow->createWindow(mMonitor->getDefaultMonitor(),1280, 583, 0, 0);
	window = mWindow->createWindow(mMonitor->getDefaultMonitor(),1280, 720, 0, 0);

	GLFWwindow* wnd = (GLFWwindow*)window->getHandle();

    glfwSetWindowUserPointer(wnd, this);
	glfwSetCursorPosCallback(wnd, mouseCursorCallback);
    glfwSetMouseButtonCallback(wnd, mouseButtonCallback);
    glfwSetKeyCallback(wnd, keyboardCallback);
    glfwSetWindowCloseCallback(wnd, windowCloseCallback);
    glfwSetWindowSizeCallback(wnd, windowResizedCallback);
//    glfwSetWindowRefreshCallback(wnd, windowRefreshCallback);

	return 0;
}
int OGLRenderer::destroy()
{
    ExampleScene::destroyInstance();
    ExampleScene2::destroyInstance();

    Graphics::destroyInstance();
    SceneManager::destroyInstance();
    TextureManager::destroyInstance();
    TextureLoader::destroyInstance();
    CanvasInstance::destroyInstance(); // Nota: base de todas as imagens!
	WindowManager::destroyInstance();
	MonitorManager::destroyInstance();
	OGLTextRenderer::destroyInstance();
	Transition::destroyInstance();
	Blending::destroyInstance();

	glfwTerminate();

	return 0;
}
int OGLRenderer::setup()
{
	glPointSize(10);
	glEnable(GL_POINT_SMOOTH);
	glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
int OGLRenderer::start()
{
    if(running) return 0;

    running = true;

    Transition* transition = Transition::getInstance();
    transition->setSceneSlotB( ExampleScene2::getInstance() );
    transition->start();
    mainScene = transition;
    window->show();

    //  Layer2* testLayer = new Layer2(mainScene2, 0);
    //  std::this_thread::sleep_for(std::chrono::milliseconds( (long)(1000) ));

    Graphics* g = Graphics::getInstance();

    double timeCurrent;
	while(true)
	{
		timeCurrent = glfwGetTime();
		deltaTime   = timeCurrent - timeBegin;

		//--------------------------------------------//

		g->setFramebuffer(0);
		g->clearFramebuffer(0.5, 0.5, 0.50, 1.0);
		g->setEffect(0);

		mainScene->process(deltaTime);
		mainScene->render(g);

		//--------------------------------------------//

		fpsCurrent = 1.0/deltaTime;

		stringstream ss;
		ss.precision(3);
		ss << fixed;
		ss << TITULO << " [ ";
		ss << "Mouse (x:" << mousex << ", y:" << mousey << ") | ";
		ss << "FPS: " << fpsCurrent << " | ";
		ss << "Sound CPU: " << Sound::Renderer::getInstance()->getCpuLoad()*100 << " ]";

		window->setTitle(ss.str());
		window->update();

		timeBegin = timeCurrent;

//		std::this_thread::sleep_for(std::chrono::milliseconds( (long)(1000/30) ));

		if(!running && !transition->isFading()) break;
	}

	return destroy();
}
int OGLRenderer::stop()
{
    Transition* transition = Transition::getInstance();

    if(!running && !transition->isFading()) return 1;

    if(!transition->isFading())
    {
        transition->clearSceneSlotB();
        transition->start();
        running = false;
    }

	return 0;
}
