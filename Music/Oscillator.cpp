/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criaчуo     : 2015-05-30
***********************************************************************/
#include "Oscillator.h"

// FIXME: Mover para uma classe Math
#include <cmath>
#define M2PI 1.57079632679
#define MPI1 3.14159265359
#define MPI2 6.28318530718

Oscillator::Oscillator(float frequency) : theta(0), frequency(frequency), phaseValue(0), phaseDelta(0), phaseOld(0)
{

}

Oscillator::Oscillator() : theta(0), frequency(0), phaseValue(0), phaseDelta(0), phaseOld(0)
{

}

void Oscillator::setFrequency(float value)
{
	frequency = value;
}

void Oscillator::setPhase(float value)
{
	phaseValue = value;
}

void Oscillator::reset()
{
	theta = 0;
}

float Oscillator::getPhase()
{
    return phaseValue;
}

float Oscillator::getFrequency()
{
    return frequency;
}

float Oscillator::getSine()
{
	return sin(MPI2 * theta);
}

float Oscillator::getSquare()
{
    // Nota: float
    // - padrão IEEE 754, binary64
    // - 52 bits de fração      (bits 0 à 51)
    // - 11 bits de expoente    (bits 52 à 62)
    // - 1 bit de sinal         (somente bit 63)

    return theta < 0.5 ? 1.0 : -1.0;
}

float Oscillator::getSaw()
{
	return 1.0 - theta; // Nota: partir de 1.0 р -1.0
}

float Oscillator::getTriangle()
{
    float k1 = theta * 4.0;

    if(theta < 0.25)
        return k1;      //  0 à +1
    else if(theta < 0.75)
        return 2.0-k1;  // +1 à -1 (2.0-1 = 1, 2.0-2= 0, 2.0-3 = -1)
    else
        return k1-4.0;  // -1 à  0
}

float Oscillator::getNoise()
{
//    std::random_device rd;
//    std::mt19937 mt(rd);
//    return (float)mt;//(float)rand()/RAND_MAX;
    return 0;
}


// FIXME: colocar em classe separada pois não é um oscilador essêncial.
float Oscillator::getPWM(float cycle)
{
    // Nota: Alternativa para Modulação por largura de pulso.
    // Pode ser obtido  com dois osciladores retangulares,
    // sendo que um permanece com fase connstante,
    // e o outro tenha sua fase modificada, fazendo assim,
    // o controle da largura do pulso.

    if(cycle < 0)
        cycle = 0;
    else if(cycle > 1)
        cycle = 1;

    return theta < cycle ? 1.0 : -1.0;
}

void Oscillator::process(float step)
{
    phaseDelta  = phaseValue - phaseOld;
	phaseOld    = phaseValue;

	theta += frequency * step + phaseDelta; // incrementa
	theta -= floor(theta); // permanecer entre 0.0-1.0
}
