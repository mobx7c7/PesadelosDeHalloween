/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-21
***********************************************************************/
#ifndef OGLGRAPHICS_H
#define OGLGRAPHICS_H

#include "App/Graphics.h"
#include "Common/Canvas.h"
#include "Common/Effect.h"
#include "Common/Text.h"

class OGLGraphics : public Graphics
{
    protected:

        Font*           font        = 0;
        Texture*        texture     = 0;
        Effect*         effect      = 0;
        Framebuffer*    framebuffer = 0;

        Shader*         solidShader = 0;

        CanvasInstance* canvas;
        glm::vec2       res;
        glm::mat4       m_src;
        glm::mat4       m_dst;

        OGLTextRenderer* textRenderer = 0;

        float color[4];

	public:

		OGLGraphics();
		~OGLGraphics();

		void temp_reloadShaders();

		void clearFramebuffer(float r, float g, float b, float a);
		void setColor(float r, float g, float b, float a);
		void setFramebuffer(Framebuffer* fbo);
		void setEffect(Effect* effect);
		//void setFont(Font* font);
		//void setTexture(Texture* texture);

		void getPixel(int x, int y, float* pixel);

        void drawText(string text, double x, double y);
        void drawRect(double x, double y, double width, double height);
		void drawTexture(Texture*, float, float);
		void drawTexture(Texture*, float, float, float, float);
		void drawTexture(Texture*, float, float, float, float, float, float, float, float);

		void drawText(string text, float px, float py, float sx, float sy);
};

#endif // OGLGRAPHICS_H
