/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-13
***********************************************************************/
#ifndef WINDOW_H
#define WINDOW_H

#include "gl_includes.h"
#include "Monitor.h"

class Window
{
protected:

    void*           handle;
    std::string     title;
    Monitor*        monitor;

    int             width       = 0;
    int             height      = 0;
    int             windowPosX  = 0;
    int             windowPosY  = 0;

    bool            focused             = false;
    bool            windowShouldClose   = false;

    double          mouseX = 0;
    double          mouseY = 0;
    bool            mouseButton[8];
    bool            keys[256];

    Window();

public:

    virtual                 ~Window();
    virtual int             create(Monitor*, int, int, int, int);
    virtual int             create(Monitor*, int, int, int, int, bool);
    virtual int             destroy();
    virtual int             show();
    virtual int             hide();
    virtual void            update();

    virtual void*           getHandle();
    virtual Monitor*        getMonitor();
    virtual int             getWidth();
    virtual int             getHeight();
    virtual int             getX();
    virtual int             getY();
    virtual std::string&    getTitle();
    virtual void            setTitle(std::string title);

    virtual bool            isWindowCloseRequested();
    virtual bool            isFocused();

    // MouseInput
    //virtual bool            getKey(unsigned key);
    virtual double          getMouseX();
    virtual double          getMouseY();
    virtual bool            getMouseButton(unsigned button);

};








class NullWindow : public Window
{
private:
    static NullWindow* instance;
    NullWindow();
    ~NullWindow();
public:
    static NullWindow* getInstance();
};






class WindowManager
{
private:

    static WindowManager* instance;
    WindowManager();
    ~WindowManager();
    vector<Window*> windowList;

public:

    static WindowManager*   getInstance();
    static void             destroyInstance();
    Window*                 getWindow(unsigned);
    Window*                 getDefaultWindow();
    Window*                 createWindow(Monitor*, int, int, int, int);
    Window*                 createWindow(Monitor*, int, int, int, int, bool);
};


#endif // WINDOW_H
