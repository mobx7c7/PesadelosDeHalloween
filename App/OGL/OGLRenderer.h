/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-21
***********************************************************************/
#ifndef OGLRENDERER_H
#define OGLRENDERER_H

#include "App/Renderer.h"
#include "App/Window.h"
#include "Common/Scene.h"

class OGLRenderer : public GraphicsRenderer
{
	protected:

		Window*     window              =  0;
        Drawable*   mainScene           = 0;
        bool        running             = false;
        int         mousex              = 0;
        int         mousey              = 0;
        bool        mouseButtonState[8] = {0};

		double  fpsCurrent   = 0;
		double  fpsTarget    = 60;
		double  fpsInterval  = 1000.0/60;
		double  deltaTime    = 0;
		double  timeBegin    = 0;

        static void mouseCursorCallback(GLFWwindow* window, double x, double y);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void windowResizedCallback(GLFWwindow* window, int width, int height);
        static void windowRefreshCallback(GLFWwindow* window);
        static void windowCloseCallback(GLFWwindow* window);

	public:

		OGLRenderer(){}
		virtual ~OGLRenderer(){}
		int init();
		int destroy();
		int setup();
		int start();
		int stop();
};

#endif // OGLRENDERER_H
