/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-19
***********************************************************************/
#ifndef RECT_H
#define RECT_H

class Data
{
protected:

    char*       _data;
    unsigned    _size;

public:

    Data(unsigned size) :
        _size(size),
        _data(new char[size])
    {

    }
    virtual ~Data()
    {
        delete[] data;
    }
    void setData(const char* data)
    {
        memcpy(_data, data, size);
    }
    char& getData()
    {
        return *data;
    }
    unsigned getSize()
    {
        return size;
    }
};



class Rectf : public Rect
{
protected:

    float &x1, &y1, &x2, &y2;

public:

    RectF(float x1, float y1, float x2, float y2) : Data(sizeof(float)*4),
    {
        float* f_data   = (float*)_data;
        x1 = f_data[0],
        y1 = f_data[1],
        x2 = f_data[2],
        y2 = f_data[3],
    }
    ~RectF()
    {

    }
    float getX1()
    {
        return f_data[0];
    }
    float getY1()
    {
        return f_data[1];
    }
    float getX2()
    {
        return f_data[2];
    }
    float getY2()
    {
        return f_data[3];
    }
    float setX1(float value)
    {
        f_data[0] = value;
    }
    float setY1(float value)
    {
        f_data[1] = value;
    }
    float setX2(float value)
    {
        f_data[2] = value;
    }
    float setY2(float value)
    {
        f_data[3] = value;
    }
    float getWidth()
    {
        return fabs(f_data[0] - f_data[2]);
    }
    float getHeight()
    {
        return fabs(f_data[1] - f_data[3]);
    }
};

#endif // RECT_H
