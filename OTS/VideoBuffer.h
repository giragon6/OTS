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
};

