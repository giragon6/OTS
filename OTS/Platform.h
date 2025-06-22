#pragma once

#include <Windows.h>
#include <iostream>
#include "Pixel.h"

class Platform
{
private:
	RECT desktopRect;
	HWND desktopWindow;
	HDC desktopDC;
	HDC desktopCaptureDC;
	HBITMAP desktopCaptureBitmap;
	BITMAPINFO bmi;
public:
	Platform();
	~Platform() = default;
	int getWidth();
	int getHeight();
	void getDesktopResolution(int& width, int& height);
	uint32_t getDesktopPixelAt(int x, int y);
	void getConsoleResolution(int& width, int& height);
	void clearConsole();
	void getDesktopPixels(uint32_t pixels[]);
};

