/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-18
***********************************************************************/
#include "Sound/Buffer.h"
#include <cstring>

namespace Sound
{
	Buffer::Buffer(unsigned size, const char* srcData) : size(size), data(new char[size])
	{
        memcpy(data, srcData, size);
	}
	Buffer::Buffer() : size(0), data(0)
	{

	}
	Buffer::~Buffer()
	{
		delete[] data;
	}
	char* Buffer::getData()
	{
		return data;
	}
	unsigned Buffer::getSize()
	{
		return size;
	}
} // namespace Sound
