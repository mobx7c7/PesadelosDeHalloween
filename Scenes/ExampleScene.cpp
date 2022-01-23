/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-16
***********************************************************************/
#include "ExampleScene.h"


ExampleScene* ExampleScene::instance = 0;

ExampleScene* ExampleScene::getInstance()
{
    if(!instance) instance = new ExampleScene();
    return instance;
}

void ExampleScene::destroyInstance()
{
    if(instance) delete instance;
    instance = 0;
}

ExampleScene::ExampleScene() : Scene("Example scene 1")
{
    Window* window  = WindowManager::getInstance()->getDefaultWindow();
	wndwidth        = window->getWidth();
	wndheight       = window->getHeight();

	//--------------- RECURSOS SOM -----------------//
    {
        Sound::Loader* sndloader = Sound::Loader::getInstance();

//        sndloader->setCurrentPath("res//game//sounds//arma//");
//        sndloader->loadFileRAW("arma0_tiro.raw", 1, 22050, 16, true);
//        sndloader->loadFileRAW("arma0_vazio.raw", 1, 22050, 16, true);
//        sndloader->loadFileRAW("arma0_recarga.raw", 1, 22050, 16, true);
//
//        sampler = new Sound::Sampler("disparo");
//        sampler->loadWave("arma0_tiro.raw");
//        sampler->setMaxPolyphony(2);
//        sndsamples.push_back(sampler);
//
//        sampler = new Sound::Sampler("vazio");
//        sampler->loadWave("arma0_vazio.raw");
//        sampler->setMaxPolyphony(1);
//        sndsamples.push_back(sampler);
//
//        sampler = new Sound::Sampler("recarga");
//        sampler->loadWave("arma0_recarga.raw");
//        sampler->setMaxPolyphony(2);
//        sndsamples.push_back(sampler);

        Arma::carregarSons();
        Drop::carregarSons();

        sndloader->setCurrentPath("res//game//sounds//");
        sndloader->loadFileRAW("ding.raw", 1, 44100, 16, true);
        sndloader->loadFileRAW("parar.raw", 1, 44100, 16, true);

        sndloader->setCurrentPath("res//game//sounds//arma//");
        sndloader->loadFileRAW("hit.raw", 1, 22050, 16, true);

        Sound::Sampler* sampler;

        sampler = new Sound::Sampler("ding");
        sampler->loadWave("ding.raw");
        sampler->setMaxPolyphony(10);
        sfx[0] = sampler;

        sampler = new Sound::Sampler("parar");
        sampler->loadWave("ding.raw");
        sampler->setMaxPolyphony(10);
        sfx[1] = sampler;

        sampler = new Sound::Sampler("hit");
        sampler->loadWave("hit.raw");
        sampler->setMaxPolyphony(10);
        sfx[2] = sampler;


        textureSynth = new TextureSynth();
    }

	//-------------- RECURSOS TEXTURAS ---------------//
	{
        Jogador::carregarTexturas();
        Inimigo::carregarTexturas();
        Drop::carregarTexturas();
        Tiro::carregarTexturas();

        string path  = "res//game//bg//";
        vector<string> sprs = vector<string>
        {
            "cenario1", "cenario2", "cenario3", "cenario4",
        };

        backgrounds.resize(sprs.size());

        TextureManager* textureMan = TextureManager::getInstance();

        for(int i=0; i<sprs.size(); i++)
        {
            string nome = sprs[i];
            textureMan->insert("back_"+nome, TextureLoader::getInstance()->loadFile(path + sprs[i] + ".jpg"));
            backgrounds[i] = textureMan->get("back_"+nome);
        }
    }

    //--------------- PERSONAGENS -----------------//

    Jogador::jogador = new Jogador();

    srand(time(0));

//    for(int f = 0; f < 40; f++) listaInvetario.push_back(Drop::criarDropAleatorio(0,0));

    Inimigo::gerarInimigos(wndwidth, 0, 200, wndheight, padrao_inimigo_vel_atual, padrao_inimigo_qtd_atual);

    textureSynth->musica_tocar();
}

ExampleScene::~ExampleScene()
{
    Tiro::limparTiros();

    // Nota: Esses itens abaixo não são globais!!
    // Nota: Esses itens abaixo não são globais!!
    // Nota: Esses itens abaixo não são globais!!

    limpaListaDrop();

//    if(!listaInvetario.empty())
//    {
//        for(drop_it = listaInvetario.begin(); drop_it != listaInvetario.end(); drop_it++)
//        {
//            delete *drop_it;
//        }
//        listaInvetario.clear();
//    }
}

void ExampleScene:: limpaListaDrop()
{
    vector<Drop*>::iterator drop_it;
    if(!listaDrop.empty())
    {
        for(drop_it = listaDrop.begin(); drop_it != listaDrop.end(); drop_it++)
        {
            delete *drop_it;
        }
        listaDrop.clear();
    }
}

void ExampleScene::reiniciarJogo()
{
    background_mixar_ativo      = 0;
    background_mixar_fator      = 0;
    background_atual_a          = 0;
    background_atual_b          = 1;
    background_troca_prox       = 3;// na wave 1
    background_troca_passo      = 3;// na wave 1
    multiplicador_tempo         = 1;
    wave_atual                  = 1;
    wave_tempo                  = 0;
    wave_intervalo              = 3;
    tiro_tempo                  = 0;
    tiro_intervalo              = 1;
    spawn_intervalo             = 10;
    spawn_tempo                 = 0;
    padrao_inimigo_vel_atual    = 50;
    padrao_inimigo_vel_incr     = 10;
    padrao_inimigo_qtd_atual    = 5;
    padrao_inimigo_qtd_incr     = 1;

    limpaListaDrop();
    Tiro::limparTiros();
    Inimigo::limparInimigos();
    Inimigo::gerarInimigos(wndwidth, 0, 200, wndheight, padrao_inimigo_vel_atual, padrao_inimigo_qtd_atual);

    textureSynth->musica_mudar_tempo(1.0f);
    textureSynth->musica_tocar();

    delete Jogador::jogador;
    Jogador::jogador = new Jogador();

    reiniciar = false;
}

void ExampleScene::process(double deltaTime)
{
    if(Jogador::jogador->vida_atual < 1 && reiniciar)
    {
        reiniciarJogo();
    }

    // Fazer um "slowdown" entre transição (é legal...)
    {
        if(pause || Transition::getInstance()->isFading())
        {
            if(multiplicador_tempo > 0.1){
                multiplicador_tempo -= deltaTime * 0.5;
            }else{
                multiplicador_tempo = 0.1;
            }
        }else{
            if(multiplicador_tempo < 1){
                multiplicador_tempo += deltaTime * 0.5;
            }else{
                multiplicador_tempo = 1;
            }
        }

        deltaTime *= multiplicador_tempo;
    }
    //------------- PROCESSAMENTO GERAL --------------//
    {
        Scene::process(deltaTime);

        Jogador::jogador->process(deltaTime);

        vector<Tiro*>::iterator tiro_it;
        for(tiro_it = Tiro::listaTiros.begin(); tiro_it != Tiro::listaTiros.end(); tiro_it++){
            Tiro* tiro = *tiro_it;
            tiro->process(deltaTime);
        }

        vector<Character*>::iterator inimigo_it;
        for(inimigo_it = Character::listaInimigos.begin(); inimigo_it != Character::listaInimigos.end(); inimigo_it++){
            Character* inimigo = *inimigo_it;
            inimigo->process(deltaTime);
        }

        vector<Drop*>::iterator drop_it;
        for(drop_it = listaDrop.begin(); drop_it != listaDrop.end(); drop_it++){
            Drop* drop = *drop_it;
            drop->process(deltaTime);
        }
    }
    //--------------- SPAWM INIMIGOS -----------------//
    {
    //    spawn_tempo += deltaTime;
    //    if(spawn_tempo > spawn_intervalo)
    //    {
    //        Character::listaInimigos.push_back(Inimigo::criarInimigoAleatorio(wndwidth, rand()%wndheight, padrao_inimigo_velocidade));
    //        sort(Character::listaInimigos.begin(),  Character::listaInimigos.end());
    //        spawn_tempo = 0;
    //    }

        if(Character::listaInimigos.size() == 0)
        {
            if(textureSynth->musica_esta_tocando()){
                textureSynth->musica_parar();
                sfx[1]->play();
            }

            wave_tempo += deltaTime;
            if(wave_tempo > wave_intervalo)
            {
                Inimigo::gerarInimigos(wndwidth, 0, 200, wndheight, padrao_inimigo_vel_atual, padrao_inimigo_qtd_atual);
                padrao_inimigo_vel_atual += padrao_inimigo_vel_incr;
                padrao_inimigo_qtd_atual += padrao_inimigo_qtd_incr;
                wave_atual++;
                wave_tempo = 0;

                textureSynth->musica_mudar_tempo(1.0f + wave_atual * 0.05f);
                textureSynth->musica_tocar();
            }
        }
    }
    //---------------- CONTROLE ARMA -----------------//
    {
        // Nota: Preguiça de digitar Jogador::jogador... ;D
        Jogador* jog = Jogador::jogador;
        if(jog->vida_atual > 0)
        {
            Arma* arma = jog->pegarArmaAtual();
            if(arma != 0)
            {
                arma->process(deltaTime);
                if(mouseBotao1)
                {
                    arma->disparar(jog->getCenterX(), jog->getCenterY(), mouseX, mouseY);
                    if(!arma->automatica)
                    {
                        mouseBotao1 = false;
                    }
                }
            }
        }
    }
    //------------------- TESTES ---------------------//
    {
        if(pause || Transition::getInstance()->isFading()) return;

        vector<Character*>::iterator inimigo_it;
        for(inimigo_it = Character::listaInimigos.begin(); inimigo_it != Character::listaInimigos.end(); inimigo_it++)
        {
            Inimigo* inimigo = (Inimigo*)*inimigo_it;

            inimigo->setDestino(Jogador::jogador->getCenterX(), Jogador::jogador->getCenterY());

            vector<Tiro*>::iterator tiro_it;
            for(tiro_it = Tiro::listaTiros.begin(); tiro_it != Tiro::listaTiros.end(); tiro_it++)
            {
                Tiro* tiro = *tiro_it;
                if(tiro->colidiu(inimigo))
                {
                    sfx[2]->play(0.15f, 0);
                    cout << "removendo tiro " << tiro->getIdent() <<  ", poder_dano : " << tiro->poder_dano << endl;
                    inimigo->vida_atual -= tiro->poder_dano;
                    Tiro::listaTiros.erase(tiro_it);
                    break;
                }
            }

            if(inimigo->colidiu(Jogador::jogador) && Jogador::jogador->invencibilidade_tempo < 1)
            {
                Jogador::jogador->vida_atual -= inimigo->pegarDano();
            }

            if(inimigo->vida_atual < 1)
            {
                // FIXME: fazer regras de drop
                // Nota: chance de aparecer um drop...
//                if(rand()%5 == 0)
                {
                    listaDrop.push_back(Drop::gerarDrop(inimigo->getCenterX(), inimigo->getCenterY()));
                }

                sfx[0]->play();

                delete inimigo;
                Character::listaInimigos.erase(inimigo_it);
                inimigo_it--;
                //Character::listaInimigos.push_back(Inimigo::criarInimigoAleatorio(rand()%wndwidth, rand()%wndheight));
            }
        }

        vector<Tiro*>::iterator tiro_it;
        for(tiro_it = Tiro::listaTiros.begin(); tiro_it != Tiro::listaTiros.end(); tiro_it++)
        {
            Tiro* tiro = *tiro_it;

            Transform2& t = tiro->getTransform();
            bool tiroDentroDoMapa = t.posx >= 0 && t.posx < wndwidth+t.width  && t.posy >= 0 && t.posy < wndheight+t.height;

            if(!tiroDentroDoMapa)
            {
                delete *tiro_it;
                Tiro::listaTiros.erase(tiro_it);
                tiro_it--;
            }
        }

        vector<Drop*>::iterator drop_it;
        for(drop_it = listaDrop.begin(); drop_it != listaDrop.end(); drop_it++)
        {
            Drop* drop = *drop_it;

            bool colidiu    = drop->colidiu(Jogador::jogador);
            bool venceu     = drop->estaVencido();

            if(colidiu || venceu)
            {
                if(colidiu)
                {
                    Jogador::jogador->aplicarDrop(drop);
                }
                //cout << "removendo drop " << drop->getIdent() << endl;
                delete *drop_it;
                listaDrop.erase(drop_it);
                drop_it--;
            }
        }
    }
    //----------------- BACKGROUND -------------------//
    {
        if(background_troca_prox <= wave_atual)
        {
            background_troca_prox += background_troca_passo;
            background_mixar_ativo = true;
        }

        if(background_mixar_ativo)
        {
            background_mixar_fator += deltaTime * 0.25f;
            if(background_mixar_fator > 1)
            {
                background_atual_a      = (background_atual_a+1)%backgrounds.size();
                background_atual_b      = (background_atual_b+1)%backgrounds.size();
                background_mixar_fator  = 0;
                background_mixar_ativo  = false;
            }
        }
    }
}

