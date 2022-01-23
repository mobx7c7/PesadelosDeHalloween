/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-16
***********************************************************************/
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "GL/Framebuffer.h"
#include "GL/Shader.h"
#include "Common/Effect.h"
//#include "Common/Text.h"
#include "Window.h"

class Graphics
{
	protected:

		static Graphics* instance;
		Graphics();
		virtual ~Graphics();

	public:

	    virtual void temp_reloadShaders() = 0;

		static Graphics*    getInstance();
		static void         destroyInstance();

		virtual void        clearFramebuffer(float, float, float, float) = 0;
		virtual void        setColor(float, float, float, float) = 0;
		virtual void        setFramebuffer(Framebuffer*) = 0;
		virtual void        setEffect(Effect*) = 0;
		//virtual void        setFont(Font* font) = 0;
		//virtual void        setTexture(Texture* texture) = 0;
        virtual void        getPixel(int x, int y, float* pixel) = 0;
        virtual void        drawText(string text, double x, double y) = 0;
		virtual void        drawRect(double x, double y, double width, double height) = 0;
        virtual void        drawTexture(Texture*, float, float) = 0;
		virtual void        drawTexture(Texture*, float, float, float, float) = 0;
		virtual void        drawTexture(Texture*, float, float, float, float, float, float, float, float) = 0;
};

//class BeamGraphics : public Graphics
//{
//    //VectorGraphics
//    //VectorBeam
//    //VectorXY
//    //Vector
//};


//class NullGraphics : public Graphics
//{
//	public:
//		NullGraphics();
//		~NullGraphics();
//        void clearFramebuffer(float, float, float, float);
//		void setFramebuffer(FrameBuffer* fbuf);
//		void setEffect(Effect*);
//		void setColor(float, float, float, float);
//		//void setShader(Shader*) = 0;
//		void drawPoint(double, double);
//		void drawLine(double, double, double, double);
//		void drawRect(double, double, double, double);
//		void drawOval(double, double, double, double);
//		void drawTexture(Texture*, float, float);
//		void drawTexture(Texture*, float, float, float, float);
//		void drawTexture(Texture*, float, float, float, float, float, float, float, float);
//};



#endif // GRAPHICS_H
