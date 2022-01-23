/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-30
***********************************************************************/
#include "Transform.h"
#include <cstring> // menset()

Transform::Transform(unsigned length) :
    data(new char[length]),
    dvalues((double*)&data[0]),
    uvalues((unsigned*)&data[0]),
    length(length)
{
    memset(data, 0, length);
}
Transform::~Transform()
{
	delete[] data;
}
unsigned    Transform::getLength()
{
    return length;
}
char*       Transform::getData()
{
	return data;
}
void        Transform::setData(char* data)
{

}
Transform2::Transform2() :
    Transform(28), // 4 bytes * 5 doubles * 2 unsigned = 28
    posx(dvalues[0]),
    posy(dvalues[1]),
    scalex(dvalues[2]),
    scaley(dvalues[3]),
    rotation(dvalues[4]),
    width(uvalues[5]),
    height(uvalues[6])
{

}
Transform2::~Transform2()
{

}
//double      Transform2::posX() const
//{
//	return dvalues[0];
//}
//double      Transform2::posY() const
//{
//	return dvalues[1];
//}
//double      Transform2::scaleX() const
//{
//	return dvalues[2];
//}
//double      Transform2::scaleY() const
//{
//	return dvalues[3];
//}
//double      Transform2::rotation() const
//{
//	return dvalues[4];
//}
//unsigned    Transform2::width() const
//{
//	return uvalues[5];
//}
//unsigned    Transform2::height() const
//{
//	return uvalues[6];
//}
//void        Transform2::setPosX(const double value)
//{
//	dvalues[0] = value;
//}
//void        Transform2::setPosY(const double value)
//{
//	dvalues[1] = value;
//}
//void        Transform2::setScaleX(const double value)
//{
//	dvalues[2] = value;
//}
//void        Transform2::setScaleY(const double value)
//{
//	dvalues[3] = value;
//}
//void        Transform2::setRotation(const double value)
//{
//	dvalues[4] = value;
//}
//void        Transform2::setWidth(const unsigned value)
//{
//	uvalues[5] = value;
//}
//void        Transform2::setHeight(const unsigned value)
//{
//	uvalues[6] = value;
//}
