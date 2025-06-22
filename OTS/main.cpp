#include <iostream>
#include "App.h"

int main(int argc, char* argv[])
{
	Platform* platform = new Platform();
	App app(*platform);
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
}