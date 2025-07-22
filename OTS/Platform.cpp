#include <Windows.h>
#include <cwchar>
#include <iostream>
#include <vector>

#include "Pixel.h"
#include "Platform.h"

Platform::Platform() {
	desktopWindow = GetDesktopWindow();
	if (!desktopWindow) {
		std::cerr << "Failed to get desktop window." << std::endl;
		return;
	}
	GetWindowRect(desktopWindow, &desktopRect);
	if (desktopRect.left == 0 && desktopRect.top == 0 && desktopRect.right == 0 && desktopRect.bottom == 0) {
		std::cerr << "Failed to get desktop rectangle." << std::endl;
		return;
	}
	desktopDC = GetDC(desktopWindow);
	if (!desktopDC) {
		std::cerr << "Failed to get desktop device context." << std::endl;
		return;
	}
	desktopCaptureDC = CreateCompatibleDC(desktopDC);
	if (!desktopCaptureDC) {
		std::cerr << "Failed to create compatible device context." << std::endl;
		return;
	}
	desktopCaptureBitmap = CreateCompatibleBitmap(desktopDC, getWidth(), getHeight());
	bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
	bmi.bmiHeader.biWidth = getWidth();
	bmi.bmiHeader.biHeight = -getHeight();
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
}

int Platform::getWidth() {
	return desktopRect.right - desktopRect.left;
}

int Platform::getHeight() {
	return desktopRect.bottom - desktopRect.top;
}

void Platform::getDesktopResolution(int& width, int& height) {
	width = getWidth();
	height = getHeight();
}

void Platform::getConsoleResolution(int& width, int& height) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void Platform::clearConsole() {
	std::cout << "\033[H"; 
}

uint32_t Platform::getDesktopPixelAt(int x, int y) {
	COLORREF color = GetPixel(desktopDC, x, y);
	ReleaseDC(NULL, desktopDC);
	unsigned short int a = 100;
	unsigned short int r = GetRValue(color);
	unsigned short int g = GetGValue(color);
	unsigned short int b = GetBValue(color);
	return (a << 24) | (r << 16) | (g << 8) | b;
}

void Platform::getDesktopPixels(std::vector<uint32_t>& pixels) {
	int width = getWidth();
	int height = getHeight();

	HGDIOBJ oldBitmap = SelectObject(desktopCaptureDC, desktopCaptureBitmap);

	BitBlt(desktopCaptureDC, 0, 0, width, height, desktopDC, 0, 0, SRCCOPY);

	RGBQUAD* pPix = new RGBQUAD[width * height];

	GetDIBits(desktopCaptureDC,
		desktopCaptureBitmap,
		0,
		height,
		pPix,
		&bmi,
		DIB_RGB_COLORS);

	for (int i = 0; i < width * height; ++i) {
		uint8_t a = 255;
		uint8_t r = pPix[i].rgbRed;
		uint8_t g = pPix[i].rgbGreen;
		uint8_t b = pPix[i].rgbBlue;
		pixels[i] = (a << 24) | (r << 16) | (g << 8) | b;
	}

	delete[] pPix;

	SelectObject(desktopCaptureDC, oldBitmap);
}