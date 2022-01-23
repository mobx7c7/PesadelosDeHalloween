/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-05-30
***********************************************************************/
#include "TextureSynth.h"
#include <algorithm>
#include <cstring>  // Nota: memset
#include <cstdlib>  // Nota: rand()
#include <ctime>    // Nota: time() (em "srand(time(0))")

TextureSynth::TextureSynth()
{
    chordBank.readChordFile("res\\notes.txt");
    oscSynth.resize(4, Oscillator());
    chordNameProx   = 1;
    chordNames      = chordBank.getChordNames();
    musica_gerar_notas();

    //-----------------------------------------------------------//

    cellMapw        = 512;
    cellMaph        = 512;
    cellByteSize    = sizeof(float);
    cellMapl        = cellMapw * cellMaph;
    cellMapvec.resize(cellMapl);
    cellLinvec.resize(cellMapw);
    cellTexture     = new Texture(cellMapw, cellMaph, GL_RGBA, GL_RED, GL_FLOAT, 0);
    cellTexture->setWrapS(GL_CLAMP_TO_BORDER);

    mapa_limpar();
	mapa_gerar();

	resampler.setData(cellMapl, 1, 32, true, true, (char*)cellMapvec.data());
	createModuleIO(0, 2);

    //--------------- RECURSOS SOM -----------------//

    Sound::Loader* sndloader = Sound::Loader::getInstance();

    sndloader->setCurrentPath("res//game//sounds//inst//");
	sndloader->loadFileRAW("Kick.raw", 2, 44100, 16, true);
	sndloader->loadFileRAW("Clap.raw", 2, 44100, 16, true);
	sndloader->loadFileRAW("xylo1.raw", 2, 44100, 16, true);

	sampler_kick = new Sound::Sampler("kick");
	sampler_kick->loadWave("Kick.raw");
	sampler_kick->setMaxPolyphony(1);
	sampler_kick->setGain(0.5);

	sampler_clap = new Sound::Sampler("clap");
	sampler_clap->loadWave("Clap.raw");
	sampler_clap->setMaxPolyphony(1);
	sampler_clap->setGain(0.25);

    sampler_xylo = new Sound::Sampler("xylo");
	sampler_xylo->loadWave("xylo1.raw");
	sampler_xylo->setMaxPolyphony(1);
	sampler_xylo->setGain(0.5);

    Sound::Manager* sndman = Sound::Manager::getInstance();
    sndman->insert(this);

	srand(time(0));
}

TextureSynth::~TextureSynth()
{
    delete cellTexture;
//    delete sampler_kick;
//    delete sampler_clap;
//    delete sampler_xylo;
//    Sound::Manager* sndmanager = Sound::Manager::getInstance();
//    sndmanager->destroy(sampler_kick->getUniqueID());
//    sndmanager->destroy(sampler_clap->getUniqueID());
//    sndmanager->destroy(sampler_xylo->getUniqueID());
}

void TextureSynth::musica_gerar_notas()
{
    chordKeys = chordBank.getChordKeys(chordNames[chordNameProx]);
    for(int i=0; i<chordKeys.size(); i++)
    {
        oscSynth[i].setFrequency(chordKeys[i]);
    }
    osc_bass.setFrequency( chordKeys[0]/4 );
    chordNameProx = (chordNameProx+1)%chordNames.size();
}

void TextureSynth::musica_tocar()
{
	tocar_musica    = true;
	chordNameProx   = 1;
	musica_gerar_notas();
	cellOff         = 0;
	kick_timer      = 1;
    clap_timer      = 0.5;
    xylo_timer      = 1;
    bass_timer      = 0.25;
    chord_timer     = 0;
    rhythm_timer    = 0;
}
void TextureSynth::musica_parar()
{
	tocar_musica = false;
}
bool TextureSynth::musica_esta_tocando()
{
	return tocar_musica;
}

void TextureSynth::musica_mudar_tempo(double tempo)
{
    tempo_master = tempo;
}

void TextureSynth::gerador1()
{
    // Referências:
    // http://en.wikipedia.org/wiki/Elementary_cellular_automaton
    // http://mathworld.wolfram.com/ElementaryCellularAutomaton.html
    // http://natureofcode.com/book/chapter-7-cellular-automata/
    // http://gamedevelopment.tutsplus.com/tutorials/generate-random-cave-levels-using-cellular-automata--gamedev-9664

    std::fill(cellMapvec.begin(), cellMapvec.end(), 0);

    if(false) // Gerador aleatório
    {
        srand(time(0));
        float threshold = 0.5f;
        vector<float>::iterator curr = cellMapvec.begin();
        while(curr != cellMapvec.end())
        {
            *curr++ = ((float)rand()/RAND_MAX) > threshold ? 255 : 0;
        }
    }
    else
    {
        // Nota: Retroalimentando com linha anterior.
        std::copy(cellLinvec.begin(), cellLinvec.end(), cellMapvec.begin());
    }

    if(true) // Autômato celular
    {
        //bool estados[]{0,1,0,1,1,0,1,0}; // regra 90 - Triangulo de Sierpinski
        //bool estados[]{0,1,1,1,1,0,0,0}; // regra 30
        unsigned regra = 30;

        vector<float>::iterator gen0 = cellMapvec.begin();
        vector<float>::iterator gen1 = cellMapvec.begin()+cellMapw;

        for(int y=0; y<cellMaph-1; y++)
        {
            // Nota: primeira célula não é usavel.
            gen0+=1; gen1+=1;
            for(int x=1; x<cellMapw-1; x++)
            {
                // Nota: Concatenação de bits. Ao final, será gerado um número de 0 à 8.
                int keys = 0;
                for(int b=0; b<3; b++)
                {
                    keys |= (bool)gen0[-1+b] << b;
                }
                // Nota: Verifica a posição de bit "k" no número relacionado à regra
                // Exemplo: 90 = 0,1,0,1,1,0,1,0
                *gen1 = regra >> keys & 0x1 ? 1.0f : 0.0f;

                gen0+=1; gen1+=1;
            }
            // Nota: ultima célula não é usavel.
            gen0+=1; gen1+=1;
        }
    }
    // copia linha para ser reutilizada

    std::vector<float>::iterator cellMapLinBeg = cellMapvec.begin()+cellMapw;
    std::vector<float>::iterator cellMapLinEnd = cellMapLinBeg+cellMapw;
    std::copy(cellMapLinBeg, cellMapLinEnd, cellLinvec.begin());
}

void TextureSynth::gerador2()
{
    std::fill(cellMapvec.begin(), cellMapvec.end(), 0);

    Oscillator  osc;
    static double step = 1.0/44100;
    vector<float>::iterator v_curr = cellMapvec.begin();
    while(v_curr != cellMapvec.end())
    {
        osc.setFrequency(1000); // + 10 * lfo.getSine()
        *v_curr = 0.5 + 0.5 * osc.getPWM(0.2);  //*curr++ = (unsigned char)(127*(0.5+0.5*cellOsc.getSine()));
        *v_curr *= (float)rand()/RAND_MAX;  //*curr++ = (unsigned char)(127*(0.5+0.5*cellOsc.getSine()));
        osc.process(step);
        v_curr++;
    }
}

void TextureSynth::gerador3()
{
    std::fill(cellMapvec.begin(), cellMapvec.end(), 0);

    if(true) // Autômato celular
    {
        {
            unsigned len = cellMapw/8;
//            cellMapvec[len*2] = 1;
            cellMapvec[len*4] = 1;
//            cellMapvec[len*6] = 1;
        }

        unsigned regra = 75; // 75

        vector<float>::iterator gen0 = cellMapvec.begin();
        vector<float>::iterator gen1 = cellMapvec.begin()+cellMapw;

        for(int y=0; y<cellMaph-1; y++)
        {
            // Nota: primeira célula não é usavel.
            gen0+=1; gen1+=1;
            for(int x=1; x<cellMapw-1; x++)
            {
                // Nota: Concatenação de bits. Ao final, será gerado um número de 0 à 8.
                int keys = 0;
                for(int b=0; b<3; b++)
                {
                    keys |= (bool)gen0[-1+b] << b;
                }
                // Nota: Verifica a posição de bit "k" no número relacionado à regra
                // Exemplo: 90 = 0,1,0,1,1,0,1,0
                *gen1 = regra >> keys & 0x1 ? 1.0f : 0.0f;

                gen0+=1; gen1+=1;
            }
            // Nota: ultima célula não é usavel.
            gen0+=1; gen1+=1;
        }
    }

    if(true)
    {
        Oscillator osc;
        static double step = 1.0/44100;
        vector<float>::iterator v_curr = cellMapvec.begin();
        srand(time(0));
        while(v_curr != cellMapvec.end())
        {
            osc.setFrequency(1000); // + 10 * lfo.getSine()
            *v_curr *= 0.5 + 0.5 * osc.getPWM(0.5);  //*curr++ = (unsigned char)(127*(0.5+0.5*cellOsc.getSine()));
            //*v_curr *= (float)rand()/RAND_MAX;  //*curr++ = (unsigned char)(127*(0.5+0.5*cellOsc.getSine()));
            osc.process(step);
            v_curr++;
        }
    }
}

void TextureSynth::mapa_atualizar()
{
    cellTexture->setBuffer(0, 0, 0, cellMapw, cellMaph, GL_RED, GL_FLOAT, cellMapvec.data());
}

void TextureSynth::mapa_limpar()
{
    std::fill(cellMapvec.begin(), cellMapvec.end(), 0);
    std::fill(cellLinvec.begin(), cellLinvec.end(), 0);
    cellLinvec[cellMapw/2] = 1;
    mapa_atualizar();
}

void TextureSynth::mapa_gerar()
{
    gerador3();
    mapa_atualizar();
}

void TextureSynth::mapa_mostrar()
{
    mostrar_mapa = true;
}

void TextureSynth::mapa_esconder()
{
    mostrar_mapa = false;
}

bool TextureSynth::mapa_esta_sendo_desenhado()
{
    return mostrar_mapa;
}

