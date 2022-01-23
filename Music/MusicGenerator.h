/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-05-20
***********************************************************************/
#ifndef MUSICGENERATOR_H
#define MUSICGENERATOR_H

#include "Common/Sound/Loader.h"
#include "Common/Sound/Manager.h"
#include "Common/Sound/Sampler.h"


class Timer
{
public:
    Timer(){}
    Timer(double interval) : interval(interval){}
    double current = 0;
    double interval = 0;
    bool isOver()
    {
        return current >= interval;
    }
    void reset()
    {
        current = 0;
    }
    void process(const double deltaTime)
    {
        current += deltaTime;
    }
};

class MusicGenerator
{
    public:
        MusicGenerator();
        virtual ~MusicGenerator();
        void process(double deltaTime);

        Sound::Sampler* sampler1;
        Sound::Sampler* sampler2;
        Sound::Manager* soundMan;
        Sound::Loader*  soundLoad;

        vector<Timer>   timers;
        vector<double>  notes;
        unsigned current = 0;

};

//class WaveSlicer
//{
//    class WaveSection
//    {
//        double start;
//        double length;
//    };
//    vector<WaveSection>
//    {
//
//    }
//};

#endif // MUSICGENERATOR_H