void ExampleScene::render(Graphics* g)
{
    Framebuffer2* currentFbuf = getFramebuffer();
    glBindFramebuffer(GL_FRAMEBUFFER, currentFbuf ? currentFbuf->getObjectID() : 0);

    Scene::render(g);

    if(background_mixar_ativo)
    {
        Blending* blending = Blending::getInstance();
        blending->setFrameA(backgrounds[ background_atual_a ]);
        blending->setFrameB(backgrounds[ background_atual_b ]);
        blending->setMix(background_mixar_fator);
        blending->render(g);
    }
    else
    {
        g->drawTexture(backgrounds[ background_atual_a ], 0, 0, wndwidth, wndheight);
    }

    //--------------------------------//

    map<float, Drawable*> drawablesOrdenados;

    for(Drop* drop : listaDrop)
    {
        Transform2& t = drop->getTransform();
        drawablesOrdenados[t.posy] = drop;
    }
    for(Tiro* tiro : Tiro::listaTiros)
    {
        Transform2& t = tiro->getTransform();
        drawablesOrdenados[t.posy] = tiro;
    }
    for(Character* inimigo : Character::listaInimigos)
    {
        Transform2& t = inimigo->getTransform();
        drawablesOrdenados[t.posy+t.height/2] = inimigo;
    }

    Transform2& t = Jogador::jogador->getTransform();
    drawablesOrdenados[t.posy+t.height/2] = Jogador::jogador;

    map<float, Drawable*>::iterator drawable_it     = drawablesOrdenados.begin();
    map<float, Drawable*>::iterator drawable_fim    = drawablesOrdenados.end();
    for(;drawable_it != drawable_fim; drawable_it++)
    {
        drawable_it->second->render(g);
    }

    //--------------------------------//

    textureSynth->render(g);   // FIXME: textureSynth - tornar modulo de som e grafico separados!

    //--------------------------------//

    stringstream ss;

    if(pause)
    {
        g->setColor(0.5f,0.5f,0.5f,0.5f);
        g->drawRect(50,50,wndwidth-100,wndheight-100);
        int offx = 0;
        for(int i=0; i<listaInvetario.size(); i++)
        {
            Texture* item_tex = Drop::texturas[listaInvetario[i]->getTipo()];
            int auxX = i%9;
            int auxY = i/9;
            double posiX = item_tex->getWidth() * auxX + 50;
            double posiY = item_tex->getHeight() * auxY + 50;
            g->drawTexture(item_tex, posiX, posiY);
        }
        // Nota: somente alpha terá efeito!
        g->setColor(0,0,0,1.0f);
        g->drawText("PAUSADO!", wndwidth/2, wndheight/2);
    }
    else
    {
        Arma* arma = Jogador::jogador->pegarArmaAtual();

        ss << "Arma " << Jogador::jogador->pegarArmaAtualIndice() << " | ";

        if(arma != 0){
            if(arma->municao_atual != 0){
                ss << "Balas: " << arma->municao_atual << " | Cartuchos: " << arma->cartuchos;
            }else if(arma->municao_atual == 0 && arma->cartuchos != 0){
                ss << "Trocando pente... (" << (int)arma->troca_intervalo << " seg.)";
            }else{
                ss << "Arma inabilitada.";
            }
        }else{
            ss << "Vazio";
        }
        g->drawText(ss.str(), 25, wndheight-25);
    }

    ss.str("");
    ss << "Wave: " << wave_atual << " | Tiros: " << Tiro::listaTiros.size();
    g->drawText(ss.str(), 25, 25);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if(Jogador::jogador->vida_atual < 1)
    {
        // voce morreu, pressione espaço para reiniciar
        g->setColor(1,0,0,0.25f);
        g->drawRect(0,0,wndwidth,wndheight);
    }
    glDisable(GL_BLEND);
    g->setColor(1,1,1,1);

    Framebuffer2* parentFbuf = getParent() ? ((Drawable*)getParent())->getFramebuffer() : 0;
    glBindFramebuffer(GL_FRAMEBUFFER, parentFbuf ? parentFbuf->getObjectID() : 0);
}

