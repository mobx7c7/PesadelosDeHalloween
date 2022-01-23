/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-18
***********************************************************************/
#ifndef SOUND_BUFFER_H
#define SOUND_BUFFER_H

namespace Sound
{
	class Buffer
	{
		protected:

			char*       data;
			unsigned    size;

		public:

			Buffer(unsigned size, const char* data);
			Buffer();
			virtual ~Buffer();
			char*       getData();
			unsigned    getSize();
	};
} // namespace Sound

#endif // SOUND_BUFFER_H
