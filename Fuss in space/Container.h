#pragma once
#include "Sprite.h"
#include <array>
#include <map>
#include <set>
#include <memory>

class Container : public Sprite 
{
protected:

	std::vector<std::unique_ptr<Sprite>> sprites;

public:

	Container(const char* c, SDL_Rect* src, SDL_Rect* dst, bool startActive = false);

	void handleEvents() override;
	void update() override;
	void render() override;
	void kill() override;
	void init() override;
	std::vector<Sprite*> getActiveSprites(bool x = false);
	
	void addSprite(Sprite *s) 
	{
		sprites.push_back(std::unique_ptr<Sprite> {s});
	}
	
	template<typename T, typename... Args >
	T* addSprite(Args&&... args)
	{
		T* s = new T(std::forward<Args>(args)...);
		sprites.push_back(std::unique_ptr<Sprite> {s});
		return s;
	}
};