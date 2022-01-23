/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-05-21
***********************************************************************/
#ifndef SOUND_IO_H
#define SOUND_IO_H

namespace Sound
{
	class IO
	{
		protected:

			float*      data;
			unsigned    channelCount;

		public:

			IO(unsigned channelCount)
			{
				setChannelCount(channelCount);
			}
			virtual ~IO()
			{
				delete[] data;
			}
			float* getData()
			{
				return data;
			}
			unsigned getChannelCount()
			{
				return channelCount;
			}
			unsigned setChannelCount(unsigned channelCount)
			{
				if(this->channelCount != channelCount)
				{
					if(data) delete[] data;
					data = new float[channelCount];
					this->channelCount = channelCount;
				}
			}
	};

	class InputHandle
	{
		protected:
			IO* io;
		public:
			InputHandle(IO* io) : io(io) {}
			~InputHandle() {};
			void setInput(unsigned channels, const float* src)
			{
				if(!io || !src|| channels == 0) return;

				const float*    srcPtr = src;
				float*          dstPtr = io->getData();

				for(int i=0; i < io->getChannelCount(); i++)
				{
					*dstPtr++ = i < channels ? *srcPtr++ : 0;
				}
			}
	};

	class OutputHandle
	{
		protected:
			IO* io;
		public:
			OutputHandle(IO* io) : io(io) {}
			~OutputHandle() {};
			void setInput(unsigned channels, const float* src)
			{
				if(!io || !src|| channels == 0) return;

				const float*    srcPtr = src;
				float*          dstPtr = io->getData();

				for(int i=0; i < io->getChannelCount(); i++)
				{
					*dstPtr++ = i < channels ? *srcPtr++ : 0;
				}
			}
			void setOutput(unsigned channels, float* dst)
			{
				if(!io || !dst || channels == 0) return;

				const float*    srcPtr = io->getData();
				float*          dstPtr = dst;

				for(int i=0; i<channels; i++)
				{
					*dstPtr++ = i < io->getChannelCount() ? *srcPtr++ : 0;
				}
			}
	};


	class Module
	{
        private:

            const float* srcPtr;
			float* dstPtr;
			int i;

        protected:

			IO      *input  = 0;
			IO      *output = 0;
			bool    bypass  = false;
			float   mix     = 0.0f;

		public:

			virtual void setInputData(unsigned channels, const float* data)
			{
				if(!data || !channels || !input) return;

				srcPtr = data;
				dstPtr = input->getData();
				for(i=0; i<input->getChannelCount(); i++)
					*dstPtr++ = i < channels ? *srcPtr++ : 0.0f;
			}
			virtual void setOutputData(unsigned channels, float* data)
			{
				if(!data || !channels || !output) return;

				srcPtr = output->getData();
				dstPtr = data;
				for(i=0; i<channels; i++)
					*dstPtr++ = i < output->getChannelCount() ? *srcPtr++ : 0.0f;
			}
			virtual void process()
			{
//			    if(!input || !inputChannelCount || !output || outputChannelCount) return;
//
//                srcPtr = input->getData();
//				dstPtr = output->getData();
//                for(i=0; i<output->getChannelCount(); i++)
//					*dstPtr++ += i < input->getChannelCount() ? *srcPtr++ : 0.0f;
			}
	};
} // namespace Sound

#endif // SOUND_IO_H
