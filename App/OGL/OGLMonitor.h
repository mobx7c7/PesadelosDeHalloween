/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-21
***********************************************************************/
#ifndef OGLMONITOR_H
#define OGLMONITOR_H

#include "App/Monitor.h"

class OGLMonitor : public Monitor
{
public:
    OGLMonitor(void*);
    ~OGLMonitor();
};


class OGLMonitorManager : public MonitorManager
{
protected:

    friend class MonitorManager;
    OGLMonitorManager();
    ~OGLMonitorManager();

public:

    void            clearList();
    void            refreshList();
    unsigned        getCount();
    Monitor*        getMonitor(unsigned);
    Monitor*        getDefaultMonitor();
    std::string     getNames();
};

#endif // OGLMONITOR_H
