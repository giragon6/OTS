#include <iostream>

#include "App.h"
#include "VideoBuffer.h"
#include "Platform.h"

App::App(Platform platform) : videoBuffer(videoBuffer), platform(platform), screen(platform) {};

AppState App::init() {
	int dw, dh;
	platform.getDesktopResolution(dw, dh);
	//int cw, ch;
	//platform.getConsoleResolution(cw, ch);
	//videoBuffer = new VideoBuffer(cw, ch);
	videoBuffer = new VideoBuffer(80, 45);
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

	int srcWidth = platform.getWidth();
	int srcHeight = platform.getHeight();
	int dstWidth = 80;  
	int dstHeight = 45; 

	uint32_t* srcPixels = new uint32_t[srcWidth * srcHeight];
	platform.getDesktopPixels(srcPixels);

	uint32_t* dstPixels = new uint32_t[dstWidth * dstHeight];
	VideoBuffer::downscaleWithAveraging(srcPixels, srcWidth, srcHeight, dstPixels, dstWidth, dstHeight);

	videoBuffer->push(dstPixels, dstWidth * dstHeight);

	videoBuffer->render();

	delete[] srcPixels;
	delete[] dstPixels;
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