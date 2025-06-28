#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>

#include "App.h"
#include "VideoBuffer.h"
#include "Platform.h"
#include "Controller.h"
#include "Recorder.h"

App::App(Platform platform) : videoBuffer(videoBuffer), platform(platform), controller(controller), screen(platform), recorder(recorder) {};

AppState App::init() {
	int width = 120;
	int height = 55;
	controller = Controller();
	videoBuffer = new VideoBuffer(width, height);
	recorder = Recorder(width, height);
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
	const auto frameDuration = std::chrono::milliseconds(150);

	while (true) {
		if (_kbhit()) {
			int ch = _getch();
			if (controller.getState() == ControllerState::TEXTENTER) {
				if (ch == '\r' || ch == '\n') {
					controller.setState(ControllerState::MIRROR_NO_RECORD);
					controller.setPaused(false);
					recorder.saveToFile(controller.getTextBuffer() + ".raw");
				}
				controller.handleTextInput(ch);
			}
			if (ch == 'p' || ch == 'P') {
				controller.setPaused(!controller.isPaused());
			}
			if (ch == 'q' || ch == 'Q') {
				break;
			}
			if (ch == 'r' || ch == 'R') {
				controller.setState(ControllerState::MIRROR_RECORD);
			}
			if (ch == 's' || ch == 'S') {
				controller.setPaused(true);
				controller.setState(ControllerState::TEXTENTER);
			}
		}
		auto now = std::chrono::steady_clock::now();
		if (now - lastFrame >= frameDuration) {
			if (!controller.isPaused()) {
				videoBuffer->empty();

				platform.getDesktopPixels(srcPixels);

				VideoBuffer::downscaleWithAveraging(srcPixels, srcWidth, srcHeight, dstPixels, dstWidth, dstHeight);

				videoBuffer->push(dstPixels, dstWidth * dstHeight);
			}

			platform.clearConsole();

			std::string render = videoBuffer->getRender();

			std::cout << render;
			
			lastFrame = now;

			std::cout << controller.getPausedBar() << " * "
				<< controller.getStatusBar() << std::endl;
			std::cout << controller.getControlsBar();

			ControllerState cstate = controller.getState();

			switch (cstate) {
			case ControllerState::MIRROR_NO_RECORD:
				recorder.addFrame(dstPixels, dstWidth * dstHeight);
				break;
			case ControllerState::TEXTENTER:
				std::cout << "Enter filename: " << controller.getTextBuffer() << ".raw";
			}
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