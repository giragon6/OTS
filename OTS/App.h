#pragma once
#include "VideoBuffer.h"
#include "Platform.h"
#include "Screen.h"
#include "Controller.h"
#include "Recorder.h"
#include "Player.h"
#include "IFrameStream.h"

enum class AppState
{
	INIT,
	INIT_ERROR,
	RUNNING,
	RUN_ERROR,
	EXIT,
};

enum class AppMode
{
	MIRROR,
	PLAYBACK,
	RECORD,
	PAUSE,
	SAVE
};

interface IFrameSource
{
	virtual ~IFrameSource() = default;
	virtual bool open(const char* filename) = 0;
	virtual void close() = 0;
	virtual bool readFrame(uint32_t* pixels, int width, int height) = 0;
	virtual bool writeFrame(const uint32_t* pixels, int width, int height) = 0;
	virtual bool isOpen() const = 0;
};

class App
{
private:
	AppMode mode;
	VideoBuffer* videoBuffer;
	Platform* platform;
	Screen* screen;
	Controller* controller;
	Recorder* recorder;
	IFrameStream* provider; 
public:
	App(Platform platform, IFrameStream* provider, AppMode initialMode);
	~App() = default;
	AppState init();
	AppState run();

	void setMode(AppMode mode);
	AppMode getMode() const;

	//void renderPlaybackFrame(uint32_t* dstPixels, int dstWidth, int dstHeight);
	//void renderRecordFrame(uint32_t* srcPixels, int srcWidth, int srcHeight, uint32_t* dstPixels, int dstWidth, int dstHeight);
	void renderFrame(uint32_t* srcPixels, int srcWidth, int srcHeight, uint32_t* dstPixels, int dstWidth, int dstHeight);

	void shutdown();
};

