/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-21
***********************************************************************/
#ifndef OGLCONTROLLER_H
#define OGLCONTROLLER_H

#include "App/Controller.h"
#include "App/Window.h"

class GLFWKeyboardController : public KeyboardController
{
    protected:

        void* wnd = 0;

    public:

        GLFWKeyboardController();
        virtual ~GLFWKeyboardController();
        bool isKeyPressed(unsigned key) const;
        bool isKeyRepeated(unsigned key) const;
        void poolEvents();

        void registerKeyReleasedFunc(KeyReleasedFunc);
        void registerKeyPressedFunc(KeyPressedFunc);
};

class GLFWMouseController : public MouseController
{
    protected:

        void* wnd = 0;
        double x = 0;
        double y = 0;
        double oldx = 0;
        double oldy = 0;
        double deltax = 0;
        double deltay = 0;

    public:

        GLFWMouseController();
        virtual ~GLFWMouseController();
        bool    isButtonPressed(unsigned button) const;
        double  getDX() const;
        double  getDY()const;
        double  getX() const;
        double  getY() const;
        void    poolEvents();

        void registerMouseMovedFunc(MouseMovedFunc);
        void registerMouseDraggedFunc(MouseDraggedFunc);
        void registerMouseReleasedFunc(MouseReleasedFunc);
        void registerMousePressedFunc(MousePressedFunc);
};

#endif // OGLCONTROLLER_H
