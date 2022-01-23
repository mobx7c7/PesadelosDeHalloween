/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-21
***********************************************************************/
#include "OGLWindow.h"


OGLWindow::OGLWindow(Monitor* monitor, int width, int height, int posx, int posy, bool fullscreen)
{
	create(monitor, width, height, posx, posy, fullscreen);
}

OGLWindow::OGLWindow()
{

}

OGLWindow::~OGLWindow()
{
	destroy();
}

//void OGLWindow::GLFWWindowPosCallback(GLFWwindow* window, int x, int y)
//{
//	OGLWindow* userPtr  = (OGLWindow*)glfwGetWindowUserPointer(window);
//	userPtr->windowPosX = x;
//	userPtr->windowPosY = y;
//}

//void OGLWindow::GLFWWindowSizeCallback(GLFWwindow* window, int width, int height)
//{
//    OGLWindow* userPtr  = (OGLWindow*)glfwGetWindowUserPointer(window);
//    userPtr->width      = width;
//    userPtr->height     = height;
//}

//void OGLWindow::GLFWWindowFocusCallback(GLFWwindow* window, int focused)
//{
//    OGLWindow* userPtr = (OGLWindow*)glfwGetWindowUserPointer(window);
//    userPtr->focused    = (focused == GL_TRUE ? true : false);
//}

//void OGLWindow::GLFWWindowCloseCallback(GLFWwindow* window)
//{
//    OGLWindow* userPtr = (OGLWindow*)glfwGetWindowUserPointer(window);
//    userPtr->windowShouldClose = true;
//}

//void OGLWindow::GLFWWindowRefreshCallback(GLFWwindow* window)
//{
//    OGLWindow* userPtr = (OGLWindow*)glfwGetWindowUserPointer(window);
//}

//void OGLWindow::GLFWCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
//{
//    OGLWindow* userPtr = (OGLWindow*)glfwGetWindowUserPointer(window);
//    userPtr->mouseX     = xpos;
//    userPtr->mouseY     = ypos;
//}
//
//void OGLWindow::GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
//{
//    OGLWindow* userPtr = (OGLWindow*)glfwGetWindowUserPointer(window);
//
//    for(unsigned i=0; i<8; i++)
//    {
//        if(button == GLFW_MOUSE_BUTTON_1+i)
//        {
//            switch(action)
//            {
//                case GLFW_PRESS:
//                    userPtr->mouseButton[i] = true;
//                    break;
//                case GLFW_RELEASE:
//                    userPtr->mouseButton[i] = false;
//                    break;
//            }
//        }
//    }
//}
//
//void OGLWindow::GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
////    OGLWindow* userPtr = (OGLWindow*)glfwGetWindowUserPointer(window);
//
////       if (key == GLFW_KEY_E && action == GLFW_PRESS)
////        activate_airship();
//}

int OGLWindow::create(Monitor* monitor, int width, int height, int x, int y)
{
    return create(monitor, width, height, x, y, false);
}

int OGLWindow::create(Monitor* monitor, int width, int height, int posx, int posy, bool fullscreen)
{
    if(handle) return -1;

    Monitor* monitorSelected = 0;

    if(!monitor)
        monitorSelected = MonitorManager::getInstance()->getDefaultMonitor();
    else
        monitorSelected = monitor;

//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    //glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    //glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    //glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    //glfwWindowHint(GLFW_RED_BITS, 8);
    //glfwWindowHint(GLFW_GREEN_BITS, 8);
    //glfwWindowHint(GLFW_BLUE_BITS, 8);
    //glfwWindowHint(GLFW_ALPHA_BITS, 8);
    //glfwWindowHint(GLFW_DEPTH_BITS, 24);

    glfwWindowHint(GLFW_DECORATED, true);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_VISIBLE, false);
    glfwWindowHint(GLFW_RESIZABLE, true);

    if(fullscreen)
    {
        window = glfwCreateWindow(width,//monitorSelected->getWidth(),
                                  height,//monitorSelected->getHeight(),
                                  title.c_str(),
                                  (GLFWmonitor*)monitorSelected->getHandle(),
                                  NULL);
    }
    else
    {
        window = glfwCreateWindow(width,
                                  height,
                                  title.c_str(),
                                  NULL,
                                  NULL);
    }

	if(!window)
    {
        cerr << "Failed to create window";
        return -1;
    }

    if(fullscreen)
    {
        // Esconde cursor
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        // Ajusta posição da janela para o centro da tela
        glfwSetWindowPos(window,
                         (monitorSelected->getWidth() - width)/2,
                         (monitorSelected->getHeight() - height)/2);
        //glfwSetWindowPos(window, posx, posy);
    }

    glfwMakeContextCurrent(window);

    //Nota: GLEW só inicializa com um contexto presente!
    if(glewInit() != GLEW_OK)
    {
        destroy();
        cerr << "Failed to init GLEW";
        return -1;
    }

	this->monitor   = monitorSelected;
	this->handle    = window;
	this->width     = width;
	this->height    = height;

	return 0;
}

int OGLWindow::destroy()
{
	if(!handle) return -1;
	glfwDestroyWindow((GLFWwindow*)handle);
	monitor = 0;
	handle = 0;
	return 0;
}

int OGLWindow::show()
{
	if(!window) return 0;
	glfwShowWindow(window);
	return 1;
}

int OGLWindow::hide()
{
	if(!window) return 0;
	glfwHideWindow(window);
	return 1;
}

int OGLWindow::getWidth()
{
    glfwGetWindowSize(window, &width, 0);
    return width;
}

int OGLWindow::getHeight()
{
    glfwGetWindowSize(window, 0, &height);
    return height;
}

void OGLWindow::update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

GLFWwindow* OGLWindow::getHandle()
{
    return window;
}

void OGLWindow::setTitle(std::string title)
{
	this->title = title;
	glfwSetWindowTitle(window, title.c_str());
}
