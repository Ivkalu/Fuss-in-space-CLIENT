#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include "TextureManager.h"
#include "Defines.h"



class FontManager
{

	

public:
	static SDL_Texture* tex;
	static SDL_Rect table[255];

	static void init()
	{
		tex = TextureManager::LoadTexture("assets/Font/FontWithShadows.png");
		FILE* ptr = fopen("assets/Font/FontCalibres.txt", "r");
		if (ptr == NULL) {
			eprintf("Error reading font data!\n");
		}
		char c;
		int x = 0, w;
		while (fscanf(ptr, "%c %d\n", &c, &w) != EOF) {
			table[c].h = 8;
			table[c].x = x;
			x += w;
			table[c].w = w;
		}
		table[' '].h = 8;
		table[' '].x = x;
		table[' '].w = 3;
		
		//ucitaj iz txt datoteke sve potrebne razmake!
		
		cprintf("Fonts loaded!\n");
	}
	static int Draw(const char c, int x, int y, int fontSize);
	static int Draw(const char* c, int length, int x, int y, int fontSize);
	static bool hasKey(const int c) {
		if (c > 0 && c < 255 && table[c].h != 0) {
			return 1;
		}
		return 0;
	}
};

