/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-18
***********************************************************************/
#include "Sound/Wave.h"
#include <algorithm> // min, max
#include <iostream> // min, max
using std::min;
using std::max;

namespace Sound
{
    Wave::Wave(unsigned channelCount, unsigned sampleRate, unsigned bitsPerSample, unsigned dataSize, bool signedData, const char* data) :
        Buffer(dataSize, data),
        channelCount(channelCount),
        bitsPerSample(bitsPerSample),
        sampleRate(sampleRate),
        sampleSize(bitsPerSample/8),
        sampleCount(dataSize/channelCount/(bitsPerSample/8)),
        signedData(signedData)
    {
        maxValue = pow(2, bitsPerSample);
    }
    Wave::Wave()
    {
        // vazio!
    }
    Wave::~Wave()
    {

    }
    char* Wave::getSample(unsigned offset) const
    {
        offset = min(max(offset, 0u), sampleCount);
        return data + channelCount * sampleSize * offset;
    }
    unsigned Wave::getSampleRate()
    {
        return sampleRate;
    }
    unsigned Wave::getBitsPerSample()
    {
        return bitsPerSample;
    }
    unsigned Wave::getChannelCount()
    {
        return channelCount;
    }
    unsigned Wave::getSampleCount()
    {
        return sampleCount;
    }
    unsigned Wave::getSampleSize()
    {
        return sampleSize;
    }
    unsigned Wave::getMaxValue()
    {
        return maxValue;
    }
    bool Wave::isSigned()
    {
        return signedData;
    }
    bool Wave::isFloatingPoint()
    {
        return floatingPointData;
    }
} // namespace Sound
