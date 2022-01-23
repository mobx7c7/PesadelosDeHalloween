/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-06-17
***********************************************************************/
#ifndef ENVELOPECONTROLLER_H
#define ENVELOPECONTROLLER_H

class EnvelopeController
{
protected:
    double          t_delay = 1;
    double          t_attack = 1;
    double          t_decay = 1;
    double          t_hold = 1;
    double          v_sustain = 1;
    double          t_release = 1;

    double          current_time = 0;
    double          state_time = 0;

    double          current_value = 0;
    bool            envelope_on = false;
    unsigned char   state = 0;

public:

    void on()
    {
        state = 0;
        state_time = t_delay;
        envelope_on = true;
    }
    void off()
    {
        state = 4;
        state_time = t_release;
        envelope_on = false;
    }
    double getOutput()
    {
        return current_value;
    }
    void process(double deltaTime)
    {
//        if(envelope_on)
//        {
//            if(state < 4)
//            {
//                if(current_value < 1.0)
//                {
//                    current_value += state_time/deltaTime;
//
//                    if(state == 1){ // ataque
//                        envelope_value = current_value;
//                    }else if(state == 3){ // decaida
//                        envelope_value = (1.0 - current_value);
//                    }
//                }
//                else
//                {
//                    current_value = 0;
//                    state++;
//
//                    if(state == 1){
//                        state_time = t_attack;
//                    }else if(state == 2){
//                        state_time = t_hold;
//                    }else if(state == 3){
//                        state_time = t_decay;
//                    }
//                }
//            }
//        }
//        else
//        {
//
//        }
    }
};

#endif // ENVELOPECONTROLLER_H
