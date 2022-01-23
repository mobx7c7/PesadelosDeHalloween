/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-13
***********************************************************************/
#ifndef RENDERER_H
#define RENDERER_H

//#include "gl_includes.h"
//#include "Window.h"
//#include "Graphics.h"
//#include <thread>

class GraphicsRenderer
{
	private:

		static GraphicsRenderer* instance;

	protected:

		GraphicsRenderer();
		virtual ~GraphicsRenderer();

	public:

		static GraphicsRenderer*    getInstance();
		static void                 destroyInstance();

		virtual int                 init() = 0;
		virtual int                 destroy() = 0;
		virtual int                 setup() = 0;
		virtual int                 start() = 0;
		virtual int                 stop() = 0;

};

#endif // RENDERER_H
