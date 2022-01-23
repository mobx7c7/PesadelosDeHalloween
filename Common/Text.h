/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-31
***********************************************************************/
#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include "Graphics.h"
#include "GL/Texture.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <vector>

using std::vector;

class OGLTestText
{
private:

    static OGLTestText* instance;
    OGLTestText()
    {
        int error;

        error = FT_Init_FreeType(&library);
        if(error != FT_Err_Ok)
        {
            cout << "[OGLTestText] Error FT_Init_FreeType (code:" << error << ")" << endl;
            return;
        }

        //----------------------------------------------------------//

        error = FT_New_Face(library, "C://Windows//Fonts//Arial.ttf", 0, &face);
        if(error != FT_Err_Ok)
        {
            cout << "[OGLTestText] Error FT_New_Face: ";
            switch(error)
            {
                case FT_Err_Unknown_File_Format:
                    cout << "Format Unknown";
                    break;
                default:
                    cout << "File not found";
            }
            cout << " (code:" << error << ")" << endl;
            return;
        }

        //----------------------------------------------------------//

        FT_Set_Pixel_Sizes(face, 0, 24);

        for(unsigned i=32; i<256; i++)
        {
            error = FT_Load_Char(face, i, FT_LOAD_RENDER);
            if(error)
            {
                cout << "[OGLTestText] Error FT_Load_Char (code:" << error << ")" << endl;
                return;
            }

            glyph = face->glyph;

            //cout << glyph->bitmap.buffer;
            //cout << glyph->bitmap.width << endl;
            //cout << glyph->bitmap.rows << endl;
            //cout << glyph->bitmap_left << endl;
            //cout << glyph->bitmap_top << endl;
            //cout << glyph->advance.x << endl;
            //cout << glyph->advance.y << endl;

            // ISTO É IMPORTANTE, NÃO REMOVER O "glPixelStorei"!!!
            // Define o alinhamento do pixel
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // 1 = alinhado por byte
            glyphTextures.push_back(new Texture(glyph->bitmap.width,
                                                glyph->bitmap.rows,
                                                GL_RED,
                                                GL_RED,
                                                GL_UNSIGNED_BYTE,
                                                glyph->bitmap.buffer));
        }
    }
    ~OGLTestText()
    {
        for(Texture* texture : glyphTextures) delete texture;
        glyphTextures.clear();
    }

protected:

    FT_Library          library;
    FT_Face             face;
    FT_GlyphSlot        glyph;
    vector<Texture*>    glyphTextures;

public:

    static OGLTestText* getInstance()
    {
        if(!instance) instance = new OGLTestText();
        return instance;
    }
    //void render(string text, float posx, float posy, float sclx, float scly) // scl seria 1.0f/dimensão da tela (width, height)
    void render(Graphics* g) // scl seria 1.0f/dimensão da tela (width, height)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        unsigned x=0, y=0;
        for(Texture* glyph : glyphTextures)
        {
            g->drawTexture(glyph, 20*(x%16), 20*y);
            x++;
            y = (x/16);
        }

        glDisable(GL_BLEND);
    }
};


class Font
{
private:

    Texture* texture;
    unsigned charw      = 8;
    unsigned charh      = 8;
    unsigned tilew      = 16;
    unsigned tileh      = 14;

public:

    Font(Texture* texture, unsigned charw, unsigned charh, unsigned tilew, unsigned tileh) :
        texture(texture),
        charw(charw),
        charh(charh),
        tilew(tilew),
        tileh(tileh)
    {

    }
    ~Font()
    {
        delete texture;
    }
    Texture* getTexture()
    {
        return texture;
    }
    unsigned getCharWidth() const
    {
        return charw;
    }
    unsigned getCharHeight() const
    {
        return charh;
    }
    unsigned getTileWidth() const
    {
        return tilew;
    }
    unsigned getTileHeight() const
    {
        return tileh;
    }
};

class BitmapFont
{

};

class OGLTestText2
{
private:

    static OGLTestText2* instance;

protected:

    Font*           font;
    unsigned        tablength  = 4;
    unsigned        lin        = 0;
    unsigned        col        = 0;

    unsigned        cursorx    = 0;
    unsigned        cursory    = 0;

    unsigned        select_start = 0;
    unsigned        select_end = 0;

    OGLTestText2()
    {
        Texture* atlas = TextureLoader::getInstance()->loadBMPFile("res//AmigaTopazFonte3.bmp");
        atlas->setMagFilter(GL_NEAREST);
        atlas->setMinFilter(GL_NEAREST);
        atlas->setWrapS(GL_CLAMP_TO_BORDER);
        atlas->setWrapT(GL_CLAMP_TO_BORDER);
        font = new Font(atlas, 8, 8, 16, 14);
    }
    ~OGLTestText2()
    {
        delete font;
    }

public:

    static OGLTestText2* getInstance()
    {
        if(!instance) instance = new OGLTestText2();
        return instance;
    }

    void drawText(string text, float posx, float posy, float sclx, float scly, Graphics* g)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        lin = 0, col = 0;

        const char *p;// = text.c_str();

        //for(unsigned i=0; i<text.size(); i++)

        for(p = text.c_str(); *p; p++)
        {
            char c = (char)*p >= 32 || (char)*p <= 255 ? (char)*p - 32 : 0;

            switch((char)*p)
            {
                case '\n':
                    col=0;
                    lin++;
                    break;
                case '\t':
                    col+=tablength;
                    break;
                default:
                    unsigned charw = font->getCharWidth();
                    unsigned charh = font->getCharHeight();
                    unsigned tilew = font->getTileWidth();
                    unsigned tileh = font->getTileHeight();


                    float w1 = charw * sclx;
                    float h1 = charh * scly;
                    float x1 = (w1 * col) + posx;
                    float y1 = (h1 * lin) + posy;

//                    float x1 = (charw * sclx * col) + posx;
//                    float y1 = (charh * scly * lin) + posy;
//                    float w1 = charw * sclx;
//                    float h1 = charh * scly;

                    float x2 = charw * (c%tilew);
                    float y2 = charh * (c/tilew%tileh);
                    float w2 = charw;
                    float h2 = charh;

                    g->drawTexture(font->getTexture(), x1, y1, w1, h1, x2, y2, w2, h2);
                    col++;
            }
        }

        glDisable(GL_BLEND);
    }
};


class OGLConsole
{
	private:

		static OGLConsole* instance;

        Font* font = 0;
		unsigned b_width = 80, b_height = 300, b_length = 24000;
		unsigned w_width = 80, w_height = 25, w_length = 2000;
		unsigned currentOffset = 0;
		char* buffer = 0;
		char color = 0x09;
//        char color_lut[]    // Standard VGA
//		{
//			0,   0,   0,    // black
//			170, 0,   0,    // red
//			0,   170, 0,    // green
//			170, 85,  0,    // yellow
//			0,   0,   170,  // blue
//			170, 0,   170,  // magenta
//			0,   170, 170,  // cyan
//			170, 170, 170,  // gray
//			85,  85,  85,   // bright black
//			255, 85,  85,   // bright red
//			85,  255, 85,   // bright green
//			255, 255, 85,   // bright yellow
//			85,  85,  255,  // bright blue
//			255, 85,  255,  // bright magenta
//			85,  255, 255,  // bright cyan
//			255, 255, 255,  // bright white
//		};

		OGLConsole()
		{
            Texture* atlas = TextureLoader::getInstance()->loadBMPFile("res//AmigaTopazFonte3.bmp");
            atlas->setMagFilter(GL_NEAREST);
            atlas->setMinFilter(GL_NEAREST);
            atlas->setWrapS(GL_CLAMP_TO_BORDER);
            atlas->setWrapT(GL_CLAMP_TO_BORDER);
            font = new Font(atlas, 8, 8, 16, 14);

			buffer = new char[b_length * 2]; // caracter + color
			clear();
		}
		~OGLConsole()
		{
		    delete font;
			delete[] buffer;
		}

	public:

		static OGLConsole* getInstance()
		{
			if(!instance) instance = new OGLConsole();
			return instance;
		}

		void setColor(char color)
		{
			this->color = color;
		}

