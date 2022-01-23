/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-18
***********************************************************************/
#ifndef SOUND_SAMPLER_H
#define SOUND_SAMPLER_H

#include "Common/Sound/Wavetable.h"
#include "Common/Sound/Module.h"
#include "Common/Sound/EnvelopeSmoother.h"
#include "Common/Sound/Resampler.h"

#include <queue>
#include <mutex>

namespace Sound
{
//    class DCFilter
//    {
//        double result;
//        double
//        void process()
//        {
//            resul
//        }
//    };

    class LPF
    {
    protected:

        unsigned    inputChannels = 0;
        float*      inputData = 0;
        float*      last = 0;
        float*      output = 0;

    public:

        LPF(unsigned channels, float* data)
        {
            setInput(channels, data);
        }
        LPF()
        {

        }
        ~LPF()
        {
            delete last;
            delete output;
        }
        void setInput(unsigned channels, float* data)
        {
            inputChannels   = channels;
            inputData       = data;
            output          = new float[channels];
            last            = new float[channels];
        }
        float* getOutput()
        {
            return output;
        }
        void process(double step)
        {
            if(!inputData) return;
            for(unsigned c=0; c<inputChannels; c++)
            {
                output[c] = inputData[c] + last[c];
                last[c] = inputData[c];
            }
        }
    };

	class Sampler : public Module
	{
		protected:

			class Voice
			{
				public:
					double position;
					double gain;
					double pan;
					Voice();
				    Voice(double position);
				    Voice(double position, double gain, double pan);
			};

			deque<Voice> voices;
			mutex mtx_voices;

            unsigned voice_max = 100;
            unsigned next_voice;

			/**********************************************/

			Wave*   wave            = 0;
            bool    tmp_panic       = false; // Nota: resolve problema de concorrência entre threads
			bool    tmp_add_voice   = false; // Nota: resolve problema de concorrência entre threads
			bool    playing         = false;
			bool    paused          = false;
			bool    loopable        = false;
			double  positionBegin   = 0;
			double  positionEnd     = 0;
			double  loopBegin       = 0;
			double  loopEnd         = 0;
			double  velocity        = 0;
			double  master_gain            = 1;
			double  master_pan             = 0; // [L------0------R]

			void    refreshParams();

            Resampler           resampler;
			EnvelopeSmoother    velocityCtrl;
			LPF                 lpf;

		public:

			static double wrap(double pos, double start, double end);

			Sampler(string name);
			Sampler();
			~Sampler();

			void            play();
			void            play(double voice_gain, double voice_pan);
			void            pause();
			void            stop(); // reset

			void            setGain(double master_gain);
			void            setPan(double master_pan);

			void            setPositionCurrent(double value);
			void            setPositionBegin(double value);
			void            setPositionEnd(double value);
			void            setLoopable(bool value);
			void            setLoopBegin(double value);
			void            setLoopEnd(double value);
			void            setVelocity(double value);

			void            setMaxPolyphony(unsigned value)
			{
                voice_max = value;
			}

			bool            isPlaying();
			bool            isLoopable();
			double          getPositionCurrent(unsigned voice);
			double          getPositionBegin();
			double          getPositionEnd();
			double          getLoopBegin();
			double          getLoopEnd();
			double          getVelocity();

			unsigned        getVoiceCount();
			void            setVoiceMax(unsigned value);

			/**************************************************/

			void            loadWave(string name);
			void            releaseWave();

			/**************************************************/

			void            process(const double sampleRate);
	};
} // namespace Sound

#endif // SOUND_SAMPLER_H
