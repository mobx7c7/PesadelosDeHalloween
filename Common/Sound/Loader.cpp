/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-18
***********************************************************************/
#include "Sound/Loader.h"
#include "Sound/Wavetable.h"
#include <fstream>
#include <iostream>

using std::ifstream;
using std::cout;
using std::endl;

namespace Sound
{
	Loader* Loader::instance = 0;

	Loader::Loader()
	{
		cout << "[Sound::Loader] Iniciando..." << endl;
	}
	Loader::~Loader()
	{
		cout << "[Sound::Loader] Destruindo..." << endl;
	}
	Loader* Loader::getInstance()
	{
		if(!instance) instance = new Loader();
		return instance;
	}
	void Loader::destroyInstance()
	{
		if(instance) delete instance;
	}
	int Loader::readFile(string file)
	{
	    // FIXME: Substituir por path global armazenado em um painel de configuração global.
        ifstream is(path + file, ifstream::binary);

        if(!is)
        {
            cout << "[Sound::Loader] Impossivel abrir arquivo \"" << file << "\"" << endl;
            return 0;
        }

        is.seekg (0, is.end);
        length = is.tellg();
        is.seekg (0, is.beg);

        data = new char[length];

        is.read(data, length);
        is.close();

        return 1;
	}
	void Loader::setCurrentPath(string path)
	{
	    this->path = path;
	}
    int Loader::loadFileWAV(string file)
    {
////        ifstream f(file);
////        if(f) return 1;
//        Wavetable::getInstance()->create(file, 0, 0, 0, 0);
        return 0;
    }

    int Loader::loadFileRAW(string file, unsigned channelCount, unsigned sampleRate, unsigned bitDepth, bool signedData)
    {
        if(!readFile(file)) return 0;

        cout << "[Sound::Loader] Abrindo arquivo RAW \"" << file << "\"" << endl;

        Wavetable::getInstance()->create(file, channelCount, sampleRate, bitDepth, length, signedData, data);

        delete data;

        return 1;
    }

} // namespace Sound
