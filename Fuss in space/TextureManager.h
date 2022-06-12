#pragma once

#include "Game.h"

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, const SDL_Rect* srcrect, const SDL_Rect* dstrect);
};