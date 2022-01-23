/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-26
***********************************************************************/
#include "Button.h"

Button* Button::firstSelected = 0;

Button::Button(double x, double y, unsigned width, unsigned height, Object* parent) :  Drawable("Button", parent)
{
    Transform2& t = getTransform();
    t.posx      = x;
    t.posy      = y;
    t.width     = width;
    t.height    = height;
}

Button::~Button()
{

}

bool Button::isInside(double x, double y)
{
    Transform2& t = getTransform();
    return  x >= t.posx &&
	        y >= t.posy &&
	        x < (t.posx + t.width) &&
	        y < (t.posy + t.height);
}

void Button::process(double deltaTime)
{
	if(getParent()) // tem objeto pai?
	{
		Drawable* draw = (Drawable*)getParent();
		Transform2& t1 = getTransform();
		Transform2& t2 = draw->getTransform();
		t2.posx = t1.posx;
		t2.posy = t1.posy;
	}
}

void Button::render(Graphics* g)
{
    Transform2& t = getTransform();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if(selected){
        if(pressed){
            g->setColor(1,0,0,1);
        }else{
//            unsigned id = getIdent();
//            float k = 1.0f/255;
//            g->setColor(k * (id >> 16 & 0xFF),
//                        k * (id >> 8 & 0xFF),
//                        k * (id >> 0 & 0xFF),
//                        1.0f);
            g->setColor(1,1,1,1);
        }
        g->drawRect(t.posx, t.posy, t.width, t.height);
    }
//    glDisable(GL_BLEND);
}

bool Button::isPressed()
{
    return pressed;
}
bool Button::isSelected()
{
    return selected;
}
bool Button::isDragable()
{
    return dragable;
}
bool Button::isTouched()
{
    return touched;
}
void Button::setDragable(bool dragable)
{
    this->dragable = dragable;
}
void Button::setTouched(bool touched)
{
    this->touched = touched;
}
void Button::mouseMoved(int x, int y)
{
	dx      = x - oldx;
	dy      = y - oldy;
	oldx    = x;
	oldy    = y;

	if(isInside(x, y) && !firstSelected)
    {
        selected = true;
    }
    else if(!pressed)
    {
        selected = false;
    }
}

void Button::mouseDragged(int x, int y, int button)
{
	if(dragable && pressed && button == 0)
	{
	    Transform2& t = getTransform();
		t.posx += dx;
		t.posy += dy;
	}
}

void Button::mousePressed(int x, int y, int button)
{
	if(selected && !firstSelected && button == 0)
	{
        pressed         = true;
        firstSelected   = this;
	}
}

void Button::mouseReleased(int x, int y, int button)
{
	if(pressed && button == 0)
	{
		pressed         = false;
		firstSelected   = 0;
	}
}
