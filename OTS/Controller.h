#pragma once
#include <string>
enum ControllerState
{
	MIRROR_NO_RECORD,
	MIRROR_RECORD,
	PLAYBACK,
	CONTROLLER_ERR,
	TEXTENTER
};

class Controller
{
private:
	ControllerState state;
	bool paused;
	std::string textBuf;
public:
	Controller();
	~Controller() = default;

	void setState(ControllerState newState);
	ControllerState getState() const;

	void setPaused(bool paused);
	bool isPaused();

	std::string getControlsBar() const;
	std::string getPausedBar();
	std::string getStatusBar();
	std::string getTextBuffer() const;

	void handleTextInput(const char ch);
};

