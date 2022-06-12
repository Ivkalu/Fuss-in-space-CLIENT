#pragma once
#include "Client.h"
#include <cstdint>

class MouseTracking
{

private:

	int w, h, brushSize, xMin, yMin;
	uint8_t* mouseMovementMatrix;
	int xMax = 0, yMax = 0;

	void drawPoint(int x, int y);
	void reset();

public:

	~MouseTracking() {};

	void init(int _w, int _h, int _brushSize);
	void drawLine(int x, int y, int xProsli, int yProsli);
	void handleEvents();
	void capture();

};