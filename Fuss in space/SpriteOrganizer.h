#pragma once
#include "Container.h"
#include "TextBox.h"
#include "GameContainer.h"


class SpriteOrganizer : public Container
{
public:

	SpriteOrganizer();

	//void kill() override;

	Container* waitingMenuC;
	GameContainer* gameMenuC;
	static Container* mainMenuC;
	TextBox* Playr1TextBox;
	TextBox* Playr2TextBox;
	TextBox* Playr3TextBox;
	TextBox* Playr4TextBox;
};

extern SpriteOrganizer* spriteOrganizer;