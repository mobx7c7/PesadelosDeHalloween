/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-03
***********************************************************************/
#include "Sound.h"
#include "Common/Sound/Manager.h"
#include <cstring> // memset
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::stringstream;

namespace Sound
{
    Renderer* Renderer::instance = 0;

	int Renderer::soundCallback(const void *inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
	{
		Renderer* renderer = (Renderer*)userData;

//      memset(outputBuffer, 0, sizeof(float)*framesPerBuffer*2);
//		static int i=0;
//		if(i>framesPerBuffer){
//		    cout << "[Sound::Renderer] CPU Load: " << (100*renderer->getCpuLoad()) << endl;
//		    i=0;
//		}else{
//            i++;
//      }

		Sound::Manager::getInstance()->process((float*)outputBuffer,
                                                renderer->getOutputChannelCount(),
                                                framesPerBuffer,
                                                renderer->getSampleRate());
		return 0;
	}
	Renderer::Renderer()
	{
		cout << "[Sound::Renderer] Iniciando..." << endl;
		Pa_Initialize();
        int numDevices = Pa_GetDeviceCount();
        stringstream ss;
        for(int i=0; i<numDevices; i++)
        {
            const PaDeviceInfo*  deviceInfo = Pa_GetDeviceInfo(i);
			const PaHostApiInfo* apiInfo    = Pa_GetHostApiInfo(deviceInfo->hostApi);
			ss << "[Sound::Renderer] Device " <<  i << "\tSystem: " << apiInfo->name << "\tName: " << deviceInfo->name << endl;
        }
        cout << ss.str();
	}
	Renderer::~Renderer()
	{
		cout << "[Sound::Renderer] Destruindo..." << endl;
		destroy();
		Pa_Terminate();
	}
	Renderer* Renderer::getInstance()
	{
		if(!instance) instance = new Renderer();
		return instance;
	}
	void Renderer::destroyInstance()
	{
		if(instance) delete instance;
	}
	int Renderer::create()
	{
		if(stream) return 0;

        PaDeviceIndex       deviceIndex         = Pa_GetDefaultOutputDevice();

        const PaDeviceInfo* deviceInfo          = Pa_GetDeviceInfo(deviceIndex);

        PaStreamParameters outputParams;
        outputParams.channelCount               = 2;
        outputParams.device                     = deviceIndex;
        outputParams.sampleFormat               = paFloat32;
        outputParams.suggestedLatency           = deviceInfo->defaultLowOutputLatency;
        outputParams.hostApiSpecificStreamInfo  = NULL;

        err = Pa_OpenStream(&stream, 0, &outputParams, sampleRate, bufferSize, 0, soundCallback, (void*)this);

        cout << "[Sound::Renderer] OpenStream: " << Pa_GetErrorText(err) << endl;

		if(err != paNoError) return 0;

		if(!outputSample) outputSample = new float[outputChannelCount];

		return 1;
	}
	int Renderer::destroy()
	{
		if(!stream) return 0;

		err = Pa_CloseStream(stream);

		if(err != paNoError) return 0;

		if(outputSample) delete[] outputSample;

		return 1;
	}
	int Renderer::start()
	{
		if(!stream) return 0;

		err = Pa_StartStream(stream);

		if(err != paNoError) return 0;

		return 1;
	}
	int Renderer::stop()
	{
		if(!stream) return 0;

		err = Pa_StopStream(stream);

		if(err != paNoError) return 0;

		return 1;
	}

    unsigned Renderer::getInputChannelCount()
	{
        return inputChannelCount;
	}
	unsigned Renderer::getOutputChannelCount()
	{
        return outputChannelCount;
	}
	unsigned Renderer::getSampleRate()
	{
        return sampleRate;
	}
	unsigned Renderer::getBufferSize()
	{
	    return bufferSize;
	}
	float* Renderer::getOutputSample()
	{
		return outputSample;
	}
	double Renderer::getCpuLoad()
	{
	    if(!stream) return 0;
	    return Pa_GetStreamCpuLoad(stream);
	}

} // namespace Sound









