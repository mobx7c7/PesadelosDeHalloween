/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-13
***********************************************************************/
#include "Scene.h"
#include "Scenes/DefaultScene.h"

Scene::Scene(std::string title, Object* parent) : Drawable(title, parent)
{

}

Scene::Scene(std::string title) : Drawable(title, 0)
{

}

Scene::Scene() : Drawable("Scene", 0)
{

}

Scene::~Scene()
{
    for(Drawable* drawable : drawables) delete drawable;
    drawables.clear();
}

//void Scene::setParent(Scene* parent)
//{
//    setParent(parent);
//}
//
//Scene* Scene::getParent()
//{
//    Scene* sceneParent = (Scene*)Object::getParent();
//    return sceneParent ? sceneParent : SceneManager::getInstance()->getDefault();
//}

void Scene::setActive(bool active)
{
    this->active = active;
}

bool Scene::isActive()
{
    return active;
}

void Scene::process(double deltaTime)
{
    for(Drawable* drawable : drawables)
    {
        drawable->process(deltaTime);
    }
}

void Scene::render(Graphics* g)
{
    for(Drawable* drawable : drawables)
    {
        drawable->render(g);
    }
}

void Scene::keyPressed(int key)
{
    for(Drawable* drawable : drawables)
    {
        drawable->keyPressed(key);
    }
}

void Scene::keyReleased(int key)
{
    for(Drawable* drawable : drawables)
    {
        drawable->keyReleased(key);
    }
}

void Scene::mouseMoved(int x, int y)
{
    for(Drawable* drawable : drawables)
    {
        drawable->mouseMoved(x, y);
    }
}

void Scene::mouseDragged(int x, int y, int button)
{
    for(Drawable* drawable : drawables)
    {
        drawable->mouseDragged(x, y, button);
    }
}

void Scene::mousePressed(int x, int y, int button)
{
    for(Drawable* drawable : drawables)
    {
        drawable->mousePressed(x, y, button);
    }
}

void Scene::mouseReleased(int x, int y, int button)
{
    for(Drawable* drawable : drawables)
    {
        drawable->mouseReleased(x, y, button);
    }
}

void Scene::windowResized(int w, int h)
{
    for(Drawable* drawable : drawables)
    {
        drawable->windowResized(w, h);
    }
}




#include <sstream>

SceneManager* SceneManager::instance = 0;

SceneManager::SceneManager()
{
    cout << "[SceneManager] Iniciando..." << endl;
    currentScene = lastScene = defaultScene = new DefaultScene();
}

SceneManager::~SceneManager()
{
    cout << "[SceneManager] Destruindo..." << endl;
    delete defaultScene;
    clear();
}

SceneManager* SceneManager::getInstance()
{
    if(!instance) instance = new SceneManager();
    return instance;
}

void SceneManager::destroyInstance()
{
    if(instance) delete instance;
}

int SceneManager::insert(Scene* scene)
{
	if(!scene) return 0;
	scenesList.push_back(scene);
	return 1;
}

Scene* SceneManager::get(unsigned index)
{
    if(scenesList.empty()) return defaultScene;
    Scene* scene = scenesList.at(index);
    if(!scene) return defaultScene;
    return scene;
}

int SceneManager::setCurrent(unsigned index)
{
    if(scenesList.empty()) return 0;

    Scene* scene = scenesList.at(index);
    if(!scene) return 0;

    lastScene = currentScene;
    currentScene = scene;

    return 1;
}

Scene* SceneManager::getCurrent()
{
    return currentScene;
}

Scene* SceneManager::getLast()
{
    return lastScene;
}

Scene* SceneManager::getDefault()
{
    return defaultScene;
}

int SceneManager::clear()
{
    if(scenesList.empty()) return 0;
    std::vector<Scene*>::iterator it;
    for(it = scenesList.begin(); it != scenesList.end(); it++) delete *it;
	scenesList.clear();
	return 1;
}

int SceneManager::remove(unsigned index)
{
    Scene* scene = scenesList.at(index);
    if(!scene) return 0;
    delete scene;
    return 1;
}

void SceneManager::process(double deltaTime)
{
    if(!defaultScene) return;

    defaultScene->process(deltaTime);

    if(!scenesList.empty() && currentScene != defaultScene)
    {
        currentScene->process(deltaTime);
    }
}

void SceneManager::render(Graphics* g)
{
    if(!defaultScene) return;

    defaultScene->render(g);

    if(!scenesList.empty() && currentScene != defaultScene)
    {
        currentScene->render(g);
    }
}

