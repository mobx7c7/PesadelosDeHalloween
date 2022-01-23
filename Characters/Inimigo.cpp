/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-06-19
***********************************************************************/
#include "Inimigo.h"
#include "Jogador.h"
#include <cstdlib>

vector<Texture*> Inimigo::texturas;

void Inimigo::carregarTexturas()
{
    string path = "res//game//spr//inimigos//";
    vector<string> sprs = vector<string>
    {
        "BRUXA","DIABO","ET","FANTASMA","FRANK","KRUGER",
        "LOBIZ","MUMI","NEVES","PIN","ZASON","ZUMBI",
    };

    texturas.resize(sprs.size());

    TextureManager* textureMan = TextureManager::getInstance();

    for(int i=0; i<sprs.size(); i++)
    {
        string nome = sprs[i];
        textureMan->insert("inimigo_"+nome, TextureLoader::getInstance()->loadFile(path + nome + ".png"));
        texturas[i] = textureMan->get("inimigo_"+nome);
    }
}

Inimigo* Inimigo::criarInimigoAleatorio(double x, double y, int w, int h, double vel)
{
    Inimigo* inimigo = new Inimigo(rand() % Inimigo::texturas.size());
    inimigo->setPosicao(x+rand()%w, y+rand()%h);
    inimigo->setDestino(Jogador::jogador->getPositionX(), Jogador::jogador->getPositionY());
    inimigo->setVelocidade(vel);
    inimigo->process(0); // Atualiza os estados das variaveis
    return inimigo;
}

void Inimigo::gerarInimigos(double x, double y, int w, int h, double vel, int qtd)
{
    for(int f = 0; f < qtd; f++)
    {
        Inimigo* novoInimigo = Inimigo::criarInimigoAleatorio(x, y, w, h, vel);
        Character::listaInimigos.push_back(novoInimigo);
    }
}

void Inimigo::limparInimigos()
{
    vector<Character*>::iterator inimigo_it;
    if(!listaInimigos.empty())
    {
        for(inimigo_it = listaInimigos.begin(); inimigo_it != listaInimigos.end(); inimigo_it++)
        {
            delete *inimigo_it;
        }
        listaInimigos.clear();
    }
}

Inimigo::Inimigo(int tpInimigo)
{
    char_spr = shared_ptr<AnimatedSprite>(new AnimatedSprite(Inimigo::texturas[tpInimigo],4,4,10));
    char_spr->setFrameStart(0);
    char_spr->setFrameEnd(3);
    char_spr->setLoopable(true);

    Transform2& t1  = getTransform();
    Transform2& t2  = char_spr->getTransform();

    t1.posx         = t2.posx;
    t1.posy         = t2.posy;
    t1.width        = t2.width;
    t1.height       = t2.height;

    vida_atual      = 100;
    velocidade      = 100;
    raio            = 60;
}

Inimigo::~Inimigo()
{

}
void Inimigo::setPosicao(double x, double y)
{
    getTransform().posx = x;
    getTransform().posy = y;
}

void Inimigo::setDestino(double x, double y)
{
    this->dstx = x;
    this->dsty = y;
}

void Inimigo::setVelocidade(double velocidade)
{
    this->velocidade = velocidade;
}

double Inimigo::pegarDano()
{
    return dano;
}

void Inimigo::process(double deltaTime)
{
    //Transform2& t       = char_spr->getTransform();
    Transform2& t   = getTransform();

    double difx = dstx - getCenterX();
    double dify = dsty - getCenterY();
    ang         = atan2(dify, difx);

    if(ang > 2.4){
        //esquerda
        char_spr->setFrameStart(8);
        char_spr->setFrameEnd(12);
    }else if(ang > 0.8){
        //baixo
        char_spr->setFrameStart(0);
        char_spr->setFrameEnd(4);
    }else if(ang > -0.8){
        //direita
        char_spr->setFrameStart(12);
        char_spr->setFrameEnd(16);
    }else if(ang > -2.4){
        //cima
        char_spr->setFrameStart(4);
        char_spr->setFrameEnd(8);
    }else{
        //esquerda
        char_spr->setFrameStart(8);
        char_spr->setFrameEnd(12);
    }

    if(!char_spr->isRunning())
	{
		char_spr->start();
	}
	char_spr->process(deltaTime);

	//--------------------------------------//

    double velStep = velocidade * deltaTime;

    direcao.x = cos(ang);
    direcao.y = sin(ang);

    if(Jogador::jogador->vida_atual > 0)
    {
//        glm::vec2 alinhamento   = calcula_alinhamento(0);
//        glm::vec2 coesao        = calcula_coesao(0);

//        if(Jogador::jogador->vida_atual < 1)
//        {
//            direcao += (calcula_alinhamento(0) * 3.0f) + (calcula_coesao(0) * 3.0f) + (calcula_separacao(0) * 6.0f);
//        }
//        else
        {
            direcao += (calcula_separacao(0) * 6.0f); // += (alinhamento + 0.0f) + (coesao * 0.0f) + (separacao * 5.0f);
        }

        normalizar(direcao, 1);
        t.posx += direcao.x * velStep;
        t.posy += direcao.y * velStep;
    }
    else
    {
        t.posx += direcao.x * velStep;
        t.posy += direcao.y * velStep;
    }

    // -----------------------------------//

    Transform2& t2 = char_spr->getTransform();

    t2.posx = t.posx;
    t2.posy = t.posy;
}

void Inimigo::render(Graphics* g)
{
    char_spr->render(g);

    Transform2& t1       = getTransform();

    int largura_barra = 100;

    double xoff = getCenterX()-largura_barra/2;
    double yoff = t1.posy+40;

    g->setColor(0.5f,0.5f,0.5f,1);
    g->drawRect(xoff,yoff,100,5);
    g->setColor(0,1,0,1);
    g->drawRect(xoff,yoff,((float)largura_barra/vida_max)*(min(max(vida_atual, 0), vida_max)),5);
}
