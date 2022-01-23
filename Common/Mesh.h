/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-26
***********************************************************************/
#ifndef MESH_H
#define MESH_H

#include "GL/VertexArray.h"
#include "GL/VertexBuffer.h"
#include "GL/Shader.h"
#include "App/Window.h"
#include "gl_includes.h"
#include <vector>

#include <typeinfo>

using namespace glm;
using std::vector;

// class Mesh2D
// class Mesh3D

// class Camera   (posicao camera, posicao alvo, fov, aspecto,
// class Light    (posição camera, posicao alvo, cor/temperatura, abertura, tipo)
// class Material (shader)

class OGLTestCube3D
{
private:

    static OGLTestCube3D* instance;

protected:

    VertexBuffer* vbo;
    VertexBuffer* ibo;
    VertexArray*  vao;
    Shader*       shader;

    unsigned vertexCoordLoc;
    unsigned textureCoordLoc;
    unsigned normalCoordLoc;
    unsigned colorLoc;

    float rot = 0;

    OGLTestCube3D()
    {
        shader = new Shader();
        shader->loadShaderFile("res//lightFragment_vs.glsl", ShaderType::Vertex);
        shader->loadShaderFile("res//lightFragment_fs.glsl", ShaderType::Fragment);
        shader->link();

        vector<float> coords // formato de intercalação: vtn
        {
            // direita   (x=-0.5f)
            -0.5f,+0.5f,+0.5f,      0.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
            -0.5f,+0.5f,-0.5f,      1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
            -0.5f,-0.5f,-0.5f,      1.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
            -0.5f,-0.5f,+0.5f,      0.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
            // esquerda  (x=+0.5f)
            +0.5f,+0.5f,-0.5f,      0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
            +0.5f,+0.5f,+0.5f,      1.0f, 0.0f,     1.0f, 0.0f, 0.0f,
            +0.5f,-0.5f,+0.5f,      1.0f, 1.0f,     1.0f, 0.0f, 0.0f,
            +0.5f,-0.5f,-0.5f,      0.0f, 1.0f,     1.0f, 0.0f, 0.0f,
            // superfície(y=-0.5f)
            +0.5f,-0.5f,-0.5f,      0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
            -0.5f,-0.5f,-0.5f,      1.0f, 0.0f,     0.0f, -1.0f, 0.0f,
            -0.5f,-0.5f,+0.5f,      1.0f, 1.0f,     0.0f, -1.0f, 0.0f,
            +0.5f,-0.5f,+0.5f,      0.0f, 1.0f,     0.0f, -1.0f, 0.0f,
            // topo      (y=+0.5f)
            -0.5f,+0.5f,+0.5f,      0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
            +0.5f,+0.5f,+0.5f,      1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
            +0.5f,+0.5f,-0.5f,      1.0f, 1.0f,     0.0f, 1.0f, 0.0f,
            -0.5f,+0.5f,-0.5f,      0.0f, 1.0f,     0.0f, 1.0f, 0.0f,
            // frente    (z=-0.5f)
            -0.5f,+0.5f,-0.5f,      0.0f, 0.0f,     0.0f, 0.0f, -1.0f,
            +0.5f,+0.5f,-0.5f,      1.0f, 0.0f,     0.0f, 0.0f, -1.0f,
            +0.5f,-0.5f,-0.5f,      1.0f, 1.0f,     0.0f, 0.0f, -1.0f,
            -0.5f,-0.5f,-0.5f,      0.0f, 1.0f,     0.0f, 0.0f, -1.0f,
             // fundo     (z=+0.5f)
            +0.5f,+0.5f,+0.5f,      0.0f, 0.0f,     0.0f, 0.0f, 1.0f,
            -0.5f,+0.5f,+0.5f,      1.0f, 0.0f,     0.0f, 0.0f, 1.0f,
            -0.5f,-0.5f,+0.5f,      1.0f, 1.0f,     0.0f, 0.0f, 1.0f,
            +0.5f,-0.5f,+0.5f,      0.0f, 1.0f,     0.0f, 0.0f, 1.0f,
        };
        vector<unsigned> indexes
        {
            0, 1, 3,  3, 1, 2,
            4, 5, 7,  7, 5, 6,
            8, 9, 11, 11,9, 10,
            12,13,15, 15,13,14,
            16,17,19, 19,17,18,
            20,21,23, 23,21,22,
        };

        vbo = new VertexBuffer(VertexBufferTarget::ArrayBuffer);
        ibo = new VertexBuffer(VertexBufferTarget::ElementBuffer);

        vbo->bufferData(sizeof(float)*coords.size(), &coords[0], VertexBufferUsage::StaticDraw);
        ibo->bufferData(sizeof(unsigned)*indexes.size(), &indexes[0], VertexBufferUsage::StaticDraw);

        vao = new VertexArray();

        //-----------------------------------------------------//

        vertexCoordLoc  = 0;
        textureCoordLoc = 1;
        normalCoordLoc  = 2;
        colorLoc        = 3;

        vao->bind();
            vbo->bind();
            vao->enableVertexAttribPointer(vertexCoordLoc);
            vao->setVertexAttribPointer(vertexCoordLoc, 3, DataType::Float, false, sizeof(float)*8, (void*)0);
            vao->enableVertexAttribPointer(textureCoordLoc);
            vao->setVertexAttribPointer(textureCoordLoc, 2, DataType::Float, false, sizeof(float)*8, (void*)(sizeof(float)*3));
            vao->enableVertexAttribPointer(normalCoordLoc);
            vao->setVertexAttribPointer(normalCoordLoc, 3, DataType::Float, false, sizeof(float)*8, (void*)(sizeof(float)*5));
            //vao->enableVertexAttribPointer(colorLoc);
            //vao->setVertexAttribPointer(colorLoc, 4, DataType::Float, false, sizeof(float)*11, (void*)(sizeof(float)*7));
            ibo->bind();
        vao->unbind();

    }
    ~OGLTestCube3D()
    {
        delete vbo;
        delete ibo;
        delete vao;
        delete shader;
    }

public:

