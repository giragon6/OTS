#include <Windows.h>
#include <iostream>
#include "Screen.h"

Screen::Screen(Platform platform) : platform(platform) {
	this->platform.getDesktopResolution(width, height);
}

int Screen::getWidth() const {
	return width;
}

int Screen::getHeight() const {
	return height;
}

uint32_t Screen::getPixelAtScreenPosition(const int x, const int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height) {
		std::cerr << "Error: Coordinates (" << x << ", " << y << ") are out of bounds for screen resolution (" << width << ", " << height << ")." << std::endl;
		return 0;
	}
	return platform.getDesktopPixelAt(x, y);
}