/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-13
***********************************************************************/
#include "Controller.h"
#include "OGLController.h"
#include <cstring>

KeyboardController* KeyboardController::instance = 0;
KeyboardController::KeyboardController(){}
KeyboardController::~KeyboardController(){}
KeyboardController* KeyboardController::getInstance()
{
	if(!instance) instance = new GLFWKeyboardController();
	return instance;
}
void KeyboardController::destroyInstance()
{
	if(instance) delete instance;
}

MouseController* MouseController::instance = 0;
MouseController::MouseController(){}
MouseController::~MouseController(){}
MouseController* MouseController::getInstance()
{
	if(!instance) instance = new GLFWMouseController();
	return instance;
}
void MouseController::destroyInstance()
{
	if(instance) delete instance;
}

