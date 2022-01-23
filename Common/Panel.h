/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-02
***********************************************************************/
#ifndef PANEL_H
#define PANEL_H

#include <map>
#include <list>
#include <utility>
#include <string>

template<typename T>
class Panel
{
	private:

		std::string                 name;
		std::map<std::string, T*>   elements;
		T*                          defaultElement;

	protected:

		void setDefault(std::string name)
		{
			typename std::map<std::string, T*>::iterator it = elements.find(name);
			if (it != elements.end())
			{
				defaultElement = it->second;
			}
		}

	public:

        Panel(std::string name) : name(name)
		{

		}

		~Panel()
		{
			clear();
		}

		void insert(std::string name, T* element)
		{
			typename std::map<std::string, T*>::iterator it = elements.find(name);
			if (it != elements.end())
			{
				delete it->second;
				it->second = element;
				return;
			}
			elements.insert( std::make_pair(name, element) );
		}

		void remove(std::string name)
		{
			typename std::map<std::string, T*>::iterator it = elements.find(name);
			if (it != elements.end())
			{
				delete it->second;
				elements.erase(it);
			}
		}

		void clear()
		{
			typename std::map<std::string, T*>::iterator it;
			for(it = elements.begin(); it != elements.end(); it++)
			{
				delete it->second;
			}
			elements.clear();
		}

		T* get(std::string name)
		{
			typename std::map<std::string, T*>::iterator it = elements.find(name);
			if (it != elements.end())
			{
				return it->second;
			}
			return defaultElement;
		}

		T* getDefault()
		{
			return defaultElement;
		}

		unsigned getSize()
		{
			return elements.size();
		}

		std::string getManagerName()
		{
			return name;
		}

		std::list<std::string> getNameList()
		{
			std::list<std::string> names;
			typename std::map<std::string, T*>::iterator it;
			for(it = elements.begin(); it != elements.end(); it++)
			{
				names.push_back(it->first);
			}
			return names;
		}
};
#endif // PANEL_H
