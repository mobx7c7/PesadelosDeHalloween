/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-06-16
***********************************************************************/
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Common/AnimatedSprite.h"
#include <memory> // shared_*
#include <cmath> // hypot()
#include "gl_includes.h" // hypot()

class Character : public Drawable
{
protected:

    bool        MOVE_LEFT       = false;
    bool        MOVE_RIGHT      = false;
    bool        MOVE_UP         = false;
    bool        MOVE_DOWN       = false;

    double      raio            = 0;
    double      raio_flocking   = 100;
    double      aceleracao      = 10;
    double      velocidade      = 100;
    glm::vec2   direcao;
    Character();

public:

    int         vida_atual      = 0;
    int         vida_max        = 100;

public:

    static vector<Character*>  listaInimigos;

    virtual         ~Character();

    virtual double  getPositionX();
    virtual double  getPositionY();
    virtual double  getHeight();
    virtual double  getWidth();
    virtual double  getCenterX();
    virtual double  getCenterY();
    virtual double  getRaio();

//    virtual void    setPosicao(double x, double y);
//    virtual void    setDestino(double x, double y);

    void            keyPressed(int key);
    void            keyReleased(int key);

    bool            colidiu(Character* alvo);
    double          distancia(Character* alvo);
    void            normalizar(glm::vec2& v, double valor);
    glm::vec2       calcula_alinhamento(Character*);
    glm::vec2       calcula_coesao(Character*);
    glm::vec2       calcula_separacao(Character*);
};



#endif // CHARACTER_H
