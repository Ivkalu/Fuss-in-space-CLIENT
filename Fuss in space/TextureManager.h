#pragma once

#include "Game.h"

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, const SDL_Rect* srcrect, const SDL_Rect* dstrect);
<<<<<<< HEAD
	static void DestroyTextures();
};
=======
};	
>>>>>>> 5261913f04597a8da383b27696458fed177b202a
