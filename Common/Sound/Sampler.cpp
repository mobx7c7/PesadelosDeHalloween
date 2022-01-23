/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-18
***********************************************************************/
#include "Sound/Sampler.h"
#include <algorithm>  // min, max
#include <iostream>
#include <cmath> // abs
#include "Manager.h"> // abs

using std::min;
using std::max;
using std::cout;
using std::endl;

namespace Sound
{
	Sampler::Voice::Voice() : position(0), gain(1), pan(1){}

	Sampler::Voice::Voice(double position) : position(position), gain(1), pan(1){}

	Sampler::Voice::Voice(double position, double gain, double pan) : position(position), gain(gain), pan(pan){}

	/*************************************************************/

	Sampler::Sampler(string name) : Module(name)
	{
        Sound::Manager* sndman = Sound::Manager::getInstance();
        sndman->insert(this);
	}

	Sampler::Sampler() : Sampler("Sampler")
	{

	}

	Sampler::~Sampler()
	{
	    // ATENÇÃO: Perigo de recursividade!
//        Sound::Manager* sndman = Sound::Manager::getInstance();
//        sndman->destroy(this->getUniqueID());
	}

	void Sampler::refreshParams()
	{
		// TODO: Mover para uma classe onde possa ter seu proprio limite minmax e proprio suavizador.
		master_gain      = min(max(master_gain, 0.0), 1.0);
		master_pan       = min(max(master_pan, -1.0), 1.0);
		//position    = min(max(position, posBegin), posEnd);
		positionBegin    = min(max(positionBegin, 0.0), positionEnd-1);
		positionEnd      = min(max(positionEnd, positionBegin+1), (double)wave->getSampleCount());

		if(loopEnd < loopBegin)
		{
			loopBegin = loopEnd-1;
		}
		else if(loopBegin >= loopEnd)
		{
			loopEnd = loopBegin+1;
		}
		if(loopBegin < positionBegin)
		{
			loopBegin = positionBegin;
		}
		else if(loopEnd >= positionEnd)
		{
			loopEnd = positionEnd;
		}
	}

	void Sampler::play()
	{
		play(1.0, 0.0);
	}

	void Sampler::play(double voice_gain, double voice_pan)
	{
        if(!wave) return;
		playing  = true;
		paused   = false;

        mtx_voices.lock();
        voices.push_front( Voice(positionBegin, voice_gain, voice_pan) );
        if(voice_max > 0 && voices.size() > voice_max)
        {
            voices.pop_back();
        }
        mtx_voices.unlock();
	}

	void Sampler::pause()
	{
		if(!wave) return;
		paused = !paused;
	}

	void Sampler::stop()
	{
		if(!wave) return;
		playing  = false;

        mtx_voices.lock();
        voices.clear();
		mtx_voices.unlock();
	}

	void Sampler::setGain(double value)
	{
		if(!wave) return;
		master_gain = value;
		refreshParams();
	}

	void Sampler::setPan(double value)
	{
		if(!wave) return;
		master_pan = value;
		refreshParams();
	}

//	void Sampler::setPositionCurrent(double value)
//	{
//		if(!wave) return;
//		position = value;
//		refreshParams();
//	}

	void Sampler::setPositionBegin(double value)
	{
		if(!wave) return;
		positionBegin = value;
		refreshParams();
	}

	void Sampler::setPositionEnd(double value)
	{
		if(!wave) return;
		positionEnd = value;
		refreshParams();
	}

	void Sampler::setLoopBegin(double value)
	{
		if(!wave) return;
		loopBegin = value;
		refreshParams();
	}

	void Sampler::setLoopEnd(double value)
	{
		if(!wave) return;
		loopEnd = value;
		refreshParams();
	}

	void Sampler::setVelocity(double value)
	{
		if(!wave) return;
		velocity = value;
		refreshParams();
	}

	void Sampler::setLoopable(bool value)
	{
		if(!wave) return;
		loopable = value;
		refreshParams();
	}

	double Sampler::getPositionCurrent(unsigned voice)
	{
		return voices[voice].position;
	}

	double Sampler::getPositionBegin()
	{
		return positionBegin;
	}

	double Sampler::getPositionEnd()
	{
		return positionEnd;
	}

	double Sampler::getLoopBegin()
	{
		return loopBegin;
	}

