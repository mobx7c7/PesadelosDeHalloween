/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-05-30
***********************************************************************/
#ifndef OSCILLATOR_H
#define OSCILLATOR_H

// TODO: Oscilador
// TODO: Modulador AM
// TODO: Modulador FM
// TODO: Modulador PM
// TODO: Modulador QAM (AM + PM)
// TODO: Modulador PWM

//AM:
//  SSB (LSB = lower, USB = upper)
//  DSB

class Oscillator
{
protected:

    // frequência angular: omega = 2 * PI * freq
    float theta;
    float frequency;
    float phaseValue;
    float phaseDelta;
    float phaseOld;

public:

    Oscillator();

    Oscillator(float frequency);

    void    setFrequency(float value);

    void    setPhase(float value);

    float  getPhase();

    float  getFrequency();

    void    reset();

    float  getSine();

    float  getSquare();

    float  getSaw();

    float  getTriangle();

    float  getNoise();

    float  getPWM(float cycle);

    void    process(float step);

};

#endif // OSCILLATOR_H
