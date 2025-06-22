#pragma once
#include "Pixel.h"
#include <vector>
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

	void render();
	void empty();

	void push(const Pixel pixel);
	void push(std::vector<Pixel> pixels);
	void push(uint32_t pixels[], size_t pixelArraySize);

	static void downscaleWithAveraging(const uint32_t* src,
		int srcWidth,
		int srcHeight,
		uint32_t* dst,
		int dstWidth,
		int dstHeight);
};

