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

#define MOUSE_CAPTURE_MATRIX_SIZE 40

using std::experimental::filesystem::directory_iterator;
using std::set;
using std::string;
using std::to_string;


void MouseTracking::init(int _w, int _h, int _brushSize) 
{
	
	brushSize = _brushSize;
	xMin = w = _w + brushSize;
	yMin = h = _h + brushSize;

	cprintf("Mouse tracker initialised!\n");

}


void MouseTracking::reset() 
{

	pointsDrew.clear();
	xMax = yMax = 0;
	xMin = w;
	yMin = h;

}

void MouseTracking::capture() 
{
	size_t img_size = MOUSE_CAPTURE_MATRIX_SIZE * MOUSE_CAPTURE_MATRIX_SIZE;
	unsigned char* img = new unsigned char[img_size];
	
	for (int i = 0; i < img_size; i++) {
		img[i] = 255;
	}
	brushSize = 1;
	auto drawPoint = [&](int x, int y) mutable
	{
		for (int i = x; i < x + brushSize; i++) {
			for (int j = y; j < y + brushSize; j++) {
				if (i >= 0 && i < MOUSE_CAPTURE_MATRIX_SIZE && j >= 0 && j < MOUSE_CAPTURE_MATRIX_SIZE) {
					img[i + j * MOUSE_CAPTURE_MATRIX_SIZE] = 0;
				}
			}
		}
	};

	auto drawLine = [this, &drawPoint](int x, int y, int xProsli, int yProsli)
	{
		double length = max(1.0, sqrt(pow(x - xProsli, 2) + pow(y - yProsli, 2)));

		for (double i = 0; i <= length; i += 1) {
			drawPoint((int)(x + (xProsli - x) / length * i), (int)(y + (yProsli - y) / length * i));
		}
	};
	
	uint16_t width = xMax - xMin + 1;
	uint16_t height = yMax - yMin + 1;
	
	for (std::vector<std::pair<int, int>>::iterator it = pointsDrew.begin(); it != pointsDrew.end(); it++) {
		it->first = (int)(((float)(it->first - xMin)) / width * MOUSE_CAPTURE_MATRIX_SIZE);
		it->second = (int)(((float)(it->second - yMin)) / height * MOUSE_CAPTURE_MATRIX_SIZE);
	}
	for (std::vector<std::pair<int, int>>::iterator it = pointsDrew.begin() + 1; it != pointsDrew.end(); it++) {
		drawLine(it->first, it->second, (it - 1)->first, (it - 1)->second);
	}

#ifdef EXPORT_TO_PNG

	//capturing only the smallest rectangle containing mouse movement
	string path = PATH;
	path.append("\\");
	path.append(SET);
	path.append("\\");
	set<string> directory;
	for (const auto& file : directory_iterator(path))
	{
		directory.insert(file.path().filename().string());
	}
	int i = 0;
	for (; directory.count(to_string(i) + ".png") != 0; i++) {}

	path += to_string(i) + ".png";

	if (!stbi_write_png(path.c_str(), MOUSE_CAPTURE_MATRIX_SIZE, MOUSE_CAPTURE_MATRIX_SIZE, 1, img, MOUSE_CAPTURE_MATRIX_SIZE)) {
		eprintf("Problem with writing image!\n");
		exit(1);
	}
	stbi_image_free(img);
#endif


#ifndef BLOCK_BACKEND

	//sending to the backend
	uint8_t code[1] = { (uint8_t)S::S_SCREENSHOT_TAKEN };
	uint8_t W[2] = { (uint8_t)((MOUSE_CAPTURE_MATRIX_SIZE >> 8) & 0xFF), (uint8_t)(MOUSE_CAPTURE_MATRIX_SIZE & 0xFF) };
	uint8_t H[2] = { (uint8_t)((MOUSE_CAPTURE_MATRIX_SIZE >> 8) & 0xFF), (uint8_t)(MOUSE_CAPTURE_MATRIX_SIZE & 0xFF) };

	uint8_t* _sendbuf = new uint8_t[img_size + 5];
	if (_sendbuf == NULL)
	{
		exit(1);
	}
	memcpy(_sendbuf, code, 1);
	memcpy(_sendbuf + 1, W, 2);
	memcpy(_sendbuf + 3, H, 2);
	memcpy(_sendbuf + 5, (uint8_t*)img, img_size);

	const char* sendbuf = (const char*)_sendbuf;
	if (pointsDrew.size() > 10) {
		Game::client.sendMessege(sendbuf, (int)img_size + 5);
	}
	
	delete[] _sendbuf;
#endif

	delete[] img;
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
		xMin = inputHandler->x > xMin ? xMin : inputHandler->x;
		yMin = inputHandler->y > yMin ? yMin : inputHandler->y;
		xMax = inputHandler->x < xMax ? xMax : inputHandler->x;
		yMax = inputHandler->y < yMax ? yMax : inputHandler->y;
		pointsDrew.push_back(std::make_pair(inputHandler->x, inputHandler->y));

		//drawLine(inputHandler->x, inputHandler->y, xPrevious, yPrevious);
	}

	xPrevious = inputHandler->x;
	yPrevious = inputHandler->y;
}