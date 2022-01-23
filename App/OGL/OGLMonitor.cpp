/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-21
***********************************************************************/
#include "OGLMonitor.h"
#include "gl_includes.h"
#include <sstream>

OGLMonitor::OGLMonitor(void* handle) : Monitor(handle)
{
	if(!handle) return;

	GLFWmonitor         *monitor    = (GLFWmonitor*)handle;
	const GLFWvidmode   *mode       = glfwGetVideoMode(monitor);

	width           = mode->width;
	height          = mode->height;
	refreshRate     = mode->refreshRate;
	name            = std::string(glfwGetMonitorName(monitor));
}

OGLMonitor::~OGLMonitor()
{

}




OGLMonitorManager::OGLMonitorManager()
{
    refreshList();
    stringstream ss;
    for(int i=0; i<monitorList.size(); i++)
    {
        Monitor* m = monitorList[i];
        ss << "[MonitorManager] Monitor " << i << ": " << m->getName() << " (" << m->getWidth() << " x " << m->getHeight() << ")" << endl;
    }
    cout << ss.str();
}

OGLMonitorManager::~OGLMonitorManager()
{
    clearList();
}

void OGLMonitorManager::clearList()
{
	for(Monitor* monitor : monitorList) delete monitor;
	monitorList.clear();
}

void OGLMonitorManager::refreshList()
{
	if(!monitorList.empty()) clearList();

	int monitorCount;

	GLFWmonitor** m = glfwGetMonitors(&monitorCount);

	for(int i = 0; i < monitorCount; i++)
	{
		monitorList.push_back(new OGLMonitor(m[i]));
	}
}

unsigned OGLMonitorManager::getCount()
{
	return monitorList.size();
}

Monitor* OGLMonitorManager::getMonitor(unsigned index)
{
	return (Monitor*)monitorList[index];
}

Monitor* OGLMonitorManager::getDefaultMonitor()
{
    return monitorList[0];
}

std::string OGLMonitorManager::getNames()
{
    stringstream ss;
    for(int i=0; i<monitorList.size(); i++)
    {
        Monitor* m = monitorList[i];
        ss << "[MonitorManager] Monitor " << i << ": " << m->getName() << " (" << m->getWidth() << " x " << m->getHeight() << ")" << endl;
    }
    return ss.str();
}


