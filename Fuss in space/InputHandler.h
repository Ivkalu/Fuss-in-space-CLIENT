#pragma once
#include <stdint.h>

class InputHandler
{
public:
	uint16_t x, y;
	bool SHIFT, CTRL, CAPS_LOCK;
	bool w, a, s, d;

	bool jump;

	void handleEvents();
	void send();
	void setKey(bool x);
};


extern InputHandler* inputHandler;