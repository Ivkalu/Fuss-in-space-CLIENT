#include "TextureManager.h"
#include "map"

std::map<const char*, SDL_Texture*> textures;

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{

	if (textures.count(texture) == 0) {
		SDL_Surface* tempSurface = IMG_Load(texture);
		SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		textures[texture] = tex;
		return tex;
	 }
	else {
		return textures[texture];
	}
	
}

void TextureManager::DestroyTextures() {
	for (auto it = textures.begin(); it != textures.end(); it++) {
		SDL_DestroyTexture(it->second);
	}
}


void TextureManager::Draw(SDL_Texture* tex, const SDL_Rect* src, const SDL_Rect* dst)
{
	if (tex != nullptr && dst != nullptr) {
		SDL_RenderCopy(Game::renderer, tex, src, convertRect(dst));
	}
	else if (tex != nullptr) {
		SDL_RenderCopy(Game::renderer, tex, src, nullptr);
	}
}

//napraviti da se tekstura ucita samo prvi put na spriteu, ovisno o adresi koja je poslana
