/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-13
***********************************************************************/
#include "App/Renderer.h"
#include "App/Preferences.h"
#include "App/Serial.h"
#include "App/Sound.h"

#include "Common/Sound/Loader.h"
#include "Common/Sound/Manager.h"
#include "Common/Sound/Sampler.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <functional>

using namespace std;

class Connector
{
protected:
	float* 		data;
	unsigned 	channels;
public:
	Connector(unsigned channels) : channels(channels)
	{
		data = new float[channels];
	}
	virtual ~Connector()
	{
		delete[] data;
	}
	float* getData()
	{
	    return data;
	}
	const unsigned getChannels()
	{
	    return channels;
	}
};

// Solução para proteger objeto a ser deletado fora de um local:
// - Criar um "handle" para o real objeto. (não é herança)
// http://stackoverflow.com/questions/5840421/how-to-prevent-an-object-from-being-deleted-in-places-where-it-shouldnt-at-com
class InputConnectorHandle
{
protected:
    Connector* connector;
public:
	InputConnectorHandle(Connector* connector) : connector(connector){}
	~InputConnectorHandle(){}
    float*          getData(){return connector->getData();}
    const unsigned  getChannels(){return connector->getChannels();}
};

class OutputConnectorHandle
{
protected:
    Connector* connector;
public:
	OutputConnectorHandle(Connector* connector) : connector(connector){}
    ~OutputConnectorHandle(){}
	const float*    getData(){return connector->getData();}
    const unsigned  getChannels(){return connector->getChannels();}
};

int main()
{
    // GlobalParams* gparams;

	// TODO: Fazer uma classe de SoundEngine e colocar isso tudo no construtor!
	Sound::Renderer* sndrender = Sound::Renderer::getInstance();
	sndrender->create();
	sndrender->start();

	SerialListener* serialListener = SerialListener::getInstance();
//  serialListener->start();

	GraphicsRenderer* grenderer = GraphicsRenderer::getInstance();
	grenderer->init();
	grenderer->setup();
	grenderer->start();

    // TODO: Fazer uma classe de SoundEngine e colocar isso tudo no destrutor!

    GraphicsRenderer::destroyInstance();
	SerialListener::destroyInstance();
	Sound::Renderer::destroyInstance();
	Sound::Manager::destroyInstance();
	Sound::Loader::destroyInstance();
	Sound::Wavetable::destroyInstance();

	return 0;
}



