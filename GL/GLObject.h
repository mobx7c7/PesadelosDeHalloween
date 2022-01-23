/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2014-11-28
***********************************************************************/
#ifndef GLOBJECT_H
#define GLOBJECT_H

enum DataType
{
	Byte,
	UByte,
	Short,
	UShort,
	Int,
	UInt,
	Float,
	Double,
};

//enum ColorFormat
//{
//	Byte,
//	UByte,
//	Short,
//	UShort,
//	Int,
//	UInt,
//	Float,
//	Double,
//};


unsigned toGLEnumDataType(DataType type);

class GLObject
{
	protected:

        unsigned objectID;
		GLObject();

	public:

        virtual         ~GLObject();
		unsigned        getObjectID();
		virtual void    bind() = 0;
		virtual void    unbind() = 0;
};

#endif // GLOBJECT_H
