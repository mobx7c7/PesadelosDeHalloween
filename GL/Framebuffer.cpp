/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2014-11-28
***********************************************************************/
#include "Framebuffer.h"
#include "gl_includes.h"

//Framebuffer* Framebuffer::placeholder = 0;

//Framebuffer::Framebuffer()
//{
//}

Framebuffer::Framebuffer(unsigned width, unsigned height, unsigned textureFormat, unsigned pixelFormat, DataType dataType)
{
	_width      = width;
	_height     = height;
	_target     = GL_FRAMEBUFFER;
	_attachment = GL_COLOR_ATTACHMENT0;

	glGenFramebuffers(1, &objectID);

	bind();

    _texture        = new Texture(width, height, textureFormat, pixelFormat, toGLEnumDataType(dataType), 0);
    _renderbuffer   = new Renderbuffer(width, height);

    // glFramebufferTexture2D = vincula uma textura a um framebuffer
    glFramebufferTexture2D(_target, GL_COLOR_ATTACHMENT0, _texture->getTarget(), _texture->getObjectID(), 0); // "0" é o nível da textura.
    // glFramebufferRenderbuffer = vincula um renderbuffer a um framebuffer
    glFramebufferRenderbuffer(_target, GL_DEPTH_ATTACHMENT, _renderbuffer->getTarget(), _renderbuffer->getObjectID());

    //attatchTexture2D(Texture* texture, unsigned slot, unsigned level);
    //attatchRenderbuffer(Renderbuffer* renderbuffer, unsigned slot);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        cout << "[Framebuffer] Aviso: Framebuffer está imcompleto." << endl;
    }

    unbind();
}

Framebuffer::Framebuffer(unsigned width, unsigned height) :
    Framebuffer(width, height, GL_RGBA, GL_RGBA, DataType::UByte)
{

}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &objectID);
	if(_texture) delete _texture;
	if(_renderbuffer) delete _renderbuffer;
}

//Framebuffer* Framebuffer::getPlaceholder()
//{
//    if(placeholder) placeholder = new Framebuffer();
//    return placeholder;
//}

Texture* Framebuffer::getTexture() const
{
	return _texture;// ? _texture : TextureLoader::getInstance()->getDefault();
}

Renderbuffer* Framebuffer::getRenderbuffer() const
{
	return _renderbuffer;// ? _renderbuffer : Renderbuffer::getPlaceholder();
}

unsigned Framebuffer::getWidth()
{
    return _width;
}

unsigned Framebuffer::getHeight()
{
    return _height;
}

unsigned Framebuffer::getAttachment()
{
    return _attachment;
}

unsigned Framebuffer::getTarget()
{
	return _target;
}

void Framebuffer::bind()
{
    glBindFramebuffer(_target, objectID);
}

void Framebuffer::unbind()
{
	glBindFramebuffer(_target, 0);
}
