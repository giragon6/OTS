#pragma once
#include "VideoBuffer.h"
#include "Platform.h"
enum class AppState
{
	INIT,
	RUNNING,
	SHUTDOWN,
	RUNNING_ERROR,
	INIT_ERROR,
	SHUTDOWN_ERROR,
};

class App
{
private:
	VideoBuffer* videoBuffer;
	Platform platform;
public:
	App() = default;
	~App() = default;
	AppState init();
	AppState run();
	AppState shutdown();
};

