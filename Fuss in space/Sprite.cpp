#include "Sprite.h"
#include "Defines.h"


Sprite::Sprite(const char* c, SDL_Rect* src, SDL_Rect* dst)
	: srcR(src == nullptr ? nullptr : new SDL_Rect(*src))
	, dstR(dst == nullptr ? nullptr : new SDL_Rect{ convertWidth(dst->x), convertHeight(dst->y), convertWidth(dst->w), convertHeight(dst->h) })
{
	tex = TextureManager::LoadTexture(c);
};

Sprite::~Sprite()
{
	//SDL_DestroyTexture(tex);
}

void Sprite::render()
{
	TextureManager::Draw(tex, srcR, dstR);
}