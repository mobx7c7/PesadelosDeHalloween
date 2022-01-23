/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-30
***********************************************************************/
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Utils.h"

class Transform
{
protected:
    unsigned    length;
    char*       data;
    double*     dvalues;
    unsigned*   uvalues;
    Transform(unsigned length);
public:
    virtual ~Transform();
    unsigned    getLength();
    char*       getData();
    void        setData(char* data);
};

class Transform2 : public Transform
{
    public:

        double &posx;
        double &posy;
        double &scalex;
        double &scaley;
        double &rotation;
        unsigned &width;
        unsigned &height;

	public:

		Transform2();
		~Transform2();
//		double      posX() const;
//		double      posY() const;
//		double      scaleX() const;
//		double      scaleY() const;
//		double      rotation() const;
//		unsigned    width() const;
//		unsigned    height() const;
//
//		void        setPosX(const double value);
//		void        setPosY(const double value);
//		void        setScaleX(const double value);
//		void        setScaleY(const double value);
//		void        setRotation(const double value);
//		void        setWidth(const unsigned value);
//		void        setHeight(const unsigned value);
};

#endif // TRANSFORM_H
