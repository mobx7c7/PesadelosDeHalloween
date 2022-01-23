/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-30
***********************************************************************/
#ifndef OBJECT_H
#define OBJECT_H

#include <string>
using std::string;

class Object
{
	private:

		static unsigned nextIdent;
		unsigned        ident;

		string          name;
		Object*         parent;

	protected:

		Object(string name, Object* parent);
//		Object(string name);
//		Object();

	public:

		virtual         ~Object();
		unsigned        getIdent();
		string&         getName();
		void            setName(string name);
		Object*         getParent();
		void            setParent(Object* parent);

//		virtual void    getParameters(string parameters);
//		virtual string  setParameters();

};

//class Logger
//{
//
//};


#endif // OBJECT_H
