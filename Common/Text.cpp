/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-31
***********************************************************************/
#include "Text.h"

OGLTestText* OGLTestText::instance = 0;

OGLTestText2* OGLTestText2::instance = 0;

OGLConsole* OGLConsole::instance = 0;

OGLConsole2* OGLConsole2::instance = 0;









OGLTextRenderer* OGLTextRenderer::instance = 0;

OGLTextRenderer::OGLTextRenderer()
{
	if((error = FT_Init_FreeType(&library)) != FT_Err_Ok)
	{
		cout << "[OGLTextRenderer] Error FT_Init_FreeType (code:" << error << ")" << endl;
		return;
	}

	loadFontFile("C://Windows//Fonts//Arial.ttf");
	setFontSize(20);
}

OGLTextRenderer::~OGLTextRenderer()
{
	clear();
	if((error = FT_Done_FreeType(library)) != FT_Err_Ok)
	{
		cout << "[OGLTextRenderer] Error FT_Done_FreeType (code:" << error << ")" << endl;
		return;
	}
}

int OGLTextRenderer::loadFontFile(string file)
{
	if((error = FT_New_Face(library, file.c_str(), 0, &face)) != FT_Err_Ok)
	{
		cout << "[OGLTextRenderer] Error FT_New_Face: ";
		switch(error)
		{
			case FT_Err_Unknown_File_Format:
				cout << "Format Unknown";
				break;
			default:
				cout << "File not found";
		}
		cout << " (code:" << error << ")" << endl;
		return error;
	}
	return 1;
}

int OGLTextRenderer::setFontSize(int font_size)
{
	FT_Set_Pixel_Sizes(face, 0, font_size);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // 1 = alinhado por byte

    unsigned offx = 0, offy = 0;
	unsigned atlas_w = 0, atlas_h = 0;
	unsigned curr_atlas_w = 0, curr_atlas_h = 0;

	for(int i=0; i<256; i++)
	{
		if((error = FT_Load_Char(face, i, FT_LOAD_RENDER)))
		{
			cout << "[OGLTextRenderer] Error FT_Load_Char (code:" << error << ")" << endl;
			return error;
		}

		FT_GlyphSlot glyph = face->glyph;

		Glyph* gly      = new Glyph();

		gly->texture    = new Texture(glyph->bitmap.width, glyph->bitmap.rows, GL_RGBA, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);
		gly->width      = glyph->bitmap.width;
		gly->rows       = glyph->bitmap.rows;
		gly->left       = glyph->bitmap_left;
		gly->top        = glyph->bitmap_top;
		gly->advance_x  = glyph->advance.x;
		gly->advance_y  = glyph->advance.y;

		glyphTextures.push_back(gly);
//
//		if(offx < 32)
//        {
//            curr_atlas_w += glyph->bitmap.width;
//            offx++;
//        }
//        else
//        {
//            if(atlas_w < curr_atlas_w)
//            {
//                atlas_w = curr_atlas_w;
//            }
//            curr_atlas_w = 0;
//            curr_atlas_h += 20;
//            offx = 0;
//            offy++;
//        }
        atlas_w += glyph->bitmap.width;
	}

	atlas = new Texture(atlas_w, font_size, GL_RGBA, GL_RED, GL_UNSIGNED_BYTE, 0);

	offx = offy = 0;
	for(int i=0; i<256; i++)
    {
        if((error = FT_Load_Char(face, i, FT_LOAD_RENDER)))
		{
			cout << "[OGLTextRenderer] Error FT_Load_Char (code:" << error << ")" << endl;
			return error;
		}

		FT_GlyphSlot glyph = face->glyph;

        atlas->setBuffer(0,
                         offx,
                         offy,
                         glyph->bitmap.width,
                         glyph->bitmap.rows,
                         GL_RED,
                         GL_UNSIGNED_BYTE,
                         glyph->bitmap.buffer);

        offx+=glyph->bitmap.width;
    }

	return 1;
}

void OGLTextRenderer::clear()
{
	for(Glyph* glyph : glyphTextures) if(glyph) delete glyph;
	glyphTextures.clear();
}

OGLTextRenderer* OGLTextRenderer::getInstance()
{
	if(!instance) instance = new OGLTextRenderer();
	return instance;
}

void OGLTextRenderer::destroyInstance()
{
	if(instance) delete instance;
	instance = 0;
}

void OGLTextRenderer::drawText(string text, float posx, float posy, Graphics* g)
{
	if(text.empty()) return;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//	g->drawTexture(atlas, 0, 0);

	int offx = posx, offy = posy;
	for(int i=0; i<text.size(); i++)
	{
		Glyph* glyph = glyphTextures[ (unsigned char)text[i] ];
        if(glyph)
        {
            if((unsigned char)text[i] == '\n')
            {
                offy += 20;
                offx = posx;
            }
            else
            {
                g->drawTexture(glyph->texture, offx + glyph->left, offy - glyph->top);
                offx += glyph->advance_x >> 6;
            }
        }
	}
	glDisable(GL_BLEND);
}
void OGLTextRenderer::render(Graphics* g) // scl seria 1.0f/dimensão da tela (width, height)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	unsigned i=0, x=0, y=0;

	for(Glyph* glyph : glyphTextures)
	{
		g->drawTexture(glyph->texture, 20*x, 20*y);
		x = (i%16);
		y = (i/16);
		i++;
	}

	glDisable(GL_BLEND);
}

