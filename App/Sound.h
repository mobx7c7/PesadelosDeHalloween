/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-03
***********************************************************************/
#ifndef SOUND_RENDERER_H
#define SOUND_RENDERER_H

#include <portaudio.h>

namespace Sound
{
	class Renderer
	{
		private:

			static Renderer* instance;
			Renderer();
			~Renderer();
			static int  soundCallback(const void *inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
			float*      outputSample        = 0;
			void*       stream              = 0;
			int         err                 = 0;
			unsigned    inputChannelCount   = 2;
			unsigned    outputChannelCount  = 2;
			unsigned    sampleRate          = 44100;
			unsigned    bufferSize          = 64;

		public:

			static Renderer*    getInstance();
			static void         destroyInstance();
			int                 create();
			int                 destroy();
			int                 start();
			int                 stop();

			unsigned            getInputChannelCount();
			unsigned            getOutputChannelCount();
			unsigned            getSampleRate();
			unsigned            getBufferSize();
			float*              getOutputSample();
			double              getCpuLoad();
	};
}

#endif // SOUND_RENDERER_H
