/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-05-17
***********************************************************************/
#ifndef SOUND_ENVELOPESMOOTHER_H
#define SOUND_ENVELOPESMOOTHER_H

namespace Sound
{
	class EnvelopeSmoother
	{
		protected:

			double time         = 1;
			double result       = 1;
			double value        = 1;
			double pastResult   = 0;
			double deltaResult  = 0;
			double step         = 0;

		public:

            EnvelopeSmoother();
            ~EnvelopeSmoother();
			void            setTime(const double time); // Nota: era setForce()
			void            setValue(const double value); // Nota: era setVelocity()
			const double&   getValue();
			const double&   getResult(); // Nota: era getAccel()
			const double&   getDelta();
			void            reset();
			void            process(const double deltaTime);
	};

} // namespace Sound

#endif // SOUND_ENVELOPESMOOTHER_H
