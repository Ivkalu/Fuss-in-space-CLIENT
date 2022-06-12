#include "GameContainer.h"
#include "InputHandler.h"

GameContainer::GameContainer()
	:Container("assets/Background.png", nullptr, nullptr)
{

}

void GameContainer::handleEvents()
{
	Container::handleEvents();
}

//GameContainer je sam po sebi sintakticki suvisan jer na osnovni Container pridodaje samo jednu funkciju:
//inputHandler->send() unutar update() funkcije.
//To bi se rjesilo dodavajuci u konstruktor Sprite() opciju da se spremi funkcija za handleEvents(), update() i clear() koja ce se pozvati pri svakom pozivu.
void GameContainer::update()
{
	Container::update();
	inputHandler->send();
}

void GameContainer::clear()
{
	Container::sprites.clear();
}