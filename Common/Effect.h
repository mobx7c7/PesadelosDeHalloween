/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-21
***********************************************************************/
#ifndef EFFECT_H
#define EFFECT_H

#include "GL/Shader.h"
#include "gl_includes.h"
#include "Manager.h"

class Effect
{
	protected:

		std::string file;
		Shader*     shader;
		glm::mat4   m_src;
		glm::mat4   m_dst;
		float       opacity;
		float       mix;
		bool        bypass;

	public:

        Effect(std::string file) : file(file), opacity(1), mix(1)
		{
            shader = new Shader();
            refresh();
		}

		virtual ~Effect()
		{
		    delete shader;
		}

		Shader* getShaderProgram()
		{
		    return shader;
		}

		void setSurfaceMatrix(glm::mat4 m)
		{
			this->m_src = m;
		}

		void setTextureMatrix(glm::mat4 m)
		{
			this->m_dst = m;
		}

		void setOpacity(float opacity)
		{
            this->opacity = min(max(opacity, 0.0f), 1.0f);
		}

        void setMix(float mix)
		{
            this->mix = min(max(mix, 0.0f), 1.0f);
		}

        void setBypass(bool bypass)
		{
            this->bypass = bypass;
		}

        void refresh()
		{
		    if(shader->isLinked()) shader->clear();
            shader->loadShaderFile("res//plane.vert", ShaderType::Vertex);
			shader->loadShaderFile(file, ShaderType::Fragment);
			shader->link();
		}

		void bind()
		{
			shader->bind();
			shader->setUniformMatrix4f("m_src", 1, &m_src[0][0]);
			shader->setUniformMatrix4f("m_dst", 1, &m_dst[0][0]);
            shader->setUniform1i("texture0", 0);
            shader->setUniform1i("texture1", 1);
            shader->setUniform1i("texture2", 2);
            shader->setUniform1i("texture3", 3);
			shader->setUniform1f("opacity", opacity);
			shader->setUniform1f("mix", mix);
			shader->setUniform1i("bypass", bypass);
			// FIXME: Substituir função glfwGetTime() por outra
			shader->setUniform1f("time", (float)glfwGetTime());
			customParameters();
		}

		void unbind()
		{
			shader->unbind();
		}

    protected:

        virtual void customParameters()
        {

        }
};




class Effect2
{
protected:
    string  name;
protected:
    Effect2(string name) : name(name){}
public:
    virtual ~Effect2(){}
    virtual void begin() = 0;
    virtual void end() = 0;
};


class OGLEffect : public Effect2
{
protected:

    Shader* shader;
    string  filename;

protected:

    OGLEffect(string name, string filename) : Effect2(name), filename(filename)
    {
        shader = new Shader();
        refresh();
    }

protected:

    virtual void updateParams() = 0;

public:

    virtual ~OGLEffect()
    {
        delete shader;
    }
    virtual void refresh()
    {
        if(shader->isLinked())
        {
            shader->clear();
        }
        shader->loadShaderFile("res//plane.vert", ShaderType::Vertex);
        shader->loadShaderFile(filename, ShaderType::Fragment);
        shader->link();
    }
    void begin()
    {
        shader->bind();
        updateParams();
    }
    void end()
    {
        shader->unbind();
    }
};


class OGLWaveEffect : public OGLEffect
{
private:

    double amplitude;
    double frequency;
    double phase;
    double angle;

protected:

    void updateParams()
    {
        shader->setUniform1d("amplitude", amplitude);
        shader->setUniform1d("frequency", frequency);
        shader->setUniform1d("phase", phase);
        shader->setUniform1d("angle", angle);
    }

public:

    OGLWaveEffect() : OGLEffect("Wave", "res//waves.frag")
    {

    }
    ~OGLWaveEffect()
    {

    }
    void setAmplitude(double amplitude)
    {
        this->amplitude = amplitude;
    }
    void setFrequency(double frequency)
    {
        this->frequency = frequency;
    }
    void setPhase(double phase)
    {
        this->phase = phase;
    }
    void setAngle(double angle)
    {
        this->angle = angle;
    }
};







class EffectManager : public Manager<Effect>
{
private:

	static EffectManager* instance;

	EffectManager() : Manager<Effect>("Effect manager")
	{
		insert("Default", new Effect("res//plane.frag"));
		insert("Waves", new Effect("res//waves.frag"));
		insert("Luma", new Effect("res//luma.frag"));
		insert("Explosao atari", new Effect("res//atari_rainbow.frag"));

		setDefault("Default");
	}

	~EffectManager()
	{

	}

public:

    static EffectManager* getInstance()
    {
        if(!instance) instance = new EffectManager();
        return instance;
    }

};

#endif // EFFECT_H
