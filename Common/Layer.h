/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-19
***********************************************************************/
#ifndef LAYER_H
#define LAYER_H

/*

#include "Drawable.h"
#include "GL\Framebuffer.h"
#include "GL\Shader.h"

class Layer : public Drawable
{
protected:

    //FIXME: Colocar todos em Drawable.
    Framebuffer*        drawFramebuffer;
    Framebuffer*        copyFramebuffer;
    Layer*              parent;
    double              opacity;
    bool                active;

    //NOTA: Permanecer em Layer.
    // Fazer um DrawableManager
    vector<Drawable*>   drawables;
    // Fazer um EffectManager
    vector<Effect*>     effects;

public:

    Layer(unsigned, unsigned, Layer*);
    ~Layer();

    Drawable*       getDrawable(unsigned);
    Layer*          getParent();
    Framebuffer*    getFramebuffer();
    void            setParent(Layer*);
    void            addDrawable(Drawable*);

    void            process(double);
    void            render(Graphics*);
    void            debug();

};




#include <map>
#include <string>

template<typename Type> class AbstractDrawablePanel
{
private:

    string label;

protected:

    map<string, Type*> elements;
    AbstractDrawablePanel(string label);
    virtual ~AbstractDrawablePanel();

public:

    string& getLabel() const;
    size_t  getCount();
    void    add(string name, Type* element);
    Type*   get(string name) const;
    void    erase(string name);
    void    eraseAll();

    virtual void process(double deltaTime) = 0;
    virtual void render(Graphics* g) = 0;

};


template<typename Type>
AbstractDrawablePanel<Type>::AbstractDrawablePanel(string label) : label(label)
{

}

template<typename Type>
AbstractDrawablePanel<Type>::~AbstractDrawablePanel()
{
	eraseAll();
}

template<typename Type>
string& AbstractDrawablePanel<Type>::getLabel() const
{
	return label;
}

template<typename Type>
size_t AbstractDrawablePanel<Type>::getCount()
{
	return elements.size();
}

template<typename Type>
void AbstractDrawablePanel<Type>::add(string name, Type* element)
{
	typename map<string, Type*>::iterator it = elements.find(name);
	if(it != elements.end())
	{
        delete it->second;
        it->second = element;
        return;
	}
    elements.insert(make_pair(name, element));
}

template<typename Type>
Type* AbstractDrawablePanel<Type>::get(string name) const
{
	typename map<string, Type*>::const_iterator it = elements.find(name);
	if(it != elements.end())
	{
		return it->second;
	}
	return NULL;
}

template<typename Type>
void AbstractDrawablePanel<Type>::erase(string name)
{
	typename map<string, Type*>::const_iterator it = elements.find(name);
	if(it != elements.end())
	{
		delete it->second;
		elements.erase(it);
	}
}

template<typename Type>
void AbstractDrawablePanel<Type>::eraseAll()
{
	typename map<string, Type*>::iterator it;
	for(it = elements.begin(); it != elements.end(); it++)
	{
		delete it->second;
	}
	elements.clear();
}





class LayerPanel : public AbstractDrawablePanel<Layer>
{
public:
    LayerPanel();
    ~LayerPanel();
    void process(double deltaTime);
    void render(Graphics* g);
};

*/

#endif // LAYER_H





