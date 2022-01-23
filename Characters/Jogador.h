/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-06-19
***********************************************************************/
#ifndef JOGADOR_H
#define JOGADOR_H

#include "Character.h"
#include "Drop.h"
#include "Armas/Arma.h"
#include "Armas/Arma.h"

class Jogador : public Character
{
    public:

        static Jogador*                 jogador;
        static vector<Texture*>         texturas;
        Jogador();
        ~Jogador();

        map<unsigned, Arma*>            arma_lista;
        vector<Arma*>                   listaArmas;
        shared_ptr<AnimatedSprite>      char_spr;
        int                             arma_atual = 0;
        double                          invencibilidade_tempo = 0;
        Effect*                         cores = 0;

        void    process(double);
        void    render(Graphics*);
        void    setDestino(double, double);
        void    setPosicao(double, double);
        void    inserirArma(unsigned indice, Arma* arma);
        void    selecionarArma(unsigned);
        Arma*   pegarArmaPorIndice(unsigned);
        Arma*   pegarArmaAtual();
        int     pegarArmaAtualIndice();
        void    aplicarDrop(Drop* drop);

    public:

        static void carregarTexturas();
};

#endif // JOGADOR_H
