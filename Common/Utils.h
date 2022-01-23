/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-26
***********************************************************************/
#ifndef UTILS_H
#define UTILS_H

template<typename T>
class Point4
{
protected:
    T value[4];
public:
    T &x, &y, &z, &w;
    T &s, &t, &u, &v;
    T &r, &g, &b, &a;
    Point4(T a, T b, T c, T d);
    Point4();
};

typedef class Point4<unsigned>  Point4u;
typedef class Point4<int>       Point4i;
typedef class Point4<float>     Point4f;
typedef class Point4<double>    Point4d;

#endif // UTILS_H
