/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-18
***********************************************************************/
#include "Sound/Wavetable.h"
#include <iostream>
using std::cout;
using std::endl;

namespace Sound
{
	Wavetable* Wavetable::instance = 0;

	Wavetable::Wavetable()
	{
		cout << "[Sound::Wavetable] Iniciando..." << endl;
		placeholder = new Wave();
	}
	Wavetable::~Wavetable()
	{
		cout << "[Sound::Wavetable] Destruindo..." << endl;
		delete placeholder;
		clear();
	}
	Wavetable* Wavetable::getInstance()
	{
		if(!instance) instance = new Wavetable();
		return instance;
	}
	void Wavetable::destroyInstance()
	{
		if(instance) delete instance;
	}
	void Wavetable::create(string name, unsigned channelCount, unsigned sampleRate, unsigned bitDepth, unsigned dataSize, bool signedData, const char* data)
	{
	    Wave* wave = new Wave(channelCount, sampleRate, bitDepth, dataSize, signedData, data);
		waves.insert( std::pair<string, Wave*>(name, wave) );
	}
	void Wavetable::destroy(string name)
	{
	    map<string, Wave*>::iterator it = waves.find(name);
	    if(it != waves.end())
        {
            delete it->second;
            waves.erase(it);
        }
	}
	void Wavetable::clear()
	{
	    map<string, Wave*>::iterator it;
        for(it = waves.begin(); it!=waves.end(); it++)
        {
            delete it->second;
        }
        waves.clear();
	}
	Wave* Wavetable::get(string name)
	{
        std::map<string, Wave*>::iterator it = waves.find(name);
        if(it != waves.end())
        {
            return (Wave*)it->second;
        }
        return placeholder;
	}
	Wave* Wavetable::getPlaceholder()
	{
        return placeholder;
	}
	bool Wavetable::isLoaded(string name)
	{
        map<string, Wave*>::iterator it = waves.find(name);
	    if(it != waves.end())
        {
            return true;
        }
        return false;
	}
} // namespace Sound
