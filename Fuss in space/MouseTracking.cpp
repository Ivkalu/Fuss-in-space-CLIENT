#pragma once
#include "MouseTracking.h"
#include "Defines.h"
#include "Client.h"
#include <string>
#include <set>
#include "Game.h"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image/stb_image_resize.h"



using std::experimental::filesystem::directory_iterator;
using std::set;
using std::string;
using std::to_string;


void MouseTracking::init(int _w, int _h, int _brushSize = 1) 
{
	
	brushSize = _brushSize;
	xMin = w = _w + brushSize;
	yMin = h = _h + brushSize;

	size_t img_size = w * h;
	mouseMovementMatrix = (uint8_t*)malloc(img_size * sizeof(uint8_t));
	
	if (mouseMovementMatrix == NULL) {
		eprintf("Couldn't create matrix!\n");
	}
	
	for (int i = 0; i < img_size; i++) {
		mouseMovementMatrix[i] = (uint8_t)255;
	}

	cprintf("Mouse tracker initialised!\n");

}


void MouseTracking::reset() 
{

	for (int i = xMin; i <= xMax; i++) {
		for (int j = yMin; j <= yMax; j++) {
			if (i >= 0 && i < w && j >= 0 && j < h) {
				mouseMovementMatrix[i + j * w] = 255;
			}
		}
	}
	xMax = yMax = 0;
	xMin = w;
	yMin = h;

}


void MouseTracking::drawLine(int x, int y, int xProsli, int yProsli)
{

	double length = max(1.0, sqrt(pow(x - xProsli, 2) + pow(y - yProsli, 2)));

	for (double i = 0; i <= length; i += 1) {
		drawPoint((int)(x + (xProsli - x) / length * i), (int)(y + (yProsli - y) / length * i));
	}

}


void MouseTracking::drawPoint(int x, int y)
{

	for (int i = x; i < x + brushSize; i++) {
		for (int j = y; j < y + brushSize; j++) {
			if (i >= 0 && i < w && j >= 0 && j < h) {
				xMin = i > xMin ? xMin : i;
				yMin = j > yMin ? yMin : j;
				xMax = i < xMax ? xMax : i;
				yMax = j < yMax ? yMax : j;
				mouseMovementMatrix[i + j * w] = (uint8_t)0;
			}
		}
	}

}


void MouseTracking::capture() 
{

	uint16_t width = xMax - xMin + 1;
	uint16_t height = yMax - yMin + 1;
	size_t img_size = width * height;

	unsigned char* img = (unsigned char*)malloc(img_size);

	if (img == NULL) {
		eprintf("Unable to allocate memory for the image!\n");
		exit(1);
	}

	for (int i = xMin; i <= xMax; i++) {
		for (int j = yMin; j <= yMax; j++) {
			img[i - xMin + width * (j - yMin)] = mouseMovementMatrix[i + j * w];
		}
	}

#ifdef EXPORT_TO_PNG

	//capturing only the smallest rectangle containing mouse movement
	string path = PATH "\\" SET "\\";
	set<string> directory;
	for (const auto& file : directory_iterator(path))
	{
		directory.insert(file.path().filename().string());
	}
	int i = 0;
	for (; directory.count(to_string(i) + ".png") != 0; i++) {}

	path += to_string(i) + ".png";

	if (!stbi_write_png(path.c_str(), width, height, 1, img, width)) {
		eprintf("Problem with writing image!\n");
		exit(1);
	}

#endif

#ifdef EXPORT_SCREENSHOT_TO_PNG

	//capturing whole screen
	string s1 = PATH "screenshots\\screenshot.png";
	stbi_write_png(s1.c_str(), w, h, 1, (unsigned char*)mouseMovementMatrix, w);

#endif

#ifndef BLOCK_BACKEND

	//sending to the backend
	uint8_t code[1] = { (uint8_t)S::S_SCREENSHOT_TAKEN };
	uint8_t W[2] = { (uint8_t)((width >> 8) & 0xFF), (uint8_t)(width & 0xFF) };
	uint8_t H[2] = { (uint8_t)((height >> 8) & 0xFF), (uint8_t)(height & 0xFF) };

	uint8_t* _sendbuf = (uint8_t*)malloc(img_size + 5);
	memcpy(_sendbuf, code, 1);
	memcpy(_sendbuf + 1, W, 2);
	memcpy(_sendbuf + 3, H, 2);
	memcpy(_sendbuf + 5, (uint8_t*)img, img_size);

	const char* sendbuf = (const char*)_sendbuf;
	Game::client.sendMessege(sendbuf, (int)img_size + 5);

#endif

	stbi_image_free(img);
	reset();

}

void MouseTracking::handleEvents()
{
	static bool pressed;
	static int xPrevious, yPrevious;
	static int pressedTime;
	static Uint32 pressedStart;
	switch (Game::event.type) {

	case SDL_MOUSEBUTTONDOWN:
		pressed = 1;
		pressedStart = SDL_GetTicks();
		xPrevious = inputHandler->x;
		yPrevious = inputHandler->y;
		break;
	case SDL_MOUSEBUTTONUP:
		pressed = 0;
		pressedTime = SDL_GetTicks() - pressedStart;
		if (pressedTime > 100)
		{
			capture();
		}
		break;
	default:
		break;
	}

	if (pressed) {
		drawLine(inputHandler->x, inputHandler->y, xPrevious, yPrevious);
	}
	xPrevious = inputHandler->x;
	yPrevious = inputHandler->y;
}