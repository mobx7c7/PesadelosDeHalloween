#ifndef TIRO_H
#define TIRO_H

#include "Common/Drawable.h"
#include "Common/AnimatedSprite.h"
#include <memory> // shared_ptr
#include "Character.h"

class Tiro : public Drawable
{
    public:

        static void                 carregarTexturas();
        static void                 limparTiros();

        static vector<Tiro*>        listaTiros;
        static vector<Texture*>     texturas;

        Texture*                    textura     = 0;
        shared_ptr<Texture*>        char_atlas;
        shared_ptr<AnimatedSprite>  char_spr;

        int         velocidade  = 0;
        double      ang         = 0;
        double      raio        = 0;
        double      poder_dano  = 0;

        bool    colidiu(Character* alvo);
        double  distancia(Character* alvo);
        double  getCenterX();
        double  getCenterY();
        double  getRaio();

        Tiro(int srcx, int srcy, int dstx, int dsty, int tipo);
        virtual ~Tiro();

        void    process(double deltaTime);
        void    render(Graphics* g);
};

#endif // TIRO_H