void TextureSynth::process(double deltaTime)
{
    if(!tocar_musica) return;

    double  step        = 1.0/44100;
    float*  dstPtr      = mOutput;
    float*  cellLin     = &cellMapvec[cellMapw * (unsigned)(cellOff/cellMapw)];
    float   sinal       = 0;

    //---------------------------------------------//

    unsigned lenOff = (cellMapw/2)-oscSynth.size();
    unsigned lenPerFreq = 10;//lenOff + (lenOff/oscs.size());

    for(int i=0; i<chordKeys.size(); i++)
    {
        Oscillator& osc = oscSynth[i];
        sinal += osc.getSaw() * cellLin[lenOff + (lenPerFreq * i)];
        osc.process(step);
    }
    sinal /= oscSynth.size();
//    *dstPtr++ = sinal;

    //---------------------------------------------//
//
//    resampler.process(cellOff);
//    sinal = resampler.getOutput()[0] - 0.5 * 2;
//    *dstPtr++ = sinal;

    //---------------------------------------------//

//    qpsk_signal.setPhase(qpsk_lfo.getSine());
//    *dstPtr++ = (qpsk_signal.getSine() * qpsk_switch.getSquare()) - qpsk_carrier.getSine();
//    *dstPtr++ = (qpsk_signal.getSine()) - qpsk_carrier.getSine();
//    qpsk_signal.process(step);
//    qpsk_switch.process(step);
//    qpsk_carrier.process(step);
//    qpsk_lfo.process(step);

    //---------------------------------------------//

    double step2 = step * tempo_master;

//    rhythm_timer += step2;
//    if(rhythm_timer > 32)
//    {
//        tempo_master += 0.1;
//        cellOff = 0;
//        rhythm_timer = 0;
//    }

    // Parte amostrada

    kick_timer += step2;
    if(kick_timer > 0.5)
    {
        //sampler_kick->setGain(0.5);
        sampler_kick->play();
        kick_timer = 0;
    }

    clap_timer += step2;
    if(clap_timer > 1.0)
    {
        sampler_clap->setGain(0.5);
        sampler_clap->play();
        clap_timer = 0;
    }

    xylo_timer += step2;
    if(xylo_timer > 0.25)
    {
       //sampler_xylo->setGain(0.75);
       //sampler_xylo->setVelocity((chordKeys[rand()%chordKeys.size()]/523.251) * 2);
        sampler_xylo->setVelocity((chordKeys[rand()%chordKeys.size()]/523.251) * 2);
        sampler_xylo->play();
        xylo_timer = 0;
    }

    // Parte sintetizada

    bass_timer += step2;
    if(bass_timer > 0.5)
    {
        bass_timer = 0;
    }

    chord_timer += step2;
    if(chord_timer > 4){
        musica_gerar_notas();
        chord_timer = 0;
    }

    // Nota de malandragem: usando o tempo do baixo como controle de envelope!
    sinal += osc_bass.getSine() * (1.0-bass_timer*2);
    osc_bass.process(step);

    // Nota: sinal está saturando demais!
    sinal       *= 0.25;
    *dstPtr++   = sinal;
    *dstPtr++   = sinal;

    cellOff = fmod(cellOff + step2 * cellMapw * 4, cellMapl);
}

void TextureSynth::pintar_pixel(int x, int y)
{
    if(!mostrar_mapa) return;

    if(x >= 0 && x < cellMapw && y >= 0 && y < cellMaph && !cellMapvec.empty())
    {
        float& cell = (float&)cellMapvec[cellMapw*y+x];
        cell = 1;
        mapa_atualizar();
    }
}

void TextureSynth::render(Graphics* g)
{
    // Nota: somente rascunho para estudos...
    /*
        attachFramebuffer(fbuf1);
        attachTexture(texSrc, GL_TEXTURE0);
        attachTexture(texDst, GL_TEXTURE1);
        attachProgram(blendProg);

        drawRect(0,0,512,512);

        detachTexture(GL_TEXTURE0);
        detachTexture(GL_TEXTURE1);
        detachProgram();
        detachFramebuffer();
    */

    if(!mostrar_mapa) return;

    cellTexture->setMagFilter(GL_NEAREST);
    g->drawTexture(cellTexture,0,0,cellMapw,cellMaph);

    float f1 = floor(cellOff)/cellMapw;
    float f2 = f1 * (512.0/cellMaph);
    float f3 = fmod(floor(cellOff), cellMapw);

    //g->drawTexture(cellTexture, 600.0, 522.0, 512, 50, 0, f1, cellMapw, 0);
    //g->drawTexture(cellTexture, 1122.0, 522.0, 50, 50, f3, f1, 0, 0);
    //g->drawTexture(cellTexture, 600.0, f2, 512.0, 512.0-f2, 0.0, f1, cellMapw, cellMaph-f1);

    g->drawTexture(cellTexture, 600.0, 522.0, 512, 50, 0, f1, cellMapw, 0);
    g->drawTexture(cellTexture, 600.0, f2, 512.0, 512.0-f2, 0.0, f1, cellMapw, cellMaph-f1);
}
