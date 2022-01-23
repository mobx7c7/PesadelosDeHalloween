#include "Drop.h"
#include <cstdlib>

vector<Texture*>                Drop::texturas;

map<unsigned, Sound::Sampler*>  Drop::sfx;

void Drop::carregarTexturas()
{
    string path = "res//game//spr//drops//";
    vector<string> sprs = vector<string>
    {
        "item_melhora_jogador",
        "item_melhora_arma",
        "item_cartucho_arma",
        "item_protecao",
        "item_vida",
        "item_desgraça",
    };
    texturas.resize(sprs.size());
    TextureManager* textureMan = TextureManager::getInstance();
    for(int i=0; i<sprs.size(); i++)
    {
        string nome = sprs[i];
        textureMan->insert("drop_"+nome, TextureLoader::getInstance()->loadFile(path + nome + ".png"));
        texturas[i] = textureMan->get("drop_"+nome);
    }
}

void Drop::carregarSons()
{
    Sound::Loader* sndloader = Sound::Loader::getInstance();

    sndloader->setCurrentPath("res//game//sounds//item//");
    sndloader->loadFileRAW("cartucho.raw", 1, 22050, 16, true);
    sndloader->loadFileRAW("vida.raw", 1, 22050, 16, true);
    sndloader->loadFileRAW("pegar_item.raw", 2, 22050, 16, true);

    Sound::Sampler* sampler = 0;

    sampler = new Sound::Sampler("item_cartucho");
    sampler->loadWave("cartucho.raw");
    sampler->setMaxPolyphony(2);
    sfx[0] = sampler;

    sampler = new Sound::Sampler("item_vida");
    sampler->loadWave("vida.raw");
    sampler->setMaxPolyphony(1);
    sfx[1] = sampler;

    sampler = new Sound::Sampler("item_pegar");
    sampler->loadWave("pegar_item.raw");
    sampler->setMaxPolyphony(2);
    sfx[2] = sampler;
}

Drop* Drop::gerarDrop(float x, float y)
{
    // TODO: Regras para drop (nada de aleatório)
    Drop* drop = new Drop(x, y, rand() % Drop::texturas.size());
    drop->process(0); // Uma leve processada...
    return drop;
}

Drop::Drop(int x, int y, int tipo) : Drawable("Drop", 0)
{
    tex             = Drop::texturas[tipo];
    Transform2& t   = getTransform();
    t.posx          = x;
    t.posy          = y;
    t.width         = tex->getWidth();
    t.height        = tex->getHeight();
    this->tipo      = tipo;
    raio            = 50;

    switch(tipo)
    {
        case TipoDrop::MelhoraArma:
            valor = 20;
            break;
        case TipoDrop::MelhoraJogador:
            valor = 20; // tempo
            break;
        case TipoDrop::Cartucho:
            valor = 1; // quantidade
            break;
        case TipoDrop::Protecao:
            valor = 10; // tempo
            break;
        case TipoDrop::Vida:
            valor = 50; // valor
            break;
        case TipoDrop::Desgraca:
            valor = 100; // valor
            break;
    }
}

Drop::~Drop()
{

}

void Drop::process(double deltaTime)
{
    validade_tempo += deltaTime;
    if(estaVencido()) valor = 0;
}

void Drop::render(Graphics* g)
{
    Transform2& t = getTransform();
    g->drawTexture(tex, t.posx, t.posy);
}

int Drop::getTipo()
{
    return tipo;
}

int Drop::getValor()
{
    return valor;
}

bool Drop::estaVencido()
{
    return validade_tempo > validade_intervalo;
}

//void Drop::setPosition(double x, double y)
//{
//    getTransform().posx = x;
//    getTransform().posy = y;
//}

double Drop::distancia(Character* alvo)
{
    double dx = getCenterX() - alvo->getCenterX();
    double dy = getCenterY() - alvo->getCenterY();
    return hypot(dy, dx);
}

bool Drop::colidiu(Character* alvo)
{
    double dist = distancia(alvo);
    double raio = getRaio();// + alvo->getRaio();
    return dist < raio;
}

//double Drop::getPositionX()
//{
//    return getTransform().posx;
//}
//
//double Drop::getPositionY()
//{
//    return getTransform().posy;
//}

double Drop::getCenterX()
{
    Transform2& t = getTransform();
    return t.posx + t.width / 2;
}

double Drop::getCenterY()
{
    Transform2& t = getTransform();
    return t.posy + t.height / 2;
}
//
//double Drop::getHeight()
//{
//    return getTransform().height;
//}
//
//double Drop::getWidth()
//{
//    return getTransform().width;
//}

double Drop::getRaio()
{
    return raio;
}
