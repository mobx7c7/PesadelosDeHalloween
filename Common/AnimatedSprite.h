/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-19
***********************************************************************/
#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"
#include <memory>

class AnimatedSprite : public Sprite
{
	public:

		bool                    loopable = true;
		bool                    running = true;
		int                     frameCount = 0;
		int                     frameStart = 0;
		int                     frameEnd = 0;
		double                  frameProgress = 0;
		double                  interval = 0;
		double                  velocity = 0;

	public:

		AnimatedSprite(Texture* texture, unsigned imgw, unsigned imgh, unsigned tilew, unsigned tileh, double interval);
		AnimatedSprite(Texture* texture, unsigned tilew, unsigned tileh, double interval);
		~AnimatedSprite();

//		void setState(unsigned state);

        bool isRunning();

		void start();
		void pause();
		void stop();
		void reset();
		void setInterval(double interval);
		void setLoopable(bool loopable);
		void setFrameCurrent(int value);
		void setFrameStart(int frameStart);
		void setFrameEnd(int frameEnd);
		void setVelocity(double value);
		void process(double deltaTime);
		void render(Graphics* g);
};

typedef shared_ptr<AnimatedSprite> AnimatedSpritePtr;

#endif // ANIMATEDSPRITE_H
