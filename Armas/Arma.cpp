#include "Arma.h"
#include <cstdlib>
#include <Characters\Jogador.h>

map<unsigned, Sound::Sampler*> Arma::sfx;

void Arma::carregarSons()
{
    Sound::Loader* sndloader = Sound::Loader::getInstance();

    sndloader->setCurrentPath("res//game//sounds//arma//");
    sndloader->loadFileRAW("arma0_tiro.raw", 1, 22050, 16, true);
    sndloader->loadFileRAW("arma0_vazio.raw", 1, 22050, 16, true);
    sndloader->loadFileRAW("arma0_recarga.raw", 1, 22050, 16, true);

    sndloader->loadFileRAW("arma1_tiro.raw", 1, 22050, 16, true);
    sndloader->loadFileRAW("arma1_recarga.raw", 1, 22050, 16, true);

    Sound::Sampler* sampler = 0;

    sampler = new Sound::Sampler("disparo");
    sampler->loadWave("arma0_tiro.raw");
    sampler->setMaxPolyphony(2);
    sfx[0] = sampler;

    sampler = new Sound::Sampler("vazio");
    sampler->loadWave("arma0_vazio.raw");
    sampler->setMaxPolyphony(1);
    sfx[1] = sampler;

    sampler = new Sound::Sampler("recarga");
    sampler->loadWave("arma0_recarga.raw");
    sampler->setMaxPolyphony(2);
    sfx[2] = sampler;
}

void Arma::process(double deltaTime)
{
    redisparo_tempo += deltaTime;

    if(municao_atual == 0 && cartuchos != 0)
    {
        troca_tempo += deltaTime;
        if(troca_tempo > troca_intervalo)
        {
            if(Jogador::jogador->pegarArmaAtualIndice() != 0)
            {
                cartuchos--;
            }
            municao_atual = municao_qtd;
            troca_tempo = 0;
            sfx[2]->play();
        }
    }
}

void Arma::disparar(float srcx, float srcy, float dstx, float dsty)
{
    if(redisparo_tempo > redisparo_intervalo)
    {
        if(municao_atual != 0)
        {
            Tiro* tiro = new Tiro(srcx, srcy, dstx, dsty, 0);
            tiro->poder_dano = poder_dano;
            // Nota: Uma pequena processada para atualizar
            // os estados internos das variaveis.
            tiro->process(0);

            Tiro::listaTiros.push_back(tiro);

            municao_atual--;
            sfx[0]->play(0.25f+((float)rand()/RAND_MAX)*0.1f, 0);
        }
        else
        {
            sfx[1]->play(0.25f+((float)rand()/RAND_MAX)*0.1f, 0);
        }
        redisparo_tempo = 0;
    }
}
