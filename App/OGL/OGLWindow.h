/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-21
***********************************************************************/
#ifndef OGLWINDOW_H
#define OGLWINDOW_H

#include "gl_includes.h"
#include "App/Monitor.h"
#include "App/Window.h"


class OGLWindow : public Window
{
protected:

    Monitor*        monitor;
    GLFWwindow*     window;

//    static void GLFWWindowPosCallback(GLFWwindow*, int, int);
//    static void GLFWWindowSizeCallback(GLFWwindow*, int, int);
//    static void GLFWWindowCloseCallback(GLFWwindow*);
//    static void GLFWWindowFocusCallback(GLFWwindow*, int);
//    static void GLFWWindowRefreshCallback(GLFWwindow*);

//    static void GLFWCursorPosCallback(GLFWwindow*, double, double);
//    static void GLFWMouseButtonCallback(GLFWwindow*, int, int, int);
//    static void GLFWKeyCallback(GLFWwindow*, int, int, int, int);

    //void GLFWFramebuffersizeCallback(GLFWwindow*, int, int);
    //void GLFWWindowRefreshCallback(GLFWwindow*);
    //void GLFWDropCallback(GLFWwindow*, int count, char** names);

public:

    OGLWindow(Monitor*, int, int, int, int, bool);
    OGLWindow();
    ~OGLWindow();

    GLFWwindow*     getHandle();
    int             create(Monitor*, int, int, int, int);
    int             create(Monitor*, int, int, int, int, bool);
    int             destroy();
    int             show();
    int             hide();
    void            update();
    int             getWidth();
    int             getHeight();
    void            setTitle(std::string title);
    bool            isCloseRequested();
};

#endif // OGLWINDOW_H