    static OGLTestCube3D* getInstance()
    {
        if(!instance) instance = new OGLTestCube3D();
        return instance;
    }
    void draw()
    {
        glEnable(GL_DEPTH_TEST);
        rot += 0.01;
        shader->bind();
            Window* window = WindowManager::getInstance()->getDefaultWindow();

            mat4 anim       = mat4(1.0f);
            anim            = rotate(anim, -0.2f, vec3(1,0,0));
            anim            = rotate(anim, rot, vec3(0,1,0));

            mat4 model      = translate(mat4(1.0f), vec3(0, 0, -2.0));
            mat4 view       = mat4(1.0f);//lookAt(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, -4.0), vec3(0.0, 1.0, 0.0));
            mat4 projection = perspective(45.0f, (float)window->getWidth()/(float)window->getHeight(), 0.1f, 100.0f);

            mat4 m          = projection * view * model * anim;

            shader->setUniformMatrix4f("m_src", 1, &m[0][0]);

            shader->setUniform4f("matAmbient", 0.0, 0.175, 0.25, 1.0);
            shader->setUniform4f("matDiffuse", 0.2, 0.5, 1.0, 1.0);
            shader->setUniform4f("matSpecular", 1, 1, 1, 1);
            shader->setUniform1i("matShininess", 32);

            shader->setUniform4f("lightPosition", 4.0, 4.0, 4.0, 1.0);
            shader->setUniform4f("lightAmbient", 0, 0, 0, 0);
            shader->setUniform4f("lightDiffuse", 1, 1, 1, 1);
            shader->setUniform4f("lightSpecular", 1, 1, 1, 1);
            shader->setUniform3f("lightSpotDirection", 0, 0, 1);

            shader->setUniform4f("modelAmbient", 0, 0, 1, 1);

            vao->bind();
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            vao->unbind();
        shader->unbind();
        glDisable(GL_DEPTH_TEST);
    }
};



#endif // MESH_H
