#include "VideoBuffer.h"
#include <iostream>

VideoBuffer::VideoBuffer(int width, int height) : width(0), height(0), buffer(nullptr), size(0) {  
	if (width <= 0 || height <= 0) {  
		std::cerr << "Error: Width and height must be positive integers." << std::endl;  
		return;  
	}  
	this->width = width;  
	this->height = height;  
	size = width * height;  
	buffer = new uint32_t[size];  
}

VideoBuffer::~VideoBuffer() {
	if (buffer) {
		delete[] buffer;
		buffer = nullptr;
	}
	size = 0;
}

int VideoBuffer::getSize() {
	if (size) {
		return size;
	}
	return 0;
}

int VideoBuffer::getWidth() {
	if (width) {
		return width;
	}
	return 1;
}

int VideoBuffer::getHeight() {
	if (height) {
		return height;
	}
	return 1;
}

void VideoBuffer::render() {
	if (!buffer || size == 0) {
		std::cerr << "Error: Buffer is empty or not initialized." << std::endl;
		return;
	}
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			size_t i = y * width + x;
			uint32_t pixel = buffer[i];
			 std::cout << "\033[48;2;"
			 	<< ((pixel >> 16) & 0xFF) << ";"
			 	<< ((pixel >> 8) & 0xFF) << ";"
			 	<< (pixel & 0xFF) << "m  \033[0m";
		}
	}
}

void VideoBuffer::empty() {
	for (size_t i = 0; i < size; ++i) {
		buffer[i] = ' '; 
	}
}

void VideoBuffer::push(const Pixel pixel) {
	if (!buffer || size == 0) {
		std::cerr << "Error: Buffer is empty or not initialized." << std::endl;
		return;
	}
	if (pixel.x < 0 || pixel.y < 0 || pixel.x >= width || pixel.y >= height) {
		std::cerr << "Error: Pixel coordinates out of bounds." << std::endl;
		return;
	}
	size_t index = pixel.y * width + pixel.x;
	buffer[index] = (pixel.r << 16) | (pixel.g << 8) | pixel.b | (pixel.a << 24);
}

void VideoBuffer::push(std::vector<Pixel> pixels) {
	if (!buffer || size == 0) {
		std::cerr << "Error: Buffer is empty or not initialized." << std::endl;
		return;
	}
	for (const auto& pixel : pixels) {
		if (pixel.x < 0 || pixel.y < 0 || pixel.x >= width || pixel.y >= height) {
			std::cerr << "Error: Pixel coordinates out of bounds." << std::endl;
			continue;
		}
		size_t index = pixel.y * width + pixel.x;
		buffer[index] = (pixel.r << 16) | (pixel.g << 8) | pixel.b | (pixel.a << 24);
	}
}