/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-13
***********************************************************************/
#ifndef MONITOR_H
#define MONITOR_H

#include <string>
#include <vector>

class Monitor
{
protected:

    void*       handle;
    std::string name;
    unsigned    width, height, refreshRate;

protected:

    Monitor(void*);

public:

    virtual             ~Monitor();
    virtual void*       getHandle();
    virtual unsigned    getWidth();
    virtual unsigned    getHeight();
    virtual unsigned    getRefreshRate();
    virtual std::string getName();
};




//class OGLMonitor : public Monitor
//{
//public:
//
//    OGLMonitor(void*);
//    ~OGLMonitor();
//};







class MonitorManager
{
private:

    static MonitorManager*  instance;

protected:

    std::vector<Monitor*>   monitorList;
    MonitorManager();
    virtual ~MonitorManager();

public:

    static MonitorManager*  getInstance();
    static void             destroyInstance();
    virtual void            clearList() = 0;
    virtual void            refreshList() = 0;
    virtual unsigned        getCount() = 0;
    virtual Monitor*        getMonitor(unsigned) = 0;
    virtual Monitor*        getDefaultMonitor() = 0;
    virtual std::string     getNames() = 0;

};






//class OGLMonitorManager : public MonitorManager
//{
//protected:
//
//    friend class MonitorManager;
//    OGLMonitorManager();
//    ~OGLMonitorManager();
//
//public:
//
//    void            clearList();
//    void            refreshList();
//    unsigned        getCount();
//    Monitor*        getMonitor(unsigned);
//    Monitor*        getDefaultMonitor();
//    std::string     getNames();
//};






#endif // MONITOR_H
