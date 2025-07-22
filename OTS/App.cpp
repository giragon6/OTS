#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>

#include "App.h"
#include "VideoBuffer.h"
#include "Platform.h"
#include "Controller.h"
#include "Recorder.h"
#include "IFrameStream.h"

App::App(Platform platform, IFrameStream* provider) :
	videoBuffer(videoBuffer),
	platform(&platform),
	controller(new Controller()),
	screen(screen),
	provider(provider)
{
	mode = AppMode::RECORD;
};

AppState App::init() {
	int width = 120;
	int height = 55;
	Controller controller;
	videoBuffer = new VideoBuffer(width, height);
	if (!videoBuffer) {
		std::cerr << "Error: Failed to initialize." << std::endl;
		return AppState::INIT_ERROR; 
	}
	else {
		return AppState::INIT; 
	}
}

void App::setMode(AppMode mode) {
	mode = mode;
}

AppMode App::getMode() const {
	return mode;
}

AppState App::run() {
	std::cout << "Starting application..." << std::endl;
	if (!videoBuffer) {
		std::cerr << "Error: VideoBuffer not initialized." << std::endl;
		return AppState::RUN_ERROR;
	}
	videoBuffer->empty();

	int srcWidth = platform->getWidth();
	int srcHeight = platform->getHeight();
	int dstWidth = videoBuffer->getWidth();  
	int dstHeight = videoBuffer->getHeight(); 

	uint32_t* srcPixels = new uint32_t[srcWidth * srcHeight];
	uint32_t * dstPixels = new uint32_t[dstWidth * dstHeight];

	auto lastFrame = std::chrono::steady_clock::now();
	const auto frameDuration = std::chrono::milliseconds(150);

	switch (getMode()) 
	{
	case AppMode::RECORD:
		while (true) {
			if (_kbhit()) {
				int ch = _getch();
				if (ch == 'q' || ch == 'Q') {
					break;
				}
				if (ch == 'p' || ch == 'P') {
					controller->setPaused(!controller->isPaused());
				}
				if (ch == 'r' || ch == 'R') {
					controller->setState(ControllerState::MIRROR_RECORD);
					provider->handleInput(InputType::RECORD);
				}
				if (ch == 's' || ch == 'S') {
					controller->setPaused(true);
					controller->setState(ControllerState::TEXTENTER);
					provider->handleInput(InputType::SAVE);
				}
			}
			auto now = std::chrono::steady_clock::now();

			if (now - lastFrame >= frameDuration) {
				std::vector<uint32_t> frame = std::vector<uint32_t>(srcWidth * srcHeight);
				provider->getFrame(frame);
				std::copy(frame.begin(), frame.end(), srcPixels);
				renderFrame(srcPixels, srcWidth, srcHeight, dstPixels, dstWidth, dstHeight);
				lastFrame = now;
			}
			else {
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
	}

	std::cout << "Exiting application..." << std::endl;
	delete[] srcPixels;
	delete[] dstPixels;
	return AppState::RUNNING;
}

void App::renderFrame(uint32_t* srcPixels, int srcWidth, int srcHeight, uint32_t* dstPixels, int dstWidth, int dstHeight) {
	videoBuffer->empty();

	VideoBuffer::downscaleWithAveraging(srcPixels, srcWidth, srcHeight, dstPixels, dstWidth, dstHeight);

	videoBuffer->push(dstPixels, dstWidth * dstHeight);

	platform->clearConsole();

	std::string render = videoBuffer->getRender();

	std::cout << render;
}

AppState App::shutdown() {
	if (videoBuffer) {
		delete videoBuffer;
		videoBuffer = nullptr;
		std::cout << "VideoBuffer shut down successfully." << std::endl;
	}
	if (platform) {
		delete platform;
		platform = nullptr;
		std::cout << "Platform shut down successfully." << std::endl;
	}
	if (controller) {
		delete controller;
		controller = nullptr;
		std::cout << "Controller shut down successfully." << std::endl;
	}
	if (recorder) {
		delete recorder;
		recorder = nullptr;
		std::cout << "Recorder shut down successfully." << std::endl;
	}
	return AppState::EXIT; 
}