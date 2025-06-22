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

void Screen::getScreenPixels(uint32_t pixelBuf[]) {
	if (pixelBuf == nullptr) {
		std::cerr << "Error: pixelBuf is null." << std::endl;
		return;
	}
	platform.getDesktopPixels(pixelBuf);
}

// TODO: make this return an int holy memory inefficiency
Pixel Screen::getPixelAtScreenPosition(const int x, const int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height) {
		std::cerr << "Error: Coordinates (" << x << ", " << y << ") are out of bounds for screen resolution (" << width << ", " << height << ")." << std::endl;
		return { 0, 0, 0, 0, 0 };
	}
	return platform.getDesktopPixelAt(x, y);
}