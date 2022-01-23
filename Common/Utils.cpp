/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-26
***********************************************************************/
#include "Utils.h"

template<typename T>
Point4<T>::Point4(T a, T b, T c, T d):
    value({a,b,c,d}),
    x(value[0]), y(value[1]), z(value[2]), w(value[3]),
    s(value[0]), t(value[1]), u(value[2]), v(value[3]),
    r(value[0]), g(value[1]), b(value[2]), a(value[3])
{
}

template<typename T>
Point4<T>::Point4():
    Point4<T>(0,0,0,0)
{

}

// Solução:
// http://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
template class Point4<unsigned>;
template class Point4<int>;
template class Point4<float>;
template class Point4<double>;
