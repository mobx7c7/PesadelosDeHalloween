/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-05-03
***********************************************************************/
#include "Sound/Resampler.h"
#include <cmath>

namespace Sound
{
	int Resampler::toInt(char* data, unsigned bitDepth, unsigned maxValue, bool signedData)
	{
	    if(!data) return 0;
		int value = *(int*)data & (maxValue - 0x1);
		if(signedData)
		{
			int  mask   = (~0) & (maxValue >> 0x1) - 0x1;
			bool sign   = value >> (bitDepth - 0x1) & 0x1;  // sign bit (MSB?)
			value       = value & mask | (sign ? ~mask : 0);
		}
		return value;
	}

	float Resampler::toFloat(char* data, unsigned bitDepth, unsigned maxValue, bool signedData)
	{
		return toInt(data, bitDepth, maxValue, signedData) / (float)maxValue;
	}

	float Resampler::linearInterp(float a, float b, float t)
	{
		return a+(b-a)*t; //(1.0f-factor)*a + (factor*b);
	}

	Resampler::Resampler(Wave* wave)
	{
		loadWave(wave);
	}

	Resampler::Resampler()
	{
		releaseWave();
	}

	Resampler::~Resampler()
	{
		releaseWave();
	}

	void Resampler::loadWave(Wave* wave)
	{
		this->wave = wave;
		if(output || wave == 0)
		{
			delete output;
		}
		else
		{
			output = new float[wave->getChannelCount()];
		}
	}

	void Resampler::releaseWave()
	{
		wave        = 0;
		position    = 0;
		if(output) delete[] output;
	}

	bool Resampler::isWaveSet()
	{
		return wave != 0;
	}

	void Resampler::setPosition(double position)
	{
		if(!wave) return;
		this->position = position;
	}

	float* Resampler::getOutput()
	{
		return output;
	}

	void Resampler::process()
	{
		if(!wave || !output) return;

        unsigned    bitsPerSample   = wave->getBitsPerSample();
        unsigned    maxValue        = wave->getMaxValue();
        unsigned    sampleSize      = wave->getSampleSize();
        unsigned    channelCount    = wave->getChannelCount();
        bool        isSigned        = wave->isSigned();

        float*      currentOutput   = output;

		if(interpMethod == 1) // Linear
		{
			char* s0Ptr = wave->getSample(position+0);
			char* s1Ptr = wave->getSample(position+1);
			float s0 = 0, s1 = 0;

			for(unsigned c=0u; c<channelCount; c++)
			{
				s0 = toFloat(s0Ptr, bitsPerSample, maxValue, isSigned);
				s1 = toFloat(s1Ptr, bitsPerSample, maxValue, isSigned);
				s0Ptr += sampleSize;
				s1Ptr += sampleSize;
				*currentOutput++ = linearInterp(s0, s1, position-(int)position);
			}
		}
		else // Sem interpolação
		{
			char* sample = wave->getSample(position);
			for(unsigned c=0; c<channelCount; c++)
			{
				*currentOutput++ = toFloat(sample, bitsPerSample, maxValue, isSigned);
				sample += sampleSize;
			}
		}
	}




	Resample2::Resample2()
	{

	}

	Resample2::~Resample2()
	{
		if(output) delete output;
	}

	int Resample2::toSamplei(unsigned bitsPerSample, unsigned sampleMaxValue, bool signedData, const char* data)
	{
		int value = *(int*)data & (sampleMaxValue - 0x1);
		if(signedData)
		{
			int  mask   = (~0) & (sampleMaxValue >> 0x1) - 0x1;
			bool sign   = value >> (bitsPerSample - 0x1) & 0x1;  // sign bit (MSB)
			value       = value & mask | (sign ? ~mask : 0);
		}
		return value;
	}

	float Resample2::toSamplef(unsigned bitsPerSample, unsigned sampleMaxValue, bool signedData, const char* data)
	{
		return toSamplei(bitsPerSample, sampleMaxValue, signedData, data) / (float)sampleMaxValue;
	}

	float Resample2::doLerp(float a, float b, float t)
	{
		return a+(b-a)*t;
	}

	void Resample2::setData(int sampleCount, int channelCount, int bitsPerSample, bool signedData, bool floatData, const char* data)
	{
		if(this->sampleCount != sampleCount)
		{
			if(output) delete output;
			output = new float[channelCount];
		}
		this->data              = data;
		this->sampleCount       = sampleCount;
		this->channelCount      = channelCount;
		this->bitsPerSample     = bitsPerSample;
		this->signedData        = signedData;
		this->floatData         = floatData;

		this->channelOffset     = bitsPerSample < 8 ? 1 : bitsPerSample/8;
		this->sampleOffset      = channelOffset * channelCount;
		this->sampleMaxValue    = pow(2, bitsPerSample);
	}

	void Resample2::process(double position)
	{
	    if(!data) return;

		unsigned    offset = sampleOffset * (unsigned)position;
		const char* s0     = data + offset; // amostra 1
		const char* s1     = data + offset + sampleOffset; // amostra 2

        float v0, v1;
		for(int i=0; i<channelCount; i++)
		{
			if(!floatData)
            {
                v0 = toSamplef(bitsPerSample, sampleMaxValue, signedData, s0);
                v1 = toSamplef(bitsPerSample, sampleMaxValue, signedData, s1);
            }
            else
            {
                v0 = *(float*)s0;
                v1 = *(float*)s1;
            }
			output[i]   = doLerp(v0, v1, position - (unsigned)position);
			s0 += channelOffset;
			//s1 += channelOffset;
		}
	}

	const float* Resample2::getOutput()
	{
		return output;
	}
} // namespace Sound
