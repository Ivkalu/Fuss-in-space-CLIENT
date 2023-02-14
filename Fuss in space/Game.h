#pragma once
#include "SDL.h"
#include "Defines.h"
#include "Client.h"
#include "MouseTracking.h"
#include "SDL_image.h"
#include "InputHandler.h"


extern Client client;


class Game
{

private:

	bool isRunning = false;
	SDL_Window* window;
	
	MouseTracking mouseTracking;
	

public:

	~Game(){};

	void init();
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }

	static SDL_Renderer* renderer;
	
	static SDL_Event event;

};

