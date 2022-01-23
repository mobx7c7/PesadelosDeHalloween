/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-13
***********************************************************************/
#ifndef SCENE_H
#define SCENE_H

#include "App/Graphics.h"
#include "Drawable.h"
#include <string>
#include <vector>

class Scene : public Drawable
{
private:

    bool    active  = true;
    double  opacity = 1.0;

protected:

    std::vector<Drawable*>  drawables;

    Scene(std::string title, Object* parent);
    Scene(std::string title);
    Scene();

public:

    virtual         ~Scene();

    bool            isActive();
    void            setActive(bool active);

//    virtual void    init();
//    virtual void    start();
    virtual void    process(double deltaTime);
    virtual void    render(Graphics* g);

	virtual void    keyPressed(int key);
    virtual void    keyReleased(int key);
    virtual void    mouseMoved(int x, int y);
    virtual void    mouseDragged(int x, int y, int button);
    virtual void    mousePressed(int x, int y, int button);
    virtual void    mouseReleased(int x, int y, int button);
    virtual void    windowResized(int w, int h);
};





#include <vector>
#include <algorithm>

class SceneManager
{
private:

    static SceneManager*    instance;
    std::vector<Scene*>     scenesList;
    Scene*                  currentScene;
    Scene*                  lastScene;
    Scene*                  defaultScene;

    SceneManager();
    ~SceneManager();

public:

    static SceneManager*    getInstance();
    static void             destroyInstance();

    Scene*                  get(unsigned index);
    Scene*                  getCurrent();
    int                     setCurrent(unsigned index);
    Scene*                  getLast();
    Scene*                  getDefault();

    int                     insert(Scene* scene);
    int                     remove(unsigned index);
    int                     clear();

    /*****************************************************/

    void                    process(double);
    void                    render(Graphics*);
    void                    debug();

};

#endif // SCENE_H
