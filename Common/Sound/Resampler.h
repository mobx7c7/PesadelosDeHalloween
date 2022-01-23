/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-05-03
***********************************************************************/
#ifndef SOUND_RESAMPLER_H
#define SOUND_RESAMPLER_H

#include "Wavetable.h"
#include <iostream>
using namespace std;

namespace Sound
{
	class Resampler
	{
		protected:

			Wave*    wave = 0;
			float*   output = 0;
			double   position = 0;
			unsigned interpMethod = 1;

		public:

			Resampler(Wave* wave);
			Resampler();
			~Resampler();

			 int     toInt(char* data, unsigned bitDepth, unsigned maxValue, bool signedData);
			 float   toFloat(char* data, unsigned bitDepth, unsigned maxValue, bool signedData);
             float   linearInterp(float a, float b, float t);

			void    loadWave(Wave* wave);
			void    releaseWave();
			bool    isWaveSet();
			void    setPosition(double position);
			float*  getOutput();
			void    process();
	};

	class Resample2
	{
    protected:

        const char* data            = 0;
        float*      output          = 0;
        bool        signedData      = 0;
        bool        floatData       = 0;
        unsigned    sampleCount     = 0;
        unsigned    channelCount    = 0;
        unsigned    bitsPerSample   = 0;

        unsigned    sampleMaxValue  = 0;
        unsigned    channelOffset   = 0;
        unsigned    sampleOffset    = 0;

        int         toSamplei(unsigned bitsPerSample, unsigned sampleMaxValue, bool signedData, const char* data);
        float       toSamplef(unsigned bitsPerSample, unsigned sampleMaxValue, bool signedData, const char* data);
        float       doLerp(float a, float b, float t);

    public:

        Resample2();
        ~Resample2();
        void            setData(int sampleCount, int channelCount, int bitsPerSample, bool signedData, bool floatData, const char* data);
        void            process(double position);
        const float*    getOutput();

	};
} // namespace Sound

#endif // SOUND_RESAMPLER_H
