/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-05-17
***********************************************************************/
#include "Sound/EnvelopeSmoother.h"

namespace Sound
{
	EnvelopeSmoother::EnvelopeSmoother()
	{

	}

	EnvelopeSmoother::~EnvelopeSmoother()
	{

	}

	void EnvelopeSmoother::setTime(const double time) // Nota: era setForce()
	{
		this->time = time;
	}
	void EnvelopeSmoother::setValue(const double value) // Nota: era setVelocity()
	{
		this->value = value;
	}
	const double& EnvelopeSmoother::getValue()
	{
		return value;
	}
	const double& EnvelopeSmoother::getResult() // Nota: era getAccel()
	{
		return result;
	}
	const double& EnvelopeSmoother::getDelta()
	{
		return deltaResult;
	}
	void EnvelopeSmoother::reset()
	{
        result = 1;
	}
	void EnvelopeSmoother::process(const double deltaTime)
	{
		step = time * deltaTime;
		if(result + step < value)
		{
			result += step;
		}
		else if(result - step > value)
		{
			result -= step;
		}
		else
		{
			result = value;
		}
//        result = value;
		deltaResult = result - pastResult;
		pastResult  = result;
	}

} // namespace Sound
