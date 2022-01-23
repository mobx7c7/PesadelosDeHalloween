/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-16
***********************************************************************/
#ifndef DEFAULTSCENE_H
#define DEFAULTSCENE_H

#include "Common/Scene.h"

class DefaultScene : public Scene
{
public:

    DefaultScene();
    ~DefaultScene();

    void    process(double);
    void    render(Graphics*);
    void    debug();

};
#endif // DEFAULTSCENE_H
