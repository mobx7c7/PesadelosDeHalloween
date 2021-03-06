/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de cria??o     : 2015-03-21
***********************************************************************/
#include "OGLController.h"
#include "OGLWindow.h"

MouseMovedFunc      _MouseMovedFunc = 0;
MouseDraggedFunc    _MouseDraggedFunc = 0;
MousePressedFunc    _MousePressedFunc = 0;
MouseReleasedFunc   _MouseReleasedFunc = 0;

bool mouseButtonState[8] = {0};

void GLFWCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	if(_MouseMovedFunc)
	{
		_MouseMovedFunc(xpos, ypos);
	}
	if(_MouseDraggedFunc)
	{
		for(int i=0; i<8; i++)
		{
			if(mouseButtonState[i])
			{
				_MouseDraggedFunc(xpos, ypos, i);
			}
		}
	}
}

void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	switch(action)
	{
		case GLFW_PRESS:
			mouseButtonState[button] = true;
			break;
		case GLFW_RELEASE:
			mouseButtonState[button] = false;
			break;
	}
}

GLFWMouseController::GLFWMouseController()
{
	wnd = WindowManager::getInstance()->getDefaultWindow()->getHandle();
	GLFWwindow* window = (GLFWwindow*)wnd;
	//glfwSetMouseButtonCallback(window, GLFWMouseButtonCallback);
	//glfwSetCursorPosCallback(window, GLFWCursorPosCallback);
	glfwGetCursorPos(window, &x, &y);
	oldx = x;
	oldy = y;
}
GLFWMouseController::~GLFWMouseController()
{

}
bool GLFWMouseController::isButtonPressed(unsigned button) const
{
	return glfwGetMouseButton((GLFWwindow*)wnd, button) == GLFW_PRESS;
}
double GLFWMouseController::getDX() const
{
	return deltax;
}
double GLFWMouseController::getDY() const
{
	return deltay;
}
double GLFWMouseController::getX() const
{
	return x;
}
double GLFWMouseController::getY() const
{
	return y;
}
void GLFWMouseController::poolEvents()
{
	glfwGetCursorPos((GLFWwindow*)wnd, &x, &y);
	deltax = x - oldx;
	deltay = y - oldy;
	oldx = x;
	oldy = y;
}
void GLFWMouseController::registerMouseMovedFunc(MouseMovedFunc func)
{
	_MouseMovedFunc = func;
}
void GLFWMouseController::registerMouseDraggedFunc(MouseDraggedFunc func)
{
	_MouseDraggedFunc = func;
}
void GLFWMouseController::registerMouseReleasedFunc(MouseReleasedFunc func)
{
	_MouseReleasedFunc = func;
}
void GLFWMouseController::registerMousePressedFunc(MousePressedFunc func)
{
	_MousePressedFunc = func;
}








KeyPressedFunc      _KeyPressedFunc = 0;
KeyReleasedFunc     _KeyReleasedFunc = 0;
KeyRepeatedFunc     _KeyRepeatedFunc = 0;

void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch(action)
	{
		case GLFW_RELEASE:
			if(_KeyReleasedFunc) _KeyReleasedFunc(key);
			break;
		case GLFW_PRESS:
			if(_KeyPressedFunc) _KeyPressedFunc(key);
			break;
		case GLFW_REPEAT:
			if(_KeyRepeatedFunc) _KeyRepeatedFunc(key);
			break;
	}

}

GLFWKeyboardController::GLFWKeyboardController()
{
	wnd = WindowManager::getInstance()->getDefaultWindow()->getHandle();
}
GLFWKeyboardController::~GLFWKeyboardController()
{

}
bool GLFWKeyboardController::isKeyPressed(unsigned key) const
{
	return glfwGetKey((GLFWwindow*)wnd, key) == GLFW_PRESS;
}
bool GLFWKeyboardController::isKeyRepeated(unsigned key) const
{
	return glfwGetKey((GLFWwindow*)wnd, key) == GLFW_REPEAT;
}
void GLFWKeyboardController::poolEvents()
{

}
void GLFWKeyboardController::registerKeyReleasedFunc(KeyReleasedFunc func)
{
	_KeyReleasedFunc = func;
}
void GLFWKeyboardController::registerKeyPressedFunc(KeyPressedFunc func)
{
	_KeyPressedFunc = func;
}







