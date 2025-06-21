#include "App.h"
#include "VideoBuffer.h"
#include <iostream>

AppState App::init() {
	//int dw, dh;
	//platform.getDesktopResolution(dw, dh);
	int cw, ch;
	platform.getConsoleResolution(cw, ch);
	videoBuffer = new VideoBuffer(cw, ch);
	if (!videoBuffer) {
		std::cerr << "Error: Failed to initialize VideoBuffer." << std::endl;
		return AppState::INIT_ERROR; 
	}
	else {
		return AppState::INIT; 
	}
}

AppState App::run() {
	if (!videoBuffer) {
		std::cerr << "Error: VideoBuffer not initialized." << std::endl;
		return AppState::RUNNING_ERROR;
	}
	videoBuffer->empty();
	int w = videoBuffer->getWidth();
	for (int i = 0; i < videoBuffer->getSize(); i++) {
		Pixel randPix =
		{
			i % w, // x
			i / w, // y
			100, // a
			rand() % 256, // r
			rand() % 256, // g
			rand() % 256, //b
		};
		videoBuffer->push(randPix);
	}
	videoBuffer->render();
	return AppState::RUNNING;
}

AppState App::shutdown() {
	if (videoBuffer) {
		delete videoBuffer;
		videoBuffer = nullptr;
		std::cout << "VideoBuffer shut down successfully." << std::endl;
		return AppState::SHUTDOWN; 
	}
	else {
		std::cerr << "Error: VideoBuffer not initialized." << std::endl;
		return AppState::SHUTDOWN_ERROR; 
	}
}