/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-05-20
***********************************************************************/
#include "MusicGenerator.h"
#include <cstdlib>

MusicGenerator::MusicGenerator()
{
    using namespace Sound;

    Sound::Loader* soundLoad = Sound::Loader::getInstance();
    soundLoad->loadFileRAW("xylo1.raw", 2, 44100, 16, true);

	sampler1 = new Sound::Sampler("SamplerA");
	sampler1->loadWave("xylo1.raw");
	sampler2 = new Sound::Sampler("SamplerB");
	sampler2->loadWave("xylo1.raw");

    soundMan = Sound::Manager::getInstance();
	soundMan->insert(sampler1);
	soundMan->insert(sampler2);

    // Retirado de: http://www.sengpielaudio.com/Root-Ratios.gif
	notes.push_back(0.0000); // Dó
        //notes.push_back(0.0595);
	notes.push_back(0.1225); // Ré
        //notes.push_back(0.1892);
	//notes.push_back(0.2599); // Mi
	//notes.push_back(0.3348); // Fá
        //notes.push_back(0.4142);
	notes.push_back(0.4983); // Sol
        //notes.push_back(0.5874);
	//notes.push_back(0.6818); // Lá
        //notes.push_back(0.7818);
	//notes.push_back(0.8897); // Si
	//notes.push_back(1.0000);

	timers.push_back(Timer(0.5));
	timers.push_back(Timer(1));

	//double getKey(unsigned key){return key/8}
}

MusicGenerator::~MusicGenerator()
{
    //soundMan->destroyByName("SamplerA");
    //soundMan->destroyByName("SamplerB");
    Sound::Wavetable::getInstance()->destroy("xylo1.raw");
}
void MusicGenerator::process(double deltaTime)
{
    Timer* timer;

    static double t = 1;

    t+=deltaTime *0.1;

    double tempo = t * deltaTime;

    timer = &timers[0];

    if(timer->isOver())
    {
        timer->reset();
        current = rand()%notes.size();
        double scale = 1;// 1 + rand()%3;
        //cout << "Escala " << scale << ", Tecla " << current << endl;

        sampler1->setVelocity(scale + notes[current]);
        sampler1->play();
    }

    timer = &timers[1];

    if(timer->isOver())
    {
        sampler2->setVelocity(0.25);
        sampler2->play();
        timer->reset();
    }

    for(Timer& timer : timers){
        timer.process(tempo);
    }
}
