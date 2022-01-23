/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-18
***********************************************************************/
#ifndef SOUND_WAVETABLE_H
#define SOUND_WAVETABLE_H

#include "Common/Sound/Wave.h"
#include <map>
#include <vector>
#include <string>

using std::map;
using std::vector;
using std::string;

namespace Sound
{
    class Wavetable
    {
    private:
        static Wavetable*   instance;
        Wavetable();
        ~Wavetable();
    protected:
        Wave*               placeholder;
        map<string, Wave*>  waves;
    public:
        static Wavetable*   getInstance();
        static void         destroyInstance();
        void                create(string name, unsigned channelCount, unsigned sampleRate, unsigned bitDepth, unsigned dataSize, bool signedData, const char* data);
        void                destroy(string name);
        void                clear();
        Wave*               get(string name);
        Wave*               getPlaceholder();
        bool                isLoaded(string name);
    };
} // namespace Sound

#endif // SOUND_WAVETABLE_H
