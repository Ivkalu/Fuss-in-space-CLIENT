#include "Sprite.h"
#include "Defines.h"


Sprite::Sprite(const char* c, SDL_Rect* src, SDL_Rect* dst)
	: srcR(src)
	, dstR(dst)
{
	tex = TextureManager::LoadTexture(c);
};

void Sprite::render()
{
	TextureManager::Draw(tex, srcR, dstR);
}