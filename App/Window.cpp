/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-13
***********************************************************************/
#include "Window.h"
#include "OGLWindow.h"
#include <iostream>

using std::cout;
using std::endl;

Window::Window() : handle(0)
{
    memset(mouseButton, false, 8);
    memset(keys, false, 256);
}

Window::~Window()
{

}

int Window::create(Monitor* monitor, int width, int height, int x, int y)
{
    return 0;
}

int Window::create(Monitor* monitor, int width, int height, int x, int y, bool fullscreen)
{
    return 0;
}

int Window::destroy()
{
    return 0;
}

int Window::show()
{
    return 0;
}

int Window::hide()
{
    return 0;
}

void Window::update()
{

}

void* Window::getHandle()
{
	return handle;
}

Monitor* Window::getMonitor()
{
	return monitor;
}

int Window::getWidth()
{
	return width;
}

int Window::getHeight()
{
	return height;
}

int Window::getX()
{
	return windowPosX;
}

int Window::getY()
{
	return windowPosY;
}

std::string& Window::getTitle()
{
	return title;
}

bool Window::isWindowCloseRequested()
{
    return windowShouldClose;
}

bool Window::isFocused()
{
    return focused;
}

void Window::setTitle(std::string title)
{
	this->title = title;
}

//bool Window::getKey(unsigned key)
//{
//    return keys[key];
//}

double Window::getMouseX()
{
    return mouseX;
}

double Window::getMouseY()
{
    return mouseY;
}

bool Window::getMouseButton(unsigned button)
{
    return button < 8 ? mouseButton[button] : false;
}






NullWindow* NullWindow::instance = 0;

NullWindow::NullWindow()
{

}

NullWindow::~NullWindow()
{

}

NullWindow* NullWindow::getInstance()
{
    if(!instance) instance = new NullWindow();
    return instance;
}










WindowManager* WindowManager::instance = 0;

WindowManager::WindowManager()
{
    cout << "[WindowManager] Iniciando..." << endl;
}

WindowManager::~WindowManager()
{
    cout << "[WindowManager] Destruindo..." << endl;
}

WindowManager* WindowManager::getInstance()
{
	if(!instance)
	{
		instance = new WindowManager();
	}
	return instance;
}

void WindowManager::destroyInstance()
{
	if(instance) delete instance;
}

Window* WindowManager::createWindow(Monitor* monitor, int width, int height, int posx, int posy)
{
	return createWindow(monitor, width, height, posx, posy, false);
}

Window* WindowManager::createWindow(Monitor* monitor, int width, int height, int posx, int posy, bool fullscreen)
{
    OGLWindow* window = new OGLWindow(monitor, width, height, posx, posy, fullscreen);
    if(!window) return NullWindow::getInstance();
    windowList.push_back(window);
	return window;
}

Window* WindowManager::getWindow(unsigned index)
{
    Window* window = windowList[0];
    if(!window) return NullWindow::getInstance();
    return window;
}
Window* WindowManager::getDefaultWindow()
{
    return windowList[0];
}
