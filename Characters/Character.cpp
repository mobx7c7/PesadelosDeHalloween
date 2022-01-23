/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-06-16
***********************************************************************/
#include "Character.h"
#include <algorithm> // sort

vector<Character*>      Character::listaInimigos;

Character::Character() : Drawable("Character", 0)
{

}

Character::~Character()
{

}

double Character::getPositionX()
{
    return getTransform().posx;
}

double Character::getPositionY()
{
    return getTransform().posy;
}

double Character::getHeight()
{
    return getTransform().height;
}

double Character::getWidth()
{
    return getTransform().width;
}

double Character::getCenterX()
{
    Transform2& t = getTransform();
    return t.posx + t.width / 2;
}

double Character::getCenterY()
{
    Transform2& t = getTransform();
    return t.posy + t.height / 2;
}

double Character::getRaio()
{
    return raio;
}

void Character::keyPressed(int key)
{
    switch(key)
    {
        case GLFW_KEY_W:
            MOVE_UP = true;
            break;
        case GLFW_KEY_S:
            MOVE_DOWN = true;
            break;
        case GLFW_KEY_A:
            MOVE_LEFT = true;
            break;
        case GLFW_KEY_D:
            MOVE_RIGHT = true;
            break;
    }
}

void Character::keyReleased(int key)
{
    switch(key)
    {
        case GLFW_KEY_W:
            MOVE_UP = false;
            break;
        case GLFW_KEY_S:
            MOVE_DOWN = false;
            break;
        case GLFW_KEY_A:
            MOVE_LEFT = false;
            break;
        case GLFW_KEY_D:
            MOVE_RIGHT = false;
            break;
    }
}

double Character::distancia(Character* alvo)
{
//    Transform2& t1 = c->getTransform();
//    Transform2& t2 = getTransform();

    glm::vec2 dif;

//    dif.x = t2.posx - t1.posx;
//    dif.y = t2.posy - t1.posy;

    dif.x = getCenterX() - alvo->getCenterX();
    dif.y = getCenterY() - alvo->getCenterY();

    return hypot(dif.y, dif.x);
}

bool Character::colidiu(Character* alvo)
{
    double dist = distancia(alvo);//hypot(dify, difx); //difx * difx + dify * dify;
    double raio = getRaio() + alvo->getRaio(); //(raioJoga + raioPers) * (raioJoga + raioPers);

    //cout << dist1 << ", " << raio1 << endl;

    return dist < raio;
}

void Character::normalizar(glm::vec2& v, double valor)
{
    double mag = v.x*v.x + v.y*v.y;
    if (mag == 0) return;
    v *= valor/sqrt(mag);
}

glm::vec2 Character::calcula_alinhamento(Character* alvo)
{
    glm::vec2 v;
    int vizinhos = 0;

    for (Character* agente : listaInimigos)
    {
        if (this != agente)
        {
            if (this->distancia(agente) < raio_flocking)
            {
                Transform2& t = agente->getTransform();
                v.x += agente->direcao.x;
                v.y += agente->direcao.y;
                vizinhos++;
            }
        }
    }

    if (vizinhos == 0) return v;

    v /= vizinhos;

    normalizar(v, 1);

    return v;
}

glm::vec2 Character::calcula_coesao(Character* alvo)
{
    glm::vec2   v;
    int vizinhos = 0;

    for (Character* agente : listaInimigos)
    {
        if (this != agente)
        {
            if (this->distancia(agente) < raio_flocking)
            {
                Transform2& t = agente->getTransform();
                v.x += t.posx;
                v.y += t.posy;
                vizinhos++;
            }
        }
    }

    if (vizinhos == 0) return v;

    v /= vizinhos;

    Transform2& t = getTransform();
    v = glm::vec2(v.x - t.posx, v.y - t.posy);

    normalizar(v, 1);

    return v;
}

glm::vec2 Character::calcula_separacao(Character* alvo)
{
    glm::vec2 v;
    int vizinhos = 0;

    for (Character* agente : listaInimigos)
    {
        if (this != agente)
        {
            if (this->distancia(agente) < raio_flocking)
            {
                Transform2& t1 = agente->getTransform();
                Transform2& t2 = getTransform();
                v.x += t1.posx - t2.posx;
                v.y += t1.posy - t2.posy;
                vizinhos++;
            }
        }
    }

    if (vizinhos == 0) return v;

    v /= vizinhos;

    v *= -1;

    normalizar(direcao, 1);

    return v;
}
