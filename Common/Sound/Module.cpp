/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-18
***********************************************************************/
#include "Sound/Module.h"
#include <cstdlib>
#include <cstring> //memset

namespace Sound
{
	Module::Module(string name) :
	    mInput(0),
	    mOutput(0),
	    mInputChannels(0),
	    mOutputChannels(0),
	    name(name),
	    uniqueID(rand())
    {

    }

	Module::Module() :
	    Module("Module")
    {

    }

	Module::~Module()
	{
		destroyModuleIO();
	}

	void Module::setName(const string name)
	{
		this->name = name;
	}
	const string Module::getName()
	{
		return name;
	}
	unsigned Module::getUniqueID()
	{
		return uniqueID;
	}
	void Module::createModuleIO(unsigned in, unsigned out)
	{
		if(!mInput && in > 0)
		{
			mInput = new float[in];
			mInputChannels = in;
		}
		if(!mOutput && out > 0)
		{
			mOutput = new float[out];
			mOutputChannels = out;
		}
	}
	void Module::destroyModuleIO()
	{
		if(mInput)
		{
			delete[] mInput;
			mInputChannels = 0;
		}
		if(mOutput)
		{
			delete[] mOutput;
			mOutputChannels = 0;
		}
	}
	unsigned Module::setInput(const float* buffer, unsigned channels)
	{
		if(!mInput) return 0;
		int currentCount = channels > mInputChannels ? mInputChannels : channels;
		memcpy(mInput, buffer, sizeof(float)*currentCount);
		return currentCount;
	}
    unsigned Module::getOutput(float* buffer, unsigned channels)
	{
		if(!mOutput) return 0;
		int currentCount = channels > mOutputChannels ? mOutputChannels : channels;
		memcpy(buffer, mOutput, sizeof(float)*currentCount);
		return currentCount;
	}
	const float* Module::getOutput()
	{
		return mOutput;
	}
	unsigned Module::getInputChannels()
	{
		return mInputChannels;
	}
	unsigned Module::getOutputChannels()
	{
		return mOutputChannels;
	}
	void Module::clearInput()
	{
	    if(!mInput) return;
	    memset(mInput, 0, sizeof(float)*mInputChannels);
	}
	void Module::clearOutput()
	{
	    if(!mOutput) return;
	    memset(mOutput, 0, sizeof(float)*mOutputChannels);
	}
    void Module::process(const double deltaTime)
    {

    }
//    void Module::render(const Graphics* g)
//    {
//
//    }
    void Module::setParam(string param, string value)
    {

    }
    void Module::setParam(string param, unsigned value)
    {

    }
} // namespace Sound
