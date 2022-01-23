/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-30
***********************************************************************/
#include "Object.h"
#include <cstdlib>
#include <ctime>

unsigned Object::nextIdent = 0;

//Object::Object() : Object("Object", 0){}
//
//Object::Object(string name) : Object(name, 0){}

Object::Object(string name, Object* parent) : name(name), parent(parent)
{
//    srand(time(0));
//    ident = ((rand()%0xff) << 0x18) | ((rand()%0xff) << 0x10) | ((rand()%0xff) << 0x08) | (rand()%0xff);
    ident = nextIdent;
    nextIdent++;
}

Object::~Object()
{

}

unsigned Object::getIdent()
{
    return ident;
}

string& Object::getName()
{
    return name;
}

void Object::setName(string name)
{
    this->name = name;
}

Object* Object::getParent()
{
    return parent;
}

void Object::setParent(Object* parent)
{
    this->parent = parent;
}

//void Object::getParameters(string parameters)
//{
//
//}
//
//string Object::setParameters()
//{
//
//}

