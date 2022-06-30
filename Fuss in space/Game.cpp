#pragma once
#include "Defines.h"
#include "Game.h"
#include "TextureManager.h"
#include "Button.h"
#include "Container.h"
#include "FontManager.h"
#include "TextBox.h"
#include "spriteOrganizer.h"
#include "InputHandler.h"

SDL_Renderer* Game::renderer = nullptr;
Client Game::client;
SDL_Event Game::event;


void Game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cprintf("Subsystems Initialised!\n");

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, NULL, NULL, SDL_WINDOW_MAXIMIZED);
		if (window)
		{
			cprintf("Window created!\n");
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			cprintf("Renderer created!\n")
		}

		int display_index = SDL_GetWindowDisplayIndex(window);
		if (display_index >= 0 && SDL_GetDisplayUsableBounds(display_index, &screen_size) == 0)
		{
			SDL_SetWindowSize(window, screen_size.w, screen_size.h);
			cprintf("Captured window display (%d, %d)!\n", screen_size.w, screen_size.h);
		}
		
		spriteOrganizer = new SpriteOrganizer();
		//client.init();
		mouseTracking.init(screen_size.w, screen_size.h, 11);
		FontManager::init();

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
}




void Game::handleEvents()
{
	
	while (SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT)
		{
			isRunning = false;
		}

		inputHandler->handleEvents();
		spriteOrganizer->handleEvents();
		//prebaciti u gameContainer
		mouseTracking.handleEvents();
		
	}
}

void Game::update()
{

	spriteOrganizer->update();
	client.update();
	
}

void Game::render()
{

	SDL_RenderClear(renderer);
	spriteOrganizer->render();
	SDL_RenderPresent(renderer);

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cprintf("Game Cleaned!\n");
}

