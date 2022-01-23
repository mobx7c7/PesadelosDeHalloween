/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-20
***********************************************************************/
#include "Preferences.h"

GlobalOptions* GlobalOptions::instance = 0;

GlobalOptions::GlobalOptions()
{

}
GlobalOptions::~GlobalOptions()
{

}

GlobalOptions* GlobalOptions::getInstance()
{
    if(!instance) instance = new GlobalOptions();
    return instance;
}
void GlobalOptions::destroyInstance()
{
    if(instance) delete instance;
}
bool GlobalOptions::isAvailable(string name)
{
    return false;
}
string GlobalOptions::getValue(string name)
{
    return "";
}
void GlobalOptions::setValue(string name, string value)
{

}
