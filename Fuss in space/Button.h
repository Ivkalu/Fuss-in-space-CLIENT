#pragma once
#include "Sprite.h"
#include "Game.h"
#include "Defines.h"

static float multip = (float)0.1;


class Button : public Sprite 
{

public:

	Button(const char* c, SDL_Rect* _srcrect, SDL_Rect *_dstrect, void (*func)())
		:Sprite(c, _srcrect, _dstrect),
		func(func)
	{
		h_dstR = new SDL_Rect{
			dstR->x - int(dstR->w * multip),
			dstR->y - int(dstR->h * multip),
			int(dstR->w * (1 + multip * 2)),
			int(dstR->h * (1 + multip * 2))
		};
	
	}

	void handleEvents() override;
	void render() override;
	void kill() override {
		hovering = false;
	}

private:

	void (*func)();
	const SDL_Rect* h_dstR;
	bool hovering = false;
	bool isHovering(int x, int y);

protected:
	bool pressed = false;

};