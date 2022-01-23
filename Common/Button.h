/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-26
***********************************************************************/
#ifndef BUTTON_H
#define BUTTON_H

#include "Drawable.h"

class Button : public Drawable
{
	protected:

        static Button*  firstSelected;

		bool            pressed     = false;
		bool            selected    = false;
		bool            dragable    = false;
		bool            touched     = false;

        int             oldx        = 0;
		int             oldy        = 0;
		int             dx          = 0;
		int             dy          = 0;

		bool            isInside(double x, double y);

	public:

		Button(double x, double y, unsigned width, unsigned height, Object* parent);
		~Button();

        bool isSelected();
		bool isPressed();
		bool isDragable();
		bool isTouched();
		void setDragable(bool dragable);
		void setTouched(bool touched);

		virtual void process(double deltaTime);
		virtual void render(Graphics* g);
        virtual void mouseMoved(int x, int y);
        virtual void mouseDragged(int x, int y, int button);
        virtual void mousePressed(int x, int y, int button);
        virtual void mouseReleased(int x, int y, int button);
};

#endif // BUTTON_H
