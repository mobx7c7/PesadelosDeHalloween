/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-18
***********************************************************************/
#ifndef SOUND_MODULE_H
#define SOUND_MODULE_H

#include <string>

using std::string;

namespace Sound
{
	class Module // public Object
	{
	    private:

            string      name;
            unsigned    uniqueID;

        protected:

			Module();
			Module(string name);

			float*      mInput;
			float*      mOutput;
			unsigned    mInputChannels;
			unsigned    mOutputChannels;
			void        createModuleIO(unsigned in, unsigned out);
			void        destroyModuleIO();
            void        clearInput();
            void        clearOutput();

        public:

            virtual ~Module();

            void            setName(const string name);
            const string    getName();
            unsigned        getUniqueID();
            unsigned        setInput(const float* buffer, unsigned channels);
            unsigned        getOutput(float* buffer, unsigned channels);
            const float*    getOutput();
            unsigned        getInputChannels();
            unsigned        getOutputChannels();
            virtual void    process(const double);
//            virtual void    render(const Graphics* g);
            virtual void    setParam(string param, string value);
            virtual void    setParam(string param, unsigned value);
	};
} // namespace Sound

#endif // SOUND_MODULE_H
