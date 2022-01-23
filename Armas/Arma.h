#ifndef ARMA_H
#define ARMA_H

#include "Characters/Tiro.h"
#include "Characters/Character.h"
#include "Common/Sound/Sampler.h"
#include "Common/Sound/Loader.h"
#include "Common/Sound/Loader.h"


//class Parametro
//{
//    int     type
//    bool    is_array_data;
//    void*   data;
//};
//
//
//class Parametros
//{
//    map<unsigned, void*> parametros;
//
//    bool setParameterb(unsigned parameter, bool value);
//    bool setParameterc(unsigned parameter, char value);
//    bool setParameteri(unsigned parameter, int value);
//    bool setParameterf(unsigned parameter, float value);
//    bool setParameterd(unsigned parameter, double value);
//
//    bool setParameterbv(unsigned parameter, bool* data);
//    bool setParametercv(unsigned parameter, char* data);
//    bool setParameteriv(unsigned parameter, int* data);
//    bool setParameterfv(unsigned parameter, float* data);
//    bool setParameterdv(unsigned parameter, double* data);
//};

class Arma
{
     public:

        static map<unsigned, Sound::Sampler*> sfx;

        Arma(){}
        virtual ~Arma(){}

        static void carregarSons();

        int     classe              = 0; // pistola, rifle, bomba
        bool    automatica          = false;
        int     municao_qtd         = 0;
        int     municao_atual       = 0;
        int     cartuchos           = 0;
        double  poder_dano          = 0;
        double  redisparo_intervalo = 0;
        double  redisparo_tempo     = 0;
        double  troca_intervalo     = 0;
        double  troca_tempo         = 0;

        void    process(double deltaTime);
        void    disparar(float srcx, float srcy, float dstx, float dsty);
};

class Pistola : public Arma
{
    public:

        Pistola()
        {
            automatica          = false;
            municao_qtd         = 24;
            municao_atual       = municao_qtd;
            cartuchos           = 2;
            redisparo_intervalo = 0.1;
            troca_intervalo     = 3;
            poder_dano          = 10;
        }
};

class Minigun : public Arma
{
    public:

        Minigun()
        {
            automatica          = true;
            municao_qtd         = 100;
            municao_atual       = municao_qtd;
            cartuchos           = 1;
            redisparo_intervalo = 0.1;
            troca_intervalo     = 5;
            poder_dano          = 2.5;
        }
};

class Shotgun : public Arma
{
    public:

        Shotgun()
        {
            automatica          = false;
            municao_qtd         = 8;
            municao_atual       = municao_qtd;
            cartuchos           = 3;
            redisparo_intervalo = 1;
            troca_intervalo     = 5;
            poder_dano          = 25;
        }
};

class Bomba : public Arma
{
    public:

        Bomba()
        {
            automatica          = false;
            municao_qtd         = 8;
            municao_atual       = municao_qtd;
            cartuchos           = 3;
            redisparo_intervalo = 1;
            troca_intervalo     = 5;
            poder_dano          = 25;
        }
};

#endif // ARMA_H
