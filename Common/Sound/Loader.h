/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-18
***********************************************************************/
#ifndef SOUND_LOADER_H
#define SOUND_LOADER_H

#include "Common/Sound/Wavetable.h"

namespace Sound
{
	class Loader
	{
        private:

            static Loader*  instance;
            Loader();
            ~Loader();

            unsigned    length;
            char*       data;
            int readFile(string file);

            string path = "";

        public:

            static Loader*  getInstance();
            static void     destroyInstance();
            void            setCurrentPath(string path);
            int             loadFileWAV(string file);
            int             loadFileRAW(string file, unsigned channelCount, unsigned sampleRate, unsigned bitDepth, bool signedData);
	};

} // namespace Sound

#endif // SOUND_LOADER_H
