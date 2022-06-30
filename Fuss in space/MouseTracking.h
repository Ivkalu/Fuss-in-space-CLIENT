#pragma once
#include "Client.h"
#include <cstdint>
#include <vector>

class MouseTracking
{

private:

	int w, h, brushSize, xMin, yMin;
	int xMax = 0, yMax = 0;
	std::vector<std::pair<int, int>> pointsDrew;

	void drawPoint(int x, int y);
	void reset();

public:

	~MouseTracking() {};

	void init(int _w, int _h, int _brushSize = 1);
	void drawLine(int x, int y, int xProsli, int yProsli);
	void handleEvents();
	void capture();

};