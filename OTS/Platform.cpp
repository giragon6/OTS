#include "Platform.h"
#include <Windows.h>

void Platform::getDesktopResolution(int& width, int& height) {
	RECT desktopRect;
	HWND desktopWindow = GetDesktopWindow();
	GetWindowRect(desktopWindow, &desktopRect);
	width = desktopRect.right - desktopRect.left;
	height = desktopRect.bottom - desktopRect.top;
}

void Platform::getConsoleResolution(int& width, int& height) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}