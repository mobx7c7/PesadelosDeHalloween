/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-19
***********************************************************************/
#include "Canvas.h"

CanvasInstance* CanvasInstance::instance = 0;

CanvasInstance::CanvasInstance()
{
    cout << "[CanvasInstance] Iniciando..." << endl;
}

CanvasInstance::~CanvasInstance()
{
    cout << "[CanvasInstance] Destruindo..." << endl;
}

CanvasInstance* CanvasInstance::getInstance()
{
	if(!instance)
    {
        try{
            instance = new OGLCanvasInstance();
        }catch (std::bad_alloc& ba){
            cerr << "bad_alloc: " << ba.what() << endl;
        }
    }
	return instance;
}

void CanvasInstance::destroyInstance()
{
    if(instance) delete instance;
}

OGLCanvasInstance::OGLCanvasInstance()
{
    // Nota intercalação: vertex(x,y), textura(x,y), normal(x,y,z), cor(r,g,b,a)
    std::vector<float> data
	{
		0.0f, 0.0f,     0.0f, 0.0f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,     1.0f, 0.0f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,     1.0f, 1.0f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,     0.0f, 1.0f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f, 1.0f,
	};
	std::vector<unsigned> indexes
	{
		0, 1, 3, 1, 3, 2
	};

	vbo = new VertexBuffer(VertexBufferTarget::ArrayBuffer);
	ibo = new VertexBuffer(VertexBufferTarget::ElementBuffer);

	vbo->bufferData(sizeof(float)*data.size(), &data[0], VertexBufferUsage::StaticDraw);
	ibo->bufferData(sizeof(unsigned)*indexes.size(), &indexes[0], VertexBufferUsage::StaticDraw);

	vao = new VertexArray();

	//-----------------------------------------------------//

    vertexCoordLoc  = 10;
    textureCoordLoc = 11;
    normalCoordLoc  = 12;
    colorLoc        = 13;

	vao->bind();
        vbo->bind();
        vao->enableVertexAttribPointer(vertexCoordLoc);
        vao->setVertexAttribPointer(vertexCoordLoc, 2, DataType::Float, false, sizeof(float)*11, (void*)0);
        vao->enableVertexAttribPointer(textureCoordLoc);
        vao->setVertexAttribPointer(textureCoordLoc, 2, DataType::Float, false, sizeof(float)*11, (void*)(sizeof(float)*2));
        vao->enableVertexAttribPointer(normalCoordLoc);
        vao->setVertexAttribPointer(normalCoordLoc, 3, DataType::Float, false, sizeof(float)*11, (void*)(sizeof(float)*4));
        vao->enableVertexAttribPointer(colorLoc);
        vao->setVertexAttribPointer(colorLoc, 4, DataType::Float, false, sizeof(float)*11, (void*)(sizeof(float)*7));
        ibo->bind();
	vao->unbind();
}

OGLCanvasInstance::~OGLCanvasInstance()
{
	delete vbo;
	delete ibo;
	delete vao;
}

unsigned OGLCanvasInstance::getVertexCoordLoc()
{
    return vertexCoordLoc;
}

unsigned OGLCanvasInstance::getTextureCoordLoc()
{
    return textureCoordLoc;
}

unsigned OGLCanvasInstance::getNormalCoordLoc()
{
    return normalCoordLoc;
}

unsigned OGLCanvasInstance::getColorLoc()
{
    return colorLoc;
}

void OGLCanvasInstance::draw()
{
	vao->bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	vao->unbind();
}

void OGLCanvasInstance::draw(Shader* shader)
{
    if(!shader) return;

    vbo->bind();
    ibo->bind();
    shader->bind();
    shader->enableVertexAttribArray("coord_vertex");
    shader->setVertexAttribPointer("coord_vertex", 2, GL_FLOAT, false, sizeof(float)*11, (void*)0);
    shader->enableVertexAttribArray("coord_texture");
    shader->setVertexAttribPointer("coord_texture", 2, GL_FLOAT, false, sizeof(float)*11, (void*)(sizeof(float)*2));
    shader->enableVertexAttribArray("coord_normal");
    shader->setVertexAttribPointer("coord_normal", 3, GL_FLOAT, false, sizeof(float)*11, (void*)(sizeof(float)*4));
    shader->enableVertexAttribArray("coord_color");
    shader->setVertexAttribPointer("coord_color", 4, GL_FLOAT, false, sizeof(float)*11, (void*)(sizeof(float)*7));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    shader->unbind();
    vbo->unbind();
    ibo->unbind();
}

