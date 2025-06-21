#include <iostream>
#include "App.h"
//#include <Windows.h>

int main(int argc, char* argv[])
{
	App app;
	AppState state = app.init();

	if (state == AppState::INIT_ERROR) {
		std::cerr << "Initialization failed." << std::endl;
		return 1;
	}

	state = app.run();

	if (state == AppState::RUNNING_ERROR) {
		std::cerr << "Running failed." << std::endl;
		return 1;
	}

	//HDC dc = GetDC(NULL);
	//COLORREF color = GetPixel(dc, 1, 1);
	//ReleaseDC(NULL, dc);
}