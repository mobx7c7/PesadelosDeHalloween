/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-19
***********************************************************************/
#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(Texture* texture, unsigned imgw, unsigned imgh, unsigned tilew, unsigned tileh, double interval) :
    Sprite(texture, imgw, imgh, tilew, tileh),
	frameCount(tilew*tileh)
{
    Drawable::setName("AnimatedSprite");

//    setState(0);
    setFrameStart(0);
    setFrameEnd(frameCount);
    setFrameCurrent(frameStart);
    setVelocity(1.0);
    setInterval(interval);

//	this->frameStart    = 0;
//	this->frameEnd      = frameCount;
//	this->frameProgress = frameStart;
//	this->velocity      = 1.0;
//	this->interval      = interval;
}

AnimatedSprite::AnimatedSprite(Texture* texture, unsigned tilew, unsigned tileh, double interval) :
    AnimatedSprite(texture, texture->getWidth(), texture->getHeight(), tilew, tileh, interval){}

AnimatedSprite::~AnimatedSprite(){}

//void AnimatedSprite::setState(unsigned state)
//{
//	AnimatedSpriteStateIterator animState = animStateMap.find(state);
//	if(animState == animStateMap.end())
//	{
//		animStateMap.insert( AnimatedSpriteStatePair(state, AnimatedSpriteState()) );
//	}
////	currentState    = state;
////	currentStatePtr = &animState->second;
//
////	frameStart = animState->second.frameStart;
////	frameEnd = animState->second.frameEnd;
////	frameProgress = animState->second.frameProgress;
//}

bool AnimatedSprite::isRunning()
{
    return running;
}

void AnimatedSprite::start()
{
	running = true;
}

void AnimatedSprite::pause()
{
	running = !running;
}

void AnimatedSprite::reset()
{
    frameProgress = frameStart;
}

void AnimatedSprite::stop()
{
	running = false;
}

void AnimatedSprite::setInterval(double interval)
{
	this->interval = max(interval, 0.0);
}

void AnimatedSprite::setLoopable(bool loopable)
{
	this->loopable = loopable;
}

void AnimatedSprite::setFrameCurrent(int value)
{
    //frameProgress = min(max(value, frameStart), frameEnd);
    frameProgress = value;
}

void AnimatedSprite::setFrameStart(int frameStart)
{
    //this->frameStart = min(max(frameStart, 0u), frameEnd-1);
    this->frameStart = frameStart;
}

void AnimatedSprite::setFrameEnd(int frameEnd)
{
    //this->frameEnd = min(max(frameEnd+1, frameStart+1), frameCount);
    this->frameEnd = frameEnd;
}

void AnimatedSprite::setVelocity(double value)
{
    velocity = value;
}

void AnimatedSprite::process(double deltaTime)
{
    if(running)
    {
        if(frameStart == frameEnd)
        {
            frameProgress = frameStart;
        }
        else
        {
            frameProgress += velocity * interval * deltaTime;

            if(loopable)
            {
                frameProgress -= (frameEnd-frameStart) * floor(frameProgress/frameEnd);

                if(frameProgress < frameStart){
                    frameProgress = frameStart;
                }else if(frameProgress > frameEnd){
                    frameProgress = frameEnd;
                }
                //frameProgress = min(max(frameProgress, (double)frameStart), (double)frameEnd);
            }
            else if(frameProgress > frameEnd)
            {
                stop();
                reset();
            }
        }

        tilex = (int)frameProgress%tilew;
        tiley = (int)frameProgress/tileh;
    }
}

void AnimatedSprite::render(Graphics* g)
{
    Transform2& t = getTransform();
    g->drawTexture(texture,
                   t.posx,
                   t.posy,
                   t.width,
                   t.height,
                   sprw * tilex,
                   sprh * tiley,
                   sprw,
                   sprh);
}
