#include <string>
#include <iostream>

#include "Controller.h"

Controller::Controller() : state(ControllerState::MIRROR_NO_RECORD), paused(false), textBuf("") {}

void Controller::setState(ControllerState newState)
{
	state = newState;
}

ControllerState Controller::getState() const
{
	return state;
}

void Controller::setPaused(bool pauseStatus)
{
	paused = pauseStatus;
}

bool Controller::isPaused()
{
	return paused;
}

std::string Controller::getControlsBar() const
{
	return "P - Pause/Unpause | Q - Quit";
}

std::string Controller::getPausedBar() {
	return paused ? "PAUSED" : "RUNNING";
}

std::string Controller::getStatusBar()
{
	std::string status;
	switch (state) {
		case ControllerState::MIRROR_NO_RECORD:
			return "NOT RECORDING";
		case ControllerState::MIRROR_RECORD:
			return "RECORDING";
		case ControllerState::PLAYBACK:
			return "PLAYING";
		default:
			return "ERROR OCCURRED";
	}
}

std::string Controller::getTextBuffer() const
{
	return textBuf;
}

void Controller::handleTextInput(const char ch)
{
	if (ch == '\n') {
		if (!textBuf.empty()) {
			textBuf.clear();
		}
	} else if (ch == '\b' || ch == 127) { // Handle backspace
		if (!textBuf.empty()) {
			textBuf.pop_back();
		}
	} else if (ch >= 32 && ch <= 126) { // Printable characters
		textBuf += ch;
	}
}
