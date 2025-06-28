#pragma once
#include <vector>
#include <string>

#include "Pixel.h"
class VideoBuffer
{
private:
	uint32_t* buffer;
	int width;
	int height;
	size_t size;

public:
	VideoBuffer(int width, int height);
	~VideoBuffer();

	int getSize();
	int getWidth();
	int getHeight();

	std::string getRender();
	void empty();

	void push(const Pixel pixel);
	void push(std::vector<Pixel> pixels);
	int push(uint32_t pixels[], size_t pixelArraySize); // TODO: use enum

	static void downscaleWithAveraging(const uint32_t* src,
		int srcWidth,
		int srcHeight,
		uint32_t* dst,
		int dstWidth,
		int dstHeight);

	uint32_t* getPixels();
};

