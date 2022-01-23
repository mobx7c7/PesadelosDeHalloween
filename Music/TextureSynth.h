/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-05-30
***********************************************************************/
#ifndef TEXTURESYNTH_H
#define TEXTURESYNTH_H

#include <Common\Sound\Module.h>
#include <Common\Sound\Resampler.h>
#include <Common\Sound\Sampler.h>
#include <Common\Sound\Loader.h>
#include <Common\Sound\Manager.h>
#include <App\Graphics.h>
#include <GL\Framebuffer.h>
#include <GL\RenderBuffer.h>
#include <Oscillator.h>
#include <ChordBank.h>

//TextureScore::TextureScore() // partitura
//TextureMusic::TextureMusic() // ritmos com outras partituras

//cada estilo de musica possui uma lista de acordes
//uma geração para acorde
//uma geração para notas

class TextureSynth : public Sound::Module
{
	protected:

        vector<string>      chordNames;
        unsigned            chordNameProx;
        vector<float>       chordKeys;
	    vector<Oscillator>  oscSynth;
	    vector<int>         oscColuna;
	    void                musica_gerar_notas();

		Sound::Resample2    resampler;
		Sound::Sampler*     sampler_kick;
		double              kick_timer      = 1;
		Sound::Sampler*     sampler_clap;
		double              clap_timer      = 0.5;
        Sound::Sampler*     sampler_xylo;
		double              xylo_timer      = 1;
		Oscillator          osc_bass        = Oscillator(60);
		double              bass_timer      = 0.25;
		ChordBank           chordBank;
		double              chord_timer     = 0;
		double              rhythm_timer    = 0;
		double              tempo_master    = 1;
		bool                tocar_musica    = false;

        Oscillator          qpsk_lfo        = Oscillator(1);
		Oscillator          qpsk_switch     = Oscillator(1);
		Oscillator          qpsk_carrier    = Oscillator(4000);
		Oscillator          qpsk_signal     = Oscillator(4000);

    public:

        void                musica_tocar();
        void                musica_parar();
        bool                musica_esta_tocando();
        void                musica_mudar_tempo(double);

    protected:

		vector<float>       cellMapvec;
		vector<float>       cellLinvec;
		Texture*            cellTexture;
		unsigned            cellMapw;
		unsigned            cellMaph;
		unsigned            cellMapl;
		unsigned            cellByteSize;
		double              cellOff = 0;
		bool                mostrar_mapa = false;

		void                gerador1();
		void                gerador2();
		void                gerador3();

    public:

        void                mapa_limpar();
		void                mapa_gerar();
		void                mapa_mostrar();
		void                mapa_esconder();
		void                mapa_atualizar();
		bool                mapa_esta_sendo_desenhado();
		void                pintar_pixel(int x, int y);

	public:

		TextureSynth();
		virtual ~TextureSynth();

		void process(const double deltaTime);
		void render(Graphics* g);
};

#endif // TEXTURESYNTH_H
