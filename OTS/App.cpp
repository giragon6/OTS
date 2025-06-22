#include <iostream>
#include <chrono>
#include <thread>

#include "App.h"
#include "VideoBuffer.h"
#include "Platform.h"

App::App(Platform platform) : videoBuffer(videoBuffer), platform(platform), screen(platform) {};

AppState App::init() {
	videoBuffer = new VideoBuffer(120, 55);
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
	int dstWidth = videoBuffer->getWidth();  
	int dstHeight = videoBuffer->getHeight(); 

	uint32_t* srcPixels = new uint32_t[srcWidth * srcHeight];
	uint32_t * dstPixels = new uint32_t[dstWidth * dstHeight];

	auto lastFrame = std::chrono::steady_clock::now();
	const auto frameDuration = std::chrono::milliseconds(333);

	while (true) {
		auto now = std::chrono::steady_clock::now();
		if (now - lastFrame >= frameDuration) {
			videoBuffer->empty();

			platform.getDesktopPixels(srcPixels);

			VideoBuffer::downscaleWithAveraging(srcPixels, srcWidth, srcHeight, dstPixels, dstWidth, dstHeight);

			videoBuffer->push(dstPixels, dstWidth * dstHeight);
			
			platform.clearConsole();

			videoBuffer->render();

			lastFrame = now;
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

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