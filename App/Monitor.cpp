/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-13
***********************************************************************/
#include "Monitor.h"
#include <iostream>
//#include "gl_includes.h"
//#include <sstream>
#include "OGLMonitor.h"


using std::cout;
using std::endl;

Monitor::Monitor(void* handle) : handle(handle)
{

}

Monitor::~Monitor()
{

}

void* Monitor::getHandle()
{
	return handle;
}

unsigned Monitor::getWidth()
{
	if(!handle) return 0;
	return width;
}

unsigned Monitor::getHeight()
{
	if(!handle) return 0;
	return height;
}

unsigned Monitor::getRefreshRate()
{
	if(!handle) return 0;
	return refreshRate;
}

std::string Monitor::getName()
{
	if(!handle) return "";
	return name;
}














MonitorManager* MonitorManager::instance = 0;

MonitorManager::MonitorManager()
{
    cout << "[MonitorManager] Iniciando..." << endl;
}

MonitorManager::~MonitorManager()
{
    cout << "[MonitorManager] Destruindo..." << endl;
}

MonitorManager* MonitorManager::getInstance()
{
	if(!instance) instance = new OGLMonitorManager();
	return instance;
}

void MonitorManager::destroyInstance()
{
	if(instance) delete instance;
}
