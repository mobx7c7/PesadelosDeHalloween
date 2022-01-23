#ifndef DROP_H
#define DROP_H

#include "Character.h"
#include "Common/Drawable.h"
#include "Common/Sound/Sampler.h"
#include "Common/Sound/Loader.h"
#include <memory> // shared_ptr

enum TipoDrop
{
    MelhoraJogador,
    MelhoraArma,
    Cartucho,
    Protecao,
    Vida,
    Desgraca,
};

class Drop : public Drawable
{
protected:

    Texture*    tex                 = 0;
    int         tipo                = 0;
    int         valor               = 0;
    double      raio                = 0;
    double      validade_tempo      = 0;
    double      validade_intervalo  = 30;

public:

    static vector<Texture*>                 texturas;
    static map<unsigned, Sound::Sampler*>   sfx;

    static void                             carregarTexturas();
    static void                             carregarSons();
    static Drop*                            gerarDrop(float x, float y);

    void    setPosition(double, double);
    bool    estaVencido();
    bool    colidiu(Character* alvo);
    int     getTipo();
    int     getValor();
    double  distancia(Character* alvo);
    double  getCenterX();
    double  getCenterY();
    double  getRaio();

    Drop(int x, int y, int tipo);
    virtual ~Drop();

    void    process(double);
    void    render(Graphics*);

};

//class Drop_cartucho
//{
//public:
//    Drop
//};
//
//class Drop_vida
//{
//
//};
//
//class Drop_melhora_arma
//{
//
//};
//
//class Drop_melhora_jogador
//{
//
//};


#endif // DROP_H