void ExampleScene::mouseMoved(int x, int y)
{
    Scene::mouseMoved(x,y);

    mouseX = x;
    mouseY = y;
}

void ExampleScene::mousePressed(int x, int y, int button)
{
    Scene::mousePressed(x,y,button);
    switch(button)
    {
        case GLFW_MOUSE_BUTTON_1:

            textureSynth->pintar_pixel(x,y);
            mouseBotao1 = true;
            mouseX      = x;
            mouseY      = y;
            break;
    }
}

void ExampleScene::mouseReleased(int x, int y, int button)
{
    Scene::mouseReleased(x,y,button);
    switch(button)
    {
        case GLFW_MOUSE_BUTTON_1:

            mouseBotao1 = false;
            break;
    }
}

void ExampleScene::keyPressed(int key)
{
    Scene::keyPressed(key);
    switch(key)
    {
    case GLFW_KEY_SPACE:

        if(Jogador::jogador->vida_atual < 1) reiniciar = true;//reiniciar();

        break;

    case GLFW_KEY_ESCAPE:

        GraphicsRenderer::getInstance()->stop();
        break;

    case GLFW_KEY_V:

        if(!textureSynth->mapa_esta_sendo_desenhado()){
            textureSynth->mapa_mostrar();
        }else{
            textureSynth->mapa_esconder();
        }
        break;

    case GLFW_KEY_B:

        if(!textureSynth->musica_esta_tocando())
            textureSynth->musica_tocar();
        else
            textureSynth->musica_parar();
        break;

    case GLFW_KEY_N:

        textureSynth->mapa_gerar();
        break;

    case GLFW_KEY_M:

        textureSynth->mapa_limpar();
        break;

    case GLFW_KEY_P:

        pause = !pause;
        break;

    case GLFW_KEY_1:

        Jogador::jogador->selecionarArma(0);
        break;

    case GLFW_KEY_2:

        Jogador::jogador->selecionarArma(1);
        break;

    case GLFW_KEY_3:

        Jogador::jogador->selecionarArma(2);
        break;

    case GLFW_KEY_4:

        Jogador::jogador->selecionarArma(3);
        break;

    case GLFW_KEY_5:

        Jogador::jogador->selecionarArma(4);
        break;

    case GLFW_KEY_6:

        Jogador::jogador->selecionarArma(5);
        break;

    case GLFW_KEY_7:

        Jogador::jogador->selecionarArma(6);
        break;
    }

    Jogador::jogador->keyPressed(key);
}

void ExampleScene::keyReleased(int key)
{
    Scene::keyReleased(key);
    switch(key)
    {
        case GLFW_KEY_3:
            mapa_gerar = false;
            break;
    }

    Jogador::jogador->keyReleased(key);
}

void ExampleScene::windowResized(int w, int h)
{
    Scene::windowResized(w, h);
    wndwidth    = w;
    wndheight   = h;

    Blending::getInstance()->windowResized(w,h);

//  (monitorSelected->getWidth() - width)/2,
//  (monitorSelected->getHeight() - height)/2);

//    back_spr_a->getTransform().width  = wndwidth;
//    back_spr_a->getTransform().height = wndheight;

//	float aspect_w = ((float)backimg->getWidth()/backimg->getHeight()) * ((float)h/w);
//	float aspect_h = ((float)backimg->getHeight()/backimg->getWidth()) * ((float)w/h);
//
//    if(aspect_h > 1)
//        backspr->getTransform().height *= aspect_h;
}