		void write(char* data, unsigned length, unsigned offset)
		{
			for(int i=0; i<length; i++)
			{
				unsigned lin = currentOffset/b_height;
				unsigned col = currentOffset%b_width;
				char* b = &buffer[(lin*b_width*2)+(col*2)];
				b[0] = data[i];
				b[1] = color;
				currentOffset = (currentOffset+1)%b_length;
			}
		}

		void clear()
		{
			for(int i=0; i<b_length; i++)
			{
				unsigned lin = i/b_height;
				unsigned col = i%b_width;
				char* b = &buffer[(lin*b_width*2)+(col*2)];
				b[0] = (col%(255-32))+32; // ' '
				b[1] = color;
			}
		}
		void display(float posx, float posy, float sclx, float scly, Graphics* g)
		{
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            unsigned lin = 0;
            unsigned col = 0;
            unsigned off = 0;

            unsigned charw, charh, tilew, tileh;
            float _posx, _posy;

            charw  = font->getCharWidth();
            charh  = font->getCharHeight();
            tilew  = font->getTileWidth();
            tileh  = font->getTileHeight();

            for(int i=0; i<=w_length; i++)
            {
                char* b = &buffer[(lin*b_width*2)+(col*2)];
                char  c = b[0] >= 32 || b[0] <= 255 ? b[0] - 32 : 0;

                _posx  = (charw * sclx * col) + posx;
                _posy  = (charh * scly * lin) + posy;

                g->drawTexture(font->getTexture(),
                               _posx,
                               _posy,
                                charw * sclx,
                                charh * scly,
                                charw * (c%tilew),
                                charh * (c/tilew%tileh),
                                charw,
                                charh);


                lin = i/b_width;
                col = i%b_width;
            }
		}

//		void display(float posx, float posy, float sclx, float scly, Graphics* g)
//        {
//            glEnable(GL_BLEND);
//            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//            unsigned lin = 0;
//            unsigned col = 0;
//            unsigned off = 0;
//
//            for(unsigned i=0; i<b_length; i++)
//            {
//				char* b = &buffer[(lin*b_width*2)+(col*2)];
//                char  c = b[0] >= 32 || b[0] <= 255 ? b[0] - 32 : 0;
//
//                switch(b[0])
//                {
//                    case '\n':
//
//                        col=0;
//                        lin++;
//                        break;
//
//                    case '\t':
//
//                        col += 4;
//                        break;
//
//                    default:
//
//                        unsigned charw  = font->getCharWidth();
//                        unsigned charh  = font->getCharHeight();
//                        unsigned tilew  = font->getTileWidth();
//                        unsigned tileh  = font->getTileHeight();
//                        float   _posx   = (charw * sclx * col) + posx;
//                        float   _posy   = (charh * scly * lin) + posy;
//
//                        g->drawTexture(font->getTexture(),
//                                       _posx,
//                                       _posy,
//                                       charw * sclx,
//                                       charh * scly,
//                                       charw * (c%tilew),
//                                       charh * (c/tilew%tileh),
//                                       charw,
//                                       charh);
//
//                        off++;
//                        col = off%b_width;
//                }
//            }
//
//            glDisable(GL_BLEND);
//        }
};

#include "GL/VertexArray.h"
#include "GL/VertexBuffer.h"
#include "GL/Shader.h"
#include <vector>
#include <sstream>

class OGLConsole2
{
private:

    static OGLConsole2* instance;

    VertexArray*        vao = 0;
    VertexBuffer*       vbo = 0;
    Shader*             program = 0;
    Font*               font = 0;

    char*   buffer      = 0;
    int     bufferw     = 0;
    int     bufferh     = 0;
    int     bufferl     = 0;
    int     off         = 0;

