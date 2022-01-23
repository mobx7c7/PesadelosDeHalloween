/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-18
***********************************************************************/
#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "Common/Sound/Module.h"
#include <map>
#include <mutex>
#include <vector>
#include <string>

using std::map;
using std::mutex;
using std::vector;
using std::string;

namespace Sound
{
	class Manager
	{
		private:

			static Manager* instance;
			Manager();
			~Manager();

			map<unsigned, Module*>  modules;
            std::mutex              mtx_modules;

		public:

			static Manager* getInstance();
			static void     destroyInstance();

			static void     addBuffers(const float* srcBuf, unsigned srcChn, float* dstBuf, unsigned dstChn);

			bool            insert(Module* module);
			bool            destroy(unsigned uniqueID);
            Module*         get (unsigned uniqueID);
			void            clear();
			void            process(float* outputBuffer, unsigned channelCount, unsigned framesPerBuffer, unsigned sampleRate);
	};
} // namespace Sound

#endif // SOUND_MANAGER_H