	double Sampler::getLoopEnd()
	{
		return loopEnd;
	}

	double Sampler::getVelocity()
	{
		return velocity;
	}

	unsigned Sampler::getVoiceCount()
	{
        return voices.size();
	}

	void Sampler::setVoiceMax(unsigned value)
	{
	    voice_max = value;
	}

	bool Sampler::isPlaying()
	{
		return voices.size() > 0 ;//playing;
	}

	bool Sampler::isLoopable()
	{
		return loopable;
	}

	void Sampler::loadWave(string name)
	{
		wave            = Wavetable::getInstance()->get(name);
		if(!wave) return;
		// Nota: Dual mono: mono em 2 canais, então deve ter buffer com tamanho 2!
		createModuleIO(0, wave->getChannelCount() == 1 ? 2 : wave->getChannelCount());
		positionBegin   = 0;
		positionEnd     = wave->getSampleCount();
		loopable        = false;
		loopBegin       = 0;
		loopEnd         = wave->getSampleCount();
		velocity        = 1;
		playing         = false;
		resampler.loadWave(wave);
		velocityCtrl.reset();
		lpf.setInput(wave->getChannelCount(), resampler.getOutput());
	}
	void Sampler::releaseWave()
	{
		if(!wave) return;
		destroyModuleIO();
		voices.clear();
		wave            = 0;
		positionBegin   = 0;
		positionEnd     = 0;
		loopable        = false;
		loopBegin       = 0;
		loopEnd         = 0;
		velocity        = 0;
		resampler.releaseWave();
	}
	void Sampler::process(const double sampleRate) //void Sampler::process(float* out_sample, unsigned out_channels, double sample_rate)
	{
	    clearOutput();

		if(!wave || voices.empty()) return;

//		velocityCtrl.setTime(1);
//		velocityCtrl.setValue(!paused ? velocity : 0);
//		velocityCtrl.process(1.0/sampleRate);

        //double speed = playing ? velocityCtrl.getResult() * (wave->getSampleRate()/sampleRate) : 0;
		double speed = playing && !paused ?  velocity * (wave->getSampleRate()/sampleRate) : 0;

        deque<Voice>::iterator voice;

        mtx_voices.lock();
		for(voice = voices.begin(); voice != voices.end(); voice++)
        {
            resampler.setPosition(voice->position);
            resampler.process();

            float* srcPtr = resampler.getOutput();
            float* dstPtr = mOutput; //float* output = out_sample;//mInput;

            // TODO: mover para classe de mixagem com matriz
            for(unsigned c=0u; c<mOutputChannels; c++)
            {
                float tmp;
                if(wave->getChannelCount() == 1) // mono
                {
                    tmp = srcPtr[0];
                }
                else if(wave->getChannelCount() == 2) // stereo
                {
                    // TODO: mover para classe para filtro panning
                    tmp         = srcPtr[0] + srcPtr[1];
                    float pan   = voice->pan + master_pan;
                    float p_abs = fabs(pan);
                    switch(c)
                    {
                        case 0: // Left
                            tmp *= pan < 0 ? p_abs : 0;
                            break;
                        case 1: // Right
                            tmp *= pan > 0 ? p_abs : 0;
                            break;
                    }
                    tmp += srcPtr[c] * (1.0-p_abs);
                    tmp *= (1.0 - 0.5*p_abs); // Nota: normalizar sinal!
                }
                else if(c < wave->getChannelCount())
                {
                    //dstPtr = srcPtr[c];
                    tmp = srcPtr[c];
                }
                *dstPtr++ += tmp * voice->gain * master_gain;//abs(speed) > 0.0000001f ? tmp : 0;
            }

            if(voice->position >= loopBegin && voice->position <= loopEnd && loopable)
            {
                voice->position = wrap(voice->position + speed, loopBegin, loopEnd);
            }
            else if(voice->position < positionEnd)
            {
                voice->position = min(max(voice->position + speed, positionBegin), positionEnd);
            }
            else
            {
                voices.erase(voice--);
            }
        }
        mtx_voices.unlock();
	}

	double Sampler::wrap(double pos, double start, double end)
	{
		double length = end - start;
		double f = abs(floor(pos/end));
		return pos + (pos-start >= 0 ? -length*f : length*(f+1)); //pos-((length)*floor(pos/end));
	}
} // namespace Sound
