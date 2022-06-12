#include "Button.h"
#include "InputHandler.h"


void Button::handleEvents()
{
	hovering = isHovering(inputHandler->x, inputHandler->y);
	if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
		if (isHovering(Game::event.motion.x, Game::event.motion.y)) {
			pressed = true;
			if (func != nullptr) func();
		}
		else {
			pressed = false;
		}
	}
}



#define hovering(rect, x, y) ( x >= rect->x && y >= rect->y && x <= rect->x + rect->w && y <= rect->y + rect->h )

bool Button::isHovering(int x, int y)
{
	return hovering ? hovering(h_dstR, x, y) : hovering(dstR, x, y);
}

void Button::render()
{
	hovering ?
		TextureManager::Draw(tex, srcR, h_dstR) : TextureManager::Draw(tex, srcR, dstR);
}