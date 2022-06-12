#include "Container.h"
#include <iostream>
#include <vector>
#include <algorithm>


Container::Container(const char* c, SDL_Rect* src, SDL_Rect* dst, bool startActive)
	:Sprite(c, src, dst)
{
	if (startActive == false) {
		kill();
	}
	
}

std::vector<Sprite*> Container::getActiveSprites(bool x)
{
	static std::vector<Sprite*> activeSprites;
	if (x) {
		activeSprites.clear();
		for (auto& c : sprites) {
			if (c->isActive()) {
				activeSprites.push_back(c.get());
			}
		}
	}
	return activeSprites;
}

void Container::handleEvents() {
	std::vector<Sprite*> activeSprites = getActiveSprites(true);
	Sprite::handleEvents();
	for (auto& c : activeSprites) {
		c->handleEvents();
	}
	
}

void Container::update() {
	
	std::vector<Sprite*> activeSprites = getActiveSprites(true);
	Sprite::update();
	for (auto& c : activeSprites) {
		c->update();
	}

}

void Container::render()
{
	std::vector<Sprite*> activeSprites = getActiveSprites(true);

	Sprite::render();
	for (auto& c : activeSprites) {
		c->render();
	}
	
}

void Container::kill()
{
	Sprite::kill();
	for (auto& c : sprites) {
		c->kill();
	}
}

void Container::init()
{
	Sprite::init();
	for (auto& c : sprites) {
		c->kill();
	}
}