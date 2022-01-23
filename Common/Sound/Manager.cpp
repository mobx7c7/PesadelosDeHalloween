/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-18
***********************************************************************/
#include "Sound/Manager.h"
#include <iostream>
#include <cstring> // memset

using std::cout;
using std::endl;

namespace Sound
{
	Manager* Manager::instance = 0;

	Manager::Manager()
	{
		cout << "[Sound::Manager] Iniciando..." << endl;
	}
	Manager::~Manager()
	{
		cout << "[Sound::Manager] Destruindo..." << endl;
		clear();
	}
	Manager* Manager::getInstance()
	{
		if(!instance) instance = new Manager();
		return instance;
	}
	void Manager::destroyInstance()
	{
	    if(instance) delete instance;
	    instance = 0;
	}
    bool Manager::insert(Module* module)
	{
	    if(!module || get(module->getUniqueID())) return false;
	    mtx_modules.lock();
        modules.insert( std::pair<unsigned, Module*>(module->getUniqueID(), module) );
        mtx_modules.unlock();
        return true;
	}
    bool Manager::destroy(unsigned uniqueID)
	{
        map<unsigned, Module*>::iterator module = modules.find(uniqueID);
        if(module != modules.end())
        {
            mtx_modules.lock();
            delete module->second;
            modules.erase(module);
            mtx_modules.unlock();
            return true;
        }
        return false;
	}
    void Manager::clear()
	{
        mtx_modules.lock();
        map<unsigned, Module*>::iterator module;
        for(module = modules.begin(); module != modules.end(); module++)
        {
            delete module->second;
        }
        modules.clear();
        mtx_modules.unlock();
	}
	Module* Manager::get(unsigned uniqueID)
	{
        map<unsigned, Module*>::iterator module = modules.find(uniqueID);
        if(module != modules.end())
        {
            return (Module*)module->second;
        }
        return 0;
	}

	 // BufferOperations::add()
    void Manager::addBuffers(const float* srcBuf, unsigned srcChn, float* dstBuf, unsigned dstChn)
	{
	    if(!srcBuf || !dstBuf) return;
	    for(unsigned i=0; i < (srcChn > dstChn ? dstChn : srcChn); i++){
            *dstBuf++ += *srcBuf++;
	    }
	}

    void Manager::process(float* outputBuffer, unsigned channelCount, unsigned framesPerBuffer, unsigned sampleRate)
    {
        memset((void*)outputBuffer, 0, sizeof(float) * channelCount * framesPerBuffer);

        if(modules.empty()) return;

        map<unsigned, Module*>::iterator module;
        int     i;
        Module* current;
        float*  outPtr;

        mtx_modules.lock();
        for(module = modules.begin(); module != modules.end(); module++)
        {
            current = module->second;
            outPtr  = outputBuffer;
            if(current)
            {
                for(i=0; i<framesPerBuffer; i++)
                {
                    //setBuffers(inPtr, channelCount, module->getInput(), module->getInputChannels());
                    //module->setInput(inputBuffer, channelCount);
                    //module->process(outPtr, channelCount, sampleRate)
                    current->process(sampleRate);
                    //module->setOutput(outputBuffer, channelCount);

                    addBuffers(current->getOutput(),
                               current->getOutputChannels(),
                               outPtr,
                               channelCount);

                    outPtr += channelCount;
                }
            }
        }
        mtx_modules.unlock();
    }
} // namespace Sound
