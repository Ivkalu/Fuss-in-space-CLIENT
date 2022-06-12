#pragma once
#include "FontManager.h"


SDL_Texture* FontManager::tex;
SDL_Rect FontManager::table[255];


int FontManager::Draw(const char c, int x, int y, int fontSize)
{
    
	if (hasKey(c)) {
		
		SDL_Rect dstRect{ x, y, table[c].w* fontSize, table[c].h* fontSize };
		TextureManager::Draw(tex, table+c, &dstRect);
		
		return table[c].w* fontSize;
	}
	else {
		cprintf("Character '%c' not found! (%x)\n", c, c);
		return 0;
	}
}

int FontManager::Draw(const char* c, int length, int x, int y, int fontSize)
{
	int xStart = x;
	for (size_t i = 0; i < length; i++) {
		x+=Draw(*(c++), x,y,fontSize);
	}
	return x - xStart;
}