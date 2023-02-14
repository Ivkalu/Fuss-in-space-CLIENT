#pragma once
#include "Container.h"

class GameContainer : public Container
{
public:

	GameContainer();

	void update() override;
	void handleEvents() override;
	
	void clear();
};