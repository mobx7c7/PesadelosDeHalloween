/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2014-11-27
***********************************************************************/
#ifndef TEXTURE_H
#define TEXTURE_H

#include "GLObject.h"
#include "gl_includes.h"
#include <string>
#include <memory>

class DefaultTexture;

class Texture : public GLObject
{
	protected:

		unsigned _width;
		unsigned _height;
		unsigned _levels;
		unsigned _textureFormat;
		unsigned _pixelFormat;
		unsigned _target;
		unsigned _wrapS;
		unsigned _wrapT;
		unsigned _minFilter;
		unsigned _magFilter;
		unsigned _dataType;

		int getTexLevelParam(int level, int param);
		int getTexParam(int param);
		void setTexParam(int param, int value);

	public:

        Texture();
		Texture(int width, int height, int textureFormat, int pixelFormat, int dataType, const void* dataPtr);
		virtual ~Texture();
		void            setTexture(int target, int width, int height, int textureFormat, int pixelFormat, int minFilter, int magFilter, int wrapS, int wrapT, int dataType, const void* dataPtr);
		void            setBuffer(int level, int offx, int offy, int width, int height, int pixelFormat, int dataType, const void* dataPtr);
        void            setMinFilter(int param_value);
        void            setMagFilter(int param_value);
        void            setWrapS(int param_value);
        void            setWrapT(int param_value);
		unsigned 	    getWidth();           // GL_TEXTURE_1D
		unsigned 	    getHeight();          // GL_TEXTURE_2D
		unsigned        getLevels();          // GL_TEXTURE_3D
		unsigned 	    getTextureFormat();   // GL_RGBA8..
		unsigned 	    getPixelFormat();     // GL_RGBA...
		unsigned 	    getTarget();          // GL_TEXTURE_2D...
		unsigned 	    getMinFilter();       // GL_LINEAR, GL_NEAREST...
		unsigned 	    getMagFilter();       // GL_LINEAR, GL_NEAREST...
		unsigned 	    getWrapS();           // GL_CLAMP_TO_BORDER, GL_REPEAT...
		unsigned 	    getWrapT();           // GL_CLAMP_TO_BORDER, GL_REPEAT...
		void 		    bind();
		void 		    unbind();
};

class DefaultTexture : public Texture
{
private:
    char renderPixel(unsigned x, unsigned y);
    void renderImage(unsigned width, unsigned height, unsigned channels, char* data);
//    float renderCircularPattern(float x, float y)
//    {
//        float dist = sqrt(x*x + y*y);
//        float s = sin(dist * 200);
//        return (s + 1.0) * 0.5;
//    }
public:
    DefaultTexture();
    ~DefaultTexture();
};

#include <map>

typedef map<string, Texture*>              TextureMap;
typedef map<string, Texture*>::iterator    TextureMapIterator;
typedef pair<string, Texture*>             TextureMapPair;

class TextureManager
{
private:

    static TextureManager*  instance;
    TextureMap              textureMap;
    Texture*                default_texture;
    TextureManager();
    ~TextureManager();

public:

    static TextureManager*  getInstance();
    static void             destroyInstance();
    bool                    insert(string name, Texture* t);
    bool                    destroy(string name);
    bool                    contains(string name);
    Texture*                get(string name);
    void                    clear();
};

class TextureLoader
{
private:

    static TextureLoader*   instance;
    Texture*                placeholder;
    TextureLoader();
    ~TextureLoader();

public:

    static TextureLoader*   getInstance();
    static void             destroyInstance();
    Texture*                getDefault();
    Texture*                loadFile(std::string file);
    Texture*                loadBMPFile(std::string file);
    Texture*                loadRAWFile(std::string file, int width, int height);
};

typedef shared_ptr<Texture> TexturePtr;

#endif // TEXTURE_H
