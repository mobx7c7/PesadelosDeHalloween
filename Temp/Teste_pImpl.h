/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-05-27
***********************************************************************/
#ifndef TESTE_PIMPL_H
#define TESTE_PIMPL_H

/*
#include <map>

namespace Layer
{
//    class Object
//    {
//        virtual void processParams(double deltaTime);
//        virtual void processDisplay(const Graphics &g);
//        virtual void processEvents(const Event &e);
//    };

	class Impl : public Object
	{
		protected:

			map<string, Object&> objects;

		public:

			Impl(string name, Impl& parent) : Object(name, (Object&)parent) {}
			~Impl() {}
			void 	        create(string name)
			void 	        destroy(string name);
			void            clear();
			Object&	        get(string name);
			//bool	        isDefault();
            //Object&	        getParent();
			//const string      getName();
	};


	class Manager
	{
		private:

			static Manager* instance;

		protected:

			map<string, Impl> layers;

		public:

			static void     initInstance();
			static void     deleteInstance();
			static Manager* getInstance();
			//-----------------------------------------------//
			void create(string name)
			{
				map<string, Impl>::iterator layer = layers.find(name);
				if(layer != layers.end())
				{
					name += "_1";
				}
				layers.insert( std::pair<string, Impl>(name, Impl(0)) );
			}
			void destroy(string name)
			{
				map<string, Impl>::iterator layer = layers.find(name);
				if(layer != layers.end())
				{
					layers.erase(layer);
				}
			}
			void clear()
			{
				layers.clear();
			}
			Holder get(string name)
			{
				map<string, Impl>::iterator layer = layers.find(name);
				if(layer != layers.end())
				{
					return Holder(layer->second);
				}
				return Holder(0);
			}
	};
}

//namespace Scn
//{
//    class Manager
//	{
//		private:
//			static Manager* instance;
//		protected:
//			map<string, Layer::Holder> scenes;
//		public:
//			void 	        insertScene(string name);
//			void 	        removeScene(string name);
//			Layer::Holder 	getScene(string name)
//			Layer::Holder 	getLastScene();
//			Layer::Holder	getCurrentScene();
//			Layer::Holder	getDefaultScene();
//	};
//}

*/

#endif // TESTE_PIMPL_H
