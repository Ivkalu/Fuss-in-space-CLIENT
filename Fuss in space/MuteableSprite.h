#pragma once
#include "SDL.h"
#include "TextureManager.h"
#include "Sprite.h"

class MuteableSprite : public Sprite
{
	struct {
		void (*updateFunc)() = nullptr;
		void (*renderFunc)() = nullptr;
		void (*handleEventsFunc)() = nullptr;
	}funcs;

public:

	MuteableSprite(const char* c, SDL_Rect* src, SDL_Rect* dst) : Sprite(c, src, dst){}

	MuteableSprite(const char* c, SDL_Rect* src, SDL_Rect* dst, std::vector < std::pair<void (Sprite::*)(), void (*)() >> funcVec) : Sprite(c, src, dst) {
		for (auto func : funcVec) {
			addFunc(func.first, func.second);
		}
	}

	//copy constructor and copy assignemnt are disabled since they make no sense in this context

	void handleEvents() {
		handleEvents();
		if (funcs.handleEventsFunc != nullptr)funcs.handleEventsFunc();
	}
	void update() {
		update();
		if (funcs.updateFunc != nullptr)funcs.updateFunc();
	}
	void render() {
		render();
		if (funcs.renderFunc != nullptr)funcs.renderFunc();
	}
	
	void addFunc(void (Sprite::* method)(), void (*func)()) { //void (*func)()
		if (method == &Sprite::update) {
			funcs.updateFunc = func;
		}
		else if (method == &Sprite::handleEvents) {
			funcs.handleEventsFunc = func;
		}
		else if (method == &Sprite::render) {
			funcs.renderFunc = func;
		}
		//Example of usage
		//MuteableSprite m("", nullptr, nullptr, { {Sprite::update, []() {printf("doSth"); }}});
		
	}

};