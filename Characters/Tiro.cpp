#include "Tiro.h"

vector<Tiro*>    Tiro::listaTiros;
vector<Texture*> Tiro::texturas;

void Tiro::carregarTexturas()
{
    string path = "res//game//spr//tiro//";
    vector<string> sprs = vector<string>
    {
        "agua","fogo","gelo","magia",
    };

    texturas.resize(sprs.size());

    TextureManager* textureMan = TextureManager::getInstance();

    for(int i=0; i<sprs.size(); i++)
    {
        string nome = sprs[i];
        textureMan->insert("tiro_"+nome, TextureLoader::getInstance()->loadFile(path + nome + ".png"));
        texturas[i] = textureMan->get("tiro_"+nome);
    }
}

void Tiro::limparTiros()
{
    vector<Tiro*>::iterator tiro_it;
    if(!listaTiros.empty())
    {
        for(tiro_it = listaTiros.begin(); tiro_it != listaTiros.end(); tiro_it++)
        {
            delete *tiro_it;
        }
        listaTiros.clear();
    }
}

Tiro::Tiro(int srcx, int srcy, int dstx, int dsty, int tipo) : Drawable("Tiro", 0)
{
    char_spr = shared_ptr<AnimatedSprite>(new AnimatedSprite(texturas[tipo],4,4,20));
    char_spr->setFrameStart(0);
    char_spr->setFrameEnd(4);
    char_spr->setLoopable(true);

    // Nota: resolve alguma coisa...
    Transform2& t1      = getTransform();
    Transform2& t2      = char_spr->getTransform();
    t1.posx             = srcx;
    t1.posy             = srcy;
    t1.width            = t2.width;
    t1.height           = t2.height;

    this->velocidade    = 2000;
    this->raio          = 20;

    // calcular angulo...
    ang = atan2(dsty - t1.posy, dstx - t1.posx);
}

Tiro::~Tiro()
{

}

double Tiro::getCenterX()
{
    Transform2& t = getTransform();
    return t.posx + t.width / 2;
}

double Tiro::getCenterY()
{
    Transform2& t = getTransform();
    return t.posy + t.height / 2;
}

double Tiro::getRaio()
{
    return raio;
}

bool Tiro::colidiu(Character* alvo)
{
    double dist = distancia(alvo);
    double raio = getRaio() + alvo->getRaio();

    return dist < raio;
}

double Tiro::distancia(Character* alvo)
{
//    Transform2& t1 = alvo->getTransform();
//    Transform2& t2 = getTransform();

    glm::vec2 dif;

    dif.x = getCenterX() - alvo->getCenterX();
    dif.y = getCenterY() - alvo->getCenterY();

    return hypot(dif.y, dif.x);
}


void Tiro::process(double deltaTime)
{
    Transform2& t1 = getTransform();
    double velStep = deltaTime * velocidade;
    t1.posx += cos(ang) * velStep;
    t1.posy += sin(ang) * velStep;

    Transform2& t2 = char_spr->getTransform();
    t2.posx = t1.posx;
    t2.posy = t1.posy;
}

void Tiro::render(Graphics* g)
{
    char_spr->render(g);
}
