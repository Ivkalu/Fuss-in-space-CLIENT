#pragma once
#include "Container.h"
#include "TextBox.h"
//#include "GameContainer.h"


class SpriteOrganizer : public Container
{
public:

	SpriteOrganizer();

	//void kill() override;

	Container* waitingMenuC;
	struct GameContainer : public Container {
		GameContainer() :Container("assets/Background.png", nullptr, nullptr){}

		void update() override {
			Container::update();
			inputHandler->send();
		};

		void clear() {
			Container::sprites.clear();
		};
	} *gameMenuC;
	static Container* mainMenuC;
	TextBox* Playr1TextBox;
	TextBox* Playr2TextBox;
	TextBox* Playr3TextBox;
	TextBox* Playr4TextBox;
};

extern SpriteOrganizer* spriteOrganizer;