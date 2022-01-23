/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-18
***********************************************************************/
#ifndef SOUND_WAVE_H
#define SOUND_WAVE_H

#include "Common/Sound/Buffer.h"
#include <cstring> // memcpy

namespace Sound
{
	class Wave : public Buffer
	{
		protected:

            unsigned    maxValue            = 0;
			unsigned    channelCount        = 0;
			unsigned    bitsPerSample       = 0;
			unsigned    sampleRate          = 0;
			unsigned    sampleCount         = 0;
			unsigned    sampleSize          = 0;
			bool        signedData          = false;
			bool        floatingPointData   = false;

		public:

			Wave(unsigned channelCount, unsigned sampleRate, unsigned bitsPerSample, unsigned dataSize, bool signedData, const char* data);
			Wave();
			~Wave();
			char*    getSample(unsigned offset) const;
			unsigned getChannelCount();
			unsigned getBitsPerSample();
			unsigned getSampleRate();
			unsigned getSampleCount();
			unsigned getSampleSize();
			unsigned getMaxValue();
			bool     isSigned();
			bool     isFloatingPoint();
	};

} // namespace Sound

#endif // SOUND_WAVE_H
