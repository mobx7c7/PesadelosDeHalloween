/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-06-19
***********************************************************************/
#ifndef INIMIGO_H
#define INIMIGO_H

#include "Character.h"

class Inimigo : public Character
{
    protected:

        double dstx = 0;
        double dsty = 0;
        shared_ptr<Texture>         char_atlas;
        shared_ptr<AnimatedSprite>  char_spr;

        double dano = 1;

        double ang = 0;

    public:

        static vector<Texture*> texturas;

        static void     carregarTexturas();
        static Inimigo* criarInimigoAleatorio(double x, double y, int w, int h, double vel);
        static void     gerarInimigos(double x, double y, int w, int h, double vel, int qtd);
        static void     limparInimigos();

        Inimigo(int);
        ~Inimigo();
        void    process(double);
        void    render(Graphics*);
        void    setDestino(double, double);
        void    setPosicao(double, double);
        void    setVelocidade(double);

        double  pegarDano();
};

typedef shared_ptr<Inimigo> InimigoPtr;

#endif // INIMIGO_H
