/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-05-21
***********************************************************************/
#ifndef PARAMETER_H
#define PARAMETER_H

#include <map>
#include <queue>

using std::map;
using std::queue;

enum ParameterType
{
    Boolean,
    Int,
    Float,
};

class Parameter
{
public:
    Parameter(unsigned type, void* data) : data(data) , type(type){}
    ~Parameter(){delete[] data;}
    unsigned    type;
    void*       data;
};

//class BoolParameter : private Parameter
//{
//public:
//    void    setParameter(bool value);
//    bool    getParameter();
//};
//class IntParameter : private Parameter
//{
//public:
//    void    setParameter(int value);
//    int     getParameter();
//};
//class FloatParameter : private Parameter
//{
//public:
//    void    setParameter(float value);
//    float   getParameter();
//};



//	formato 1: bloco indice e bloco dados
//	cabeçalho: 	[size][offset] // verificação de consistência
//	indice	: 	[param_type][param_size][param_offset];
//	cabeçalho: 	[size][offset] // verificação de consistência
//	data 	: 	[param_data];
//
//	formato 2: bloco unico e intercalado
//	[param_type][param_size][param_data] | ;

class ParameterPanel
{
    friend class Parameter;
    protected:

        unsigned                    counter = 0;
        map<unsigned,   Parameter>  parameters;
        queue<unsigned>             indexRecycle;

    public:

        unsigned 	createParameter(unsigned type)
        {
            void* data;
            switch(type)
            {
            case ParameterType::Boolean:
                data = new bool;
                break;
            case ParameterType::Int:
                data = new int;
                break;
            case ParameterType::Float:
                data = new float;
                break;
            default:
                return 0;
            }

            unsigned newIndex;
            if(!indexRecycle.empty()) // se tiver algo para ser reusado...
            {
                newIndex = indexRecycle.back(); // atribui ultimo...
                indexRecycle.pop(); // remove valor da lista
            }
            else
            {
                counter++;
                newIndex = counter;
            }

            parameters.insert( std::pair<unsigned, Parameter>(newIndex, Parameter(type, data)) );
            return newIndex;
        }
        void 		deleteParameter(unsigned index)
        {
            std::map<unsigned, Parameter>::iterator it = parameters.find(index);
            if(it != parameters.end())
            {
                indexRecycle.push(it->first);
                parameters.erase(it);
            }
        }
        void* getParameter(unsigned index, unsigned type)
        {
            std::map<unsigned, Parameter>::iterator it = parameters.find(index);
            if(it != parameters.end())
            {
                if(it->second.type == type)
                {
                    return it->second.data;
                }
            }
            return 0;
        }
        void setParameter(unsigned index, unsigned type, void* data)
        {
            std::map<unsigned, Parameter>::iterator it = parameters.find(index);
            if(it != parameters.end())
            {
                if(it->second.type == type)
                {
                    //memcpy(it->second.data, data, it->second.size);
                }
            }
        }
        int getParameteri(unsigned index)
        {
            void* data = getParameter(index, ParameterType::Int);
            if(data)
            {
                return *(int*)data;
            }
            return 0;
        }
        void setParamerteri(unsigned index, int value)
        {
            setParameter(index, ParameterType::Int, &value);
        }

//	void 		setParameterb(unsigned index, bool value);
//	void 		setParameterc(unsigned index, char value);
//	void 		setParameters(unsigned index, short value);
//	void 		setParameteri(unsigned index, int value);
//	void 		setParameterf(unsigned index, float value);
//	void 		setParameterd(unsigned index, double value);
//	bool 		getParameterb(unsigned index);
//	char 		getParameterc(unsigned index);
//	short 		getParameters(unsigned index);
//	int 		getParameteri(unsigned index);
//	float 		getParameterf(unsigned index);
//	double 		getParameterd(unsigned index);
//	unsigned 	getParameterData(char* data);
//	unsigned 	setParameterData(char* data, unsigned size);
};

#endif // PARAMETER_H
