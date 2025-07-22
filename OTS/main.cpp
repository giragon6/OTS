#include <iostream>
#include "App.h"

int main(int argc, char* argv[])
{
	App* app;
	AppMode initialMode = AppMode::RECORD;
	AppState state = AppState::INIT;
	Platform* platform = new Platform();
	int width = 120;
	int height = 55;
	//platform->getConsoleResolution(width, height);
	IFrameStream* provider;
	while (state != AppState::EXIT && state != AppState::RUN_ERROR) {
		std::string filepath;
		std::cout << "Enter file path for recording/playback: ";
		std::cin >> filepath;

		if (filepath.empty()) {
			std::cerr << "File path cannot be empty." << std::endl;
			return 1;
		}

		std::string mode;
		std::cout << "Enter mode (record/playback/quit): ";
		std::cin >> mode;


		while (mode != "record" && mode != "playback" && mode != "quit") {
			std::cerr << "Invalid mode. Please enter 'record', 'playback', or 'quit'." << std::endl;
			std::cout << "Enter mode (record/playback/quit): ";
			std::cin >> mode;
		}
		if (mode == "quit") {
			std::cout << "Exiting application." << std::endl;
			return 0;
		}
		else if (mode == "record") {
			initialMode = AppMode::RECORD;
			provider = new Recorder(width, height, platform->getWidth(), platform->getHeight(), platform, filepath);
			
		}
		else if (mode == "playback") {
			initialMode = AppMode::PLAYBACK;
			provider = new Player(width, height, filepath);

		}
		else {
			std::cerr << "Unexpected mode." << std::endl;
			return 1;
		}

		app = new App(*platform, provider, initialMode);
		AppState state = app->init();

		state = app->run();
	}
	
	app->shutdown();


	if (state == AppState::INIT_ERROR) {
		std::cerr << "Initialization failed." << std::endl;
		return 1;
	}
}