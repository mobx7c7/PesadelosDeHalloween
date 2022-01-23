/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-06-19
***********************************************************************/
#include "Jogador.h"

vector<Texture*> Jogador::texturas;

void Jogador::carregarTexturas()
{
    string          path;
    vector<string>  sprs;

    path = "res//game//spr//jogador//";
    sprs = vector<string>
    {
        "GLOCK","DESERT","SHOTGUM","METRALHADORA",
        "GATLING","SNIPER","BAZUCA",
    };

    texturas.resize(sprs.size());

    TextureManager* textureMan = TextureManager::getInstance();

    for(int i=0; i<sprs.size(); i++)
    {
        string nome = sprs[i];
        textureMan->insert("jogador_"+nome, TextureLoader::getInstance()->loadFile(path + nome + ".png"));
        texturas[i] = textureMan->get("jogador_"+nome);
    }
}

Jogador* Jogador::jogador = 0;

Jogador::Jogador()
{
    arma_atual = 0;
    listaArmas = vector<Arma*>(7, nullptr);

	char_spr = shared_ptr<AnimatedSprite>(new AnimatedSprite(texturas[0],4,4,10));
    char_spr->setFrameStart(0);
	char_spr->setFrameEnd(3);
	char_spr->setLoopable(true);

    Transform2& t1  = getTransform();
    Transform2& t2  = char_spr->getTransform();

    t1.posx         = t2.posx;
    t1.posy         = t2.posy;
    t1.width        = t2.width;
    t1.height       = t2.height;

    vida_atual  = vida_max = 100;
	velocidade  = 100;
	raio        = 60;

    cores = EffectManager::getInstance()->get("Explosao atari");

    inserirArma(0, new Pistola());
    inserirArma(1, new Minigun());
    inserirArma(2, new Shotgun());
    selecionarArma(0);
}

Jogador::~Jogador()
{
//    vector<Arma*>::iterator arma_it;
//    for(arma_it = listaArmas.begin(); arma_it != listaArmas.end(); arma_it++){
//        delete *arma_it;
//        listaArmas.erase(arma_it);
//    }
}

//void Jogador::setPosicao(double positionX, double positionY)
//{
//    Transform2& t   = getTransform();
//    t.posx          = positionX;
//    t.posy          = positionY;
//}

void Jogador::process(double deltaTime)
{
    if(vida_atual < 1) return;

    Transform2& t1       = getTransform();

    double accStep      = aceleracao * deltaTime;
    double velStep      = velocidade * deltaTime;

    bool MOVE_ANY       = MOVE_LEFT && MOVE_RIGHT && MOVE_UP && MOVE_DOWN;
	bool MOVE_ALL       = MOVE_LEFT || MOVE_RIGHT || MOVE_UP || MOVE_DOWN;
    bool MOVE_HOR_LOCK  = MOVE_LEFT && MOVE_RIGHT;
    bool MOVE_VER_LOCK  = MOVE_UP && MOVE_DOWN;

    if(MOVE_LEFT && !MOVE_HOR_LOCK)
    {
        direcao.x = -1;
        char_spr->setFrameStart(8);
        char_spr->setFrameEnd(11);
    }
    else if(MOVE_RIGHT && !MOVE_HOR_LOCK)
    {
        direcao.x = +1;
        char_spr->setFrameStart(12);
        char_spr->setFrameEnd(15);
    }
    else
    {
        direcao.x = 0;
    }

    if(MOVE_UP && !MOVE_VER_LOCK)
    {
        direcao.y = -1;
        char_spr->setFrameStart(4);
        char_spr->setFrameEnd(7);
    }
    else if(MOVE_DOWN && !MOVE_VER_LOCK)
    {
        direcao.y = +1;
        char_spr->setFrameStart(0);
        char_spr->setFrameEnd(3);
    }
    else
    {
        direcao.y = 0;
    }

    // Nota: pressionar para os dois lados não leva a lugar algum.
	if(MOVE_HOR_LOCK || MOVE_VER_LOCK || !MOVE_ALL)
	{
	    if(char_spr->isRunning()) char_spr->stop();
	}
	else if(!char_spr->isRunning())
	{
		char_spr->start();
	}

    if(!MOVE_VER_LOCK)
    {
        t1.posx += velStep * direcao.x;
//        t1.posx += direcao.x;
    }
    if(!MOVE_HOR_LOCK)
    {
        t1.posy += velStep * direcao.y;
//        t1.posy += direcao.y;
    }

    char_spr->process(deltaTime);

    if(invencibilidade_tempo > 0){
        invencibilidade_tempo -= deltaTime;
    }else{
        invencibilidade_tempo = 0;
    }

    //----------------------------------------//

    //glm::vec2 alinhamento   = calcula_alinhamento(jogador);
    //glm::vec2 coesao        = calcula_coesao(jogador);

    glm::vec2 separacao     = calcula_separacao(jogador);
    direcao += (separacao * 3.0f); // += (alinhamento + 0.0f) + (coesao * 0.0f) + (separacao * 5.0f);
    normalizar(direcao, 1);
//    t1.posx += direcao.x * velStep;
//    t1.posy += direcao.y * velStep;
    t1.posx += direcao.x * velStep;
    t1.posy += direcao.y * velStep;

    // -----------------------------------//

    Transform2& t2 = char_spr->getTransform();

    t2.posx = t1.posx;
    t2.posy = t1.posy;

    // -----------------------------------//
}

void Jogador::render(Graphics* g)
{
    if(char_spr == 0 ) return;

    if(vida_atual < 1) return;

    if(invencibilidade_tempo > 0){
        g->setEffect(cores);
    }else{
        g->setEffect(0);
    }

    char_spr->render(g);

    g->setEffect(0);

    Transform2& t1 = getTransform();

    int largura_barra = 100;

    double xoff = getCenterX()-largura_barra/2;
    double yoff = t1.posy + 80;

    g->setColor(0.5f,0.5f,0.5f,1);
    g->drawRect(xoff,yoff,100,5);
    g->setColor(0,1,0,1);
    g->drawRect(xoff,yoff,((float)largura_barra/vida_max)*(min(max(vida_atual, 0), vida_max)),5);

//    g->setColor(0.5f,0.5f,0.5f,0.5f);
//    g->drawRect(0,0,500,80);
}

void Jogador::inserirArma(unsigned indice, Arma* arma)
{
    arma_lista[indice] = arma;
}

void Jogador::selecionarArma(unsigned indice)
{
    char_spr->setTexturePtr(texturas[indice]);
    arma_atual = indice;
}

Arma* Jogador::pegarArmaPorIndice(unsigned indice)
{
    return arma_lista[indice];
}

Arma* Jogador::pegarArmaAtual()
{
    return arma_lista[arma_atual];
}

int Jogador::pegarArmaAtualIndice()
{
    return arma_atual;
}

void Jogador::aplicarDrop(Drop* drop)
{
    if(drop == 0) return;

    Arma* arma = arma_lista[arma_atual];

    switch(drop->getTipo())
    {
        case TipoDrop::MelhoraArma:

            Drop::sfx[2]->play();
            //if(arma) arma->cartuchos += drop->getValor();
            break;

        case TipoDrop::MelhoraJogador:

            Drop::sfx[2]->play();
            //invencibilidade_tempo += drop->getValor();
            break;

        case TipoDrop::Cartucho:

            Drop::sfx[0]->play();
            arma->cartuchos += drop->getValor();
            break;

        case TipoDrop::Protecao:

            Drop::sfx[2]->play();
            invencibilidade_tempo = drop->getValor();
            break;

        case TipoDrop::Vida:

            Drop::sfx[1]->play();
            vida_atual += drop->getValor(); // fator
            break;

        case TipoDrop::Desgraca:

            Drop::sfx[2]->play();
            vida_atual -= drop->getValor(); // fator
            break;
    }
}
