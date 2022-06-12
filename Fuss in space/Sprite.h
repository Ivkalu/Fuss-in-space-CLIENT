#pragma once
#include "SDL.h"
#include "TextureManager.h"

class Sprite 
{
protected:

	SDL_Texture* tex;
	SDL_Rect* srcR;
	SDL_Rect* dstR;

public:

	Sprite(const char *c, SDL_Rect* src, SDL_Rect* dst);
	
	virtual ~Sprite();
	virtual void handleEvents(){}
	virtual void update(){}
	virtual void render();
	virtual void init()
	{
		active = true;
	}
	bool isActive()
	{
		return active;
	}
	virtual void kill()
	{
		active = false;
	}
	
	bool active = true;
};