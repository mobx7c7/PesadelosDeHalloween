/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2014-11-28
***********************************************************************/
#include "GLObject.h"
#include "gl_includes.h"

unsigned toGLEnumDataType(DataType type)
{
	switch(type)
	{
		case DataType::Byte:     return GL_BYTE;
		case DataType::UByte:    return GL_UNSIGNED_BYTE;
		case DataType::Short:    return GL_SHORT;
        case DataType::UShort:   return GL_UNSIGNED_SHORT;
		case DataType::Int:      return GL_INT;
		case DataType::UInt:     return GL_UNSIGNED_INT;
        case DataType::Float:    return GL_FLOAT;
		case DataType::Double:   return GL_DOUBLE;
		default:                 return 0;
	}
}

//unsigned toGLEnumColorFormat(DataType type)
//{
//	switch(type)
//	{
//		case DataType::Byte:     return GL_BYTE;
//		case DataType::UByte:    return GL_UNSIGNED_BYTE;
//		case DataType::Short:    return GL_SHORT;
//        case DataType::UShort:   return GL_UNSIGNED_SHORT;
//		case DataType::Int:      return GL_INT;
//		case DataType::UInt:     return GL_UNSIGNED_INT;
//        case DataType::Float:    return GL_FLOAT;
//		case DataType::Double:   return GL_DOUBLE;
//		default:                 return 0;
//	}
//}

GLObject::GLObject()
{

}

GLObject::~GLObject()
{

}

unsigned GLObject::getObjectID()
{
	return objectID;
}