    OGLConsole2()
    {
        Texture* atlas = TextureLoader::getInstance()->loadBMPFile("res//AmigaTopazFonte3.bmp");
        atlas->setMagFilter(GL_LINEAR);
        atlas->setMinFilter(GL_LINEAR);
        atlas->setWrapS(GL_CLAMP_TO_EDGE);
        atlas->setWrapT(GL_CLAMP_TO_EDGE);
        font = new Font(atlas, 8, 8, 16, 14);

        program = new Shader();
        program->loadShaderFile("res//Shaders//console.vert.glsl", ShaderType::Vertex);
        program->loadShaderFile("res//Shaders//console.geom.glsl", ShaderType::Geometry);
        program->loadShaderFile("res//Shaders//console.frag.glsl", ShaderType::Fragment);
        program->link();

        bufferw = 80;
        bufferh = 60;
        bufferl = bufferw*bufferh;
        buffer  = new char[bufferl];
        clear();

        vbo = new VertexBuffer(VertexBufferTarget::ArrayBuffer);
    }
    ~OGLConsole2()
    {
        delete      vbo;
        delete[]    buffer;
        delete      program;
        delete      font;
    }

public:

    static OGLConsole2* getInstance()
    {
        if(!instance) instance = new OGLConsole2();
        return instance;
    }

    void clear()
    {
        memset(buffer, 127, bufferl);
    }

    std::stringstream ss;

    void print(string text)
    {
//        static int _count = 0;
//        ss.str("");
//        ss << _count++;
//        memcpy(&buffer[off], ss.str().c_str(), ss.str().size());
//        off += bufferw;

        int doff = bufferl-off; // delta offset
        if(doff > text.size())
        {
            memcpy(&buffer[off], text.c_str(), text.size());
            off += text.size();
        }
        else
        {
            memcpy(&buffer[off], text.c_str(), doff);
            off = 0;
            memcpy(&buffer[off], &text.c_str()[doff], text.size()-doff);
            off += text.size()-doff;
        }
        off = off%bufferl;
    }

    void drawText(string text, float posx, float posy, float scalex, float scaley)
    {
        glActiveTexture(GL_TEXTURE0);
        Texture* atlas = font->getTexture();
        atlas->bind();
            program->bind();

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                program->enableVertexAttribArray("character");
                program->setVertexAttribIPointer("character", 1, GL_UNSIGNED_BYTE, 1, text.c_str());

                //program->setUniform1i("offset", off);
                program->setUniform2i("resolution", 1280, 583);
                program->setUniform2i("buffer_size", bufferw, bufferh);
                program->setUniform2i("atlas_size", font->getTileWidth(), font->getTileHeight());
                program->setUniform2i("char_size", font->getCharWidth(), font->getCharHeight());
                program->setUniform2f("char_scale", scalex, scaley);
                program->setUniform2i("position", posx, posy);

                glDrawArrays(GL_POINTS, 0, text.size());

            program->unbind();
        atlas->unbind();
    }

    void draw(float posx, float posy, float scalex, float scaley)
    {
        for(int i=0; i<bufferh; i++)
        {
            drawText(string(&buffer[bufferw*i], bufferw),
                     posx,
                     //posy + font->getCharHeight()*(bufferh-1-((bufferh-1-i+(off/bufferw))%bufferh)),
                     posy + font->getCharHeight()*(bufferh-1-(bufferh-i+off/bufferw)%bufferh),
                     scalex,
                     scaley);
        }

//         drawText(string(buffer, bufferl), 0, 0, scalex, scaley);
    }
};


// Nota: Experimental!!!
// Nota: Experimental!!!
// Nota: Experimental!!!
// Nota: Experimental!!!

class OGLTextRenderer
{
private:

	class Glyph
	{
		public:
            Texture* texture = 0;
            unsigned width = 0;
            unsigned rows = 0;
            unsigned left = 0;
            unsigned top = 0;
            unsigned advance_x = 0;
            unsigned advance_y = 0;
			Glyph(){}
			~Glyph() { if(texture) delete texture; }
	};

    static OGLTextRenderer* instance;

    int                 error;
    FT_Library          library;
    FT_Face             face;
    vector<Glyph*>      glyphTextures;

    Texture*            atlas;

    OGLTextRenderer();
     ~OGLTextRenderer();

public:

    static OGLTextRenderer* getInstance();
    static void             destroyInstance();
    int     loadFontFile(string file);
    int     setFontSize(int font_size);
    void    clear();
    void    drawText(string text, float posx, float posy, Graphics* g);
    void    render(Graphics* g);

};
#endif // TEXT_H
