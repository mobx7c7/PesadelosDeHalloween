/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2014-11-27
***********************************************************************/
#include "Texture.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "gl_includes.h"
#include "FreeImage.h"

Texture::Texture()
{
    glGenTextures(1, &objectID);
}

Texture::Texture(int width, int height, int textureFormat, int pixelFormat, int dataType, const void* dataPtr) :
    Texture()
{
	setTexture(GL_TEXTURE_2D,
               width,
               height,
               textureFormat,
               pixelFormat,
               GL_LINEAR, //GL_NEAREST,
               GL_LINEAR, //GL_NEAREST,
               GL_CLAMP_TO_BORDER,
               GL_CLAMP_TO_BORDER,
               dataType,
               dataPtr);
}

Texture::~Texture()
{
	if(glIsTexture(objectID))
	{
		glDeleteTextures(1, &objectID);
	}
}

void Texture::setTexture(int target, int width, int height, int textureFormat, int pixelFormat, int minFilter, int magFilter, int wrapS, int wrapT, int dataType, const void* dataPtr)
{
//	_width          = width;    // largura
//	_height         = height;   // altura
	_levels         = 0;        // profundidade?
	_dataType       = dataType;
//	_textureFormat  = textureFormat;
	_pixelFormat    = pixelFormat;
	_target         = target;
//	_minFilter      = minFilter;
//	_magFilter      = magFilter;
//	_wrapS          = wrapS;
//	_wrapT          = wrapT;

    // Nota: substituindo por funções "get" de parametros do OpenGL...
    // Nota: substituindo por funções "get" de parametros do OpenGL...
    // Nota: substituindo por funções "get" de parametros do OpenGL...

	glBindTexture(_target, objectID);

    glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameteri(_target, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(_target, GL_TEXTURE_WRAP_T, wrapT);
    // glTexImage2D — especifica uma imagem de textura 2D
    glTexImage2D(_target,
                 _levels,
                 textureFormat, //TextureFormat::RGB8
                 width,
                 height,
                 0,             //border: This value must be 0.
                 _pixelFormat,  //TexturePixelFormat::RGBA
                 _dataType,     //TexturePixelDataType::U8
                 dataPtr);

	glBindTexture(_target, 0);
}

int Texture::getTexLevelParam(int level, int param)
{
    int value;
    bind();
    glGetTexLevelParameteriv(_target, level, param, &value);
	return value;
}

int Texture::getTexParam(int param)
{
    int value = 0;
    bind();
    glGetTexParameteriv(_target, param, &value);
	return value;
}

void Texture::setTexParam(int param, int value)
{
	bind();
	glTexParameteri(_target, param, value);
}

void Texture::setBuffer(int level, int offx, int offy, int width, int height, int pixelFormat, int dataType, const void* dataPtr)
{
    bind();
    glTexSubImage2D(_target, level, offx, offy, width, height, pixelFormat, dataType, dataPtr);
    //glTextureSubImage2D()
    unbind();
}

unsigned Texture::getWidth()
{
	return getTexLevelParam(0, GL_TEXTURE_WIDTH);
}

unsigned Texture::getHeight()
{
	return getTexLevelParam(0, GL_TEXTURE_HEIGHT);
}

unsigned Texture::getLevels()
{
	return _levels;
}

unsigned Texture::getTextureFormat()
{
	return getTexLevelParam(0, GL_TEXTURE_INTERNAL_FORMAT);
}

unsigned Texture::getPixelFormat()
{
	return _pixelFormat;
}

unsigned Texture::getTarget()
{
	return _target;
}

unsigned Texture::getMinFilter()
{
	return getTexParam(GL_TEXTURE_MIN_FILTER);
}

unsigned Texture::getMagFilter()
{
	return getTexParam(GL_TEXTURE_MAG_FILTER);
}

unsigned Texture::getWrapS()
{
	return getTexParam(GL_TEXTURE_WRAP_S);
}

unsigned Texture::getWrapT()
{
	return getTexParam(GL_TEXTURE_WRAP_T);
}

void Texture::setMinFilter(int param_value)
{
	setTexParam(GL_TEXTURE_MIN_FILTER, param_value);
}

void Texture::setMagFilter(int param_value)
{
	setTexParam(GL_TEXTURE_MAG_FILTER, param_value);
}

void Texture::setWrapS(int param_value)
{
	setTexParam(GL_TEXTURE_WRAP_S, param_value);
}

void Texture::setWrapT(int param_value)
{
	setTexParam(GL_TEXTURE_WRAP_T, param_value);
}

void Texture::bind()
{
    int value = 0;
    int param = 0;

    switch(_target)
    {
        case GL_TEXTURE_1D:
            param = GL_TEXTURE_BINDING_1D;
            break;
        case GL_TEXTURE_2D:
            param = GL_TEXTURE_BINDING_2D;
            break;
    }

    glGetIntegerv(param, &value);

    if(value == objectID) return;

    glBindTexture(_target, objectID);
}

void Texture::unbind()
{
	glBindTexture(_target, 0);
}


//--------------------------------------------------------------------------//

char DefaultTexture::renderPixel(unsigned x, unsigned y)
{
	//return (x+(y%32>=16?16:0))%32>=16?100:155;
	return (x+y)%32>=16?100:155;
}

void DefaultTexture::renderImage(unsigned width, unsigned height, unsigned channels, char* data)
{
	float norm_w = 1.0/width;
	float norm_h = 1.0/height;

	char* pixel;
	unsigned x, y;

	for(y=0u; y<height; y++)
		for(x=0u; x<width; x++)
		{
			pixel = &data[(x+y*height)*channels];
			pixel[0] = pixel[1] = pixel[2] = renderPixel(x, y);
			pixel[3] = 255u;
		}
}

DefaultTexture::DefaultTexture()
{
	char* data = new char[1048576]; // 512 * 512 * 4

	//memset(data, 0, 1048576);

	renderImage(512, 512, 4, data);

	setTexture(GL_TEXTURE_2D,
	           512,
	           512,
	           GL_RGBA8,
	           GL_BGRA,
	           GL_LINEAR,
	           GL_LINEAR,
	           GL_REPEAT,
	           GL_REPEAT,
	           GL_UNSIGNED_BYTE,
	           data);

	delete data;
}

DefaultTexture::~DefaultTexture()
{

}

//--------------------------------------------------------------------------//

TextureManager* TextureManager::instance = 0;

TextureManager::TextureManager()
{
    cout << "[TextureManager] Iniciando..." << endl;
	default_texture = new DefaultTexture();
}

TextureManager::~TextureManager()
{
    cout << "[TextureManager] Destruindo..." << endl;
	delete default_texture;
	clear();
}

TextureManager* TextureManager::getInstance()
{
	if(!instance) instance = new TextureManager();
	return instance;
}
void TextureManager::destroyInstance()
{
	if(instance) delete instance;
	instance = 0;
}

bool TextureManager::insert(string name, Texture* t)
{
	if(!t) return false;
	TextureMapIterator texture = textureMap.find(name);
	if(texture != textureMap.end()) texture->second = t;
	textureMap.insert(TextureMapPair(name, t));
	return true;
}

bool TextureManager::destroy(string name)
{
	TextureMapIterator texture = textureMap.find(name);
	if(texture != textureMap.end())
	{
		delete texture->second;
		textureMap.erase(texture);
		return true;
	}
	return false;
}

bool TextureManager::contains(string name)
{
	TextureMapIterator texture = textureMap.find(name);
	return texture != textureMap.end();
}

Texture* TextureManager::get(string name)
{
	TextureMapIterator texture = textureMap.find(name);
	if(texture != textureMap.end())
	{
		return texture->second;
	}
	return default_texture;
}

void TextureManager::clear()
{
	TextureMapIterator texture;
	for(texture = textureMap.begin(); texture != textureMap.end(); texture++)
	{
		delete texture->second;
	}
	textureMap.clear();
}


TextureLoader* TextureLoader::instance = 0;

TextureLoader::TextureLoader()
{
    cout << "[TextureLoader] Iniciando..." << endl;
    placeholder = new DefaultTexture();
    FreeImage_Initialise();
}

TextureLoader::~TextureLoader()
{
    cout << "[TextureLoader] Destruindo..." << endl;
    if(placeholder) delete placeholder;
    FreeImage_DeInitialise();
}

TextureLoader* TextureLoader::getInstance()
{
    if(!instance) instance = new TextureLoader();
    return instance;
}

void TextureLoader::destroyInstance()
{
    if(instance) delete instance;
    instance = 0;
}

Texture* TextureLoader::getDefault()
{
    return placeholder;
}

Texture* TextureLoader::loadFile(std::string file)
{
	FREE_IMAGE_FORMAT   fif = FIF_UNKNOWN;      // image format
	FIBITMAP*           dib(0);                 // pointer to the image, once loaded
	BYTE*               bits(0);                // pointer to the image data
	unsigned            width(0), height(0);    // image width and height

    fif = FreeImage_GetFileType(file.c_str(), 0);  // pega formato pela extensão do arquivo.

	if(fif == FIF_UNKNOWN) // se desconhecido, tentar advinhar o formato
        fif = FreeImage_GetFIFFromFilename(file.c_str());

	if(fif == FIF_UNKNOWN) // se ainda desconhecido, erro!
    {
        std::cout << "[TextureLoader] Impossivel abrir arquivo \"" << file << "\"." << std::endl;
        return 0;
    }

    //check that the plugin has reading capabilities and load the file
	if(FreeImage_FIFSupportsReading(fif))
    {
        if(!(dib = FreeImage_Load(fif, file.c_str())))
        {
            std::cout << "[TextureLoader] Erro ao ler o arquivo \"" << file << "\"." << std::endl;
            return 0;
        }
    }
    else
    {
        std::cout << "[TextureLoader] Erro ao ler o arquivo \"" << file << "\"." << std::endl;
        return 0;
    }

	bits    = FreeImage_GetBits(dib);
	width   = FreeImage_GetWidth(dib);
	height  = FreeImage_GetHeight(dib);

	if(!bits || !width || !height)
    {
        return 0;
    }

    FreeImage_FlipVertical(dib);  // para o OpenGL...

	std::cout << "[TextureLoader] Carregando arquivo \"" << file << "\"" << std::endl;

    Texture* texture(0);
    if(FreeImage_IsTransparent(dib)){
        texture = new Texture(width, height, GL_RGBA, GL_BGRA, GL_UNSIGNED_BYTE, bits);
    }else{
        texture = new Texture(width, height, GL_RGBA, GL_BGR, GL_UNSIGNED_BYTE, bits);
    }

	FreeImage_Unload(dib);

    return texture;
}

Texture* TextureLoader::loadBMPFile(std::string file)
{
	std::ifstream f(file, std::ifstream::binary);

	if(!f.good())
	{
		std::cout << "[TextureManager] Impossível abrir o arquivo \"" << file << "\"" << std::endl;
		return getDefault();
	}

	char bmp_header[54];

    // Nota: 54 é o tamanho do cabeçalho um BMP.
	f.read(bmp_header,54);

	if(f.gcount()!=54)
	{
		std::cout << "[TextureManager] Arquivo \"" << file << "\ é inválido." << std::endl;
		return getDefault();
	}

	if(bmp_header[0] != 'B' && bmp_header[1] != 'M')
	{
		std::cout << "[TextureManager] Arquivo \"" << file << "\ não é um arquivo BMP." << std::endl;
		return getDefault();
	}

    std::stringstream ss;
	ss << "[TextureManager] Carregando arquivo " << file << endl;
	std::cout << ss.str();

    int offset      = *(int*)&bmp_header[0x0A];
	int width       = *(int*)&bmp_header[0x12];
	int height      = *(int*)&bmp_header[0x16];
	int bits        = *(short*)&bmp_header[0x1C];
	int compression = *(int*)&bmp_header[0x1E];
	int length      = *(int*)&bmp_header[0x22];

    // bits 24 = RGB
    // bits 32 = RGBA
    int channels    = bits/8;

	char* data      = new char[length];

	f.seekg(offset);
	f.read(data, length);
	f.close();

    // Nota: Inverte ordem das linhas
    if(true)
    {
        char*   temp    = new char[length];
        int     lineLen = width * channels;
        char*   lineSrc = data + length;
        char*   lineDst = temp;
        while(lineSrc != data)
        {
            lineSrc -= lineLen;
            memcpy(lineDst, lineSrc, lineLen);
            lineDst += lineLen;
        }
        memcpy(data, temp, length);
        delete[] temp;
    }

	Texture* texture = new Texture(width, height, GL_RGBA8, GL_BGR, GL_UNSIGNED_BYTE, data);

	delete data;

	return texture;
}

Texture* TextureLoader::loadRAWFile(std::string file, int width, int height)
{
	std::ifstream f(file, std::ifstream::binary);

	if(f.bad())
	{
		return 0;
	}

	f.seekg(0, f.end);
	int length = f.tellg();
	f.seekg(0, f.beg);

	char* data = new char[length];

	f.read(data, length);

	Texture* texture = new Texture(width, height, GL_RGBA8, GL_BGR, GL_UNSIGNED_BYTE, data);

    std::stringstream ss;
	ss << "[TextureManager] loadRAW:\n" << std::endl;
	ss << "\tArquivo : " << file << std::endl;
	ss << "\tDimensao: " << width << "x" << height << std::endl;
	ss << "\tCanais  : " << 3 << std::endl;
	ss << "\tTamanho : " << length << " bytes" << std::endl;
	std::cout << ss.str() << std::endl;

	delete data;

	return texture;
}
