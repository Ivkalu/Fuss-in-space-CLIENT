#include "InputHandler.h"
#include "SDL.h"
#include "Game.h"

void InputHandler::handleEvents()
{
	switch (Game::event.type) {
	case SDL_MOUSEMOTION:
		inputHandler->x = Game::event.motion.x;
		inputHandler->y = Game::event.motion.y;
		break;
	case SDL_KEYDOWN:
		setKey(true);
		break;
	case SDL_KEYUP:
		setKey(false);
		break;
	}
}

void InputHandler::setKey(bool b)
{
	switch (Game::event.key.keysym.sym)
	{
	case SDLK_w:
		if(b)
			jump = true;
		w = b;
		break;
	case SDLK_a:
		a = b;
		break;
	case SDLK_s:
		s = b;
		break;
	case SDLK_d:
		d = b;
		break;
	case SDLK_CAPSLOCK:
		if (b)
			CAPS_LOCK = !CAPS_LOCK;
		break;
	case SDLK_RSHIFT:
		SHIFT = b;
		break;
	case SDLK_LSHIFT:
		SHIFT = b;
		break;
	case SDLK_LCTRL:
		CTRL = b;
		break;
	default:
		break;
	}
}



void InputHandler::send()
{
	
	uint8_t sendbuf[100] = { S_PLAYER_INPUT , };
	Message<InputHandler> d;
	d.data = *this;
	memcpy(sendbuf + 1, d.data_ptr, 12);
	client.sendMessege((const char*)sendbuf, 13);
	jump = false;

}

InputHandler* inputHandler = new InputHandler();