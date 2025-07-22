#include <iostream>
#include "App.h"

int main(int argc, char* argv[])
{
	Platform* platform = new Platform();
	IFrameStream* provider = new Recorder(platform->getWidth(), platform->getHeight(), platform);
	App app(*platform, provider);
	AppState state = app.init();

	if (state == AppState::INIT_ERROR) {
		std::cerr << "Initialization failed." << std::endl;
		return 1;
	}

	while (state != AppState::EXIT && state != AppState::RUN_ERROR) {
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
			app.setMode(AppMode::RECORD);
		}
		else if (mode == "playback") {
			app.setMode(AppMode::PLAYBACK);
		}
		else {
			std::cerr << "Unexpected mode." << std::endl;
			return 1;
		}

		state = app.run();
	}
}