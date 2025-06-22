#include "VideoBuffer.h"
#include <iostream>

VideoBuffer::VideoBuffer(int width, int height) : width(width), height(height), buffer(nullptr), size(0) {  
	if (width <= 0 || height <= 0) {  
		std::cerr << "Error: Width and height must be positive integers." << std::endl;  
		return;  
	}  
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
	for (int y = 0; y < height; y += 2) {
		for (int x = 0; x < width; ++x) {
			size_t i_top = y * width + x;
			size_t i_bottom = (y + 1) * width + x;

			uint32_t top_pixel = buffer[i_top];
			uint32_t bottom_pixel = (y + 1 < height) ? buffer[i_bottom] : 0;

			int top_r = (top_pixel >> 16) & 0xFF;
			int top_g = (top_pixel >> 8) & 0xFF;
			int top_b = top_pixel & 0xFF;

			int bottom_r = (bottom_pixel >> 16) & 0xFF;
			int bottom_g = (bottom_pixel >> 8) & 0xFF;
			int bottom_b = bottom_pixel & 0xFF;

			std::cout << "\033[38;2;" << top_r << ";" << top_g << ";" << top_b << "m"
				<< "\033[48;2;" << bottom_r << ";" << bottom_g << ";" << bottom_b << "m"
				<< "\xDC";
		}
		std::cout << "\033[0m" << std::endl;
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

void VideoBuffer::push(uint32_t pixels[], size_t pixelArraySize) {
	if (!buffer || size == 0) {
		std::cerr << "Error: Buffer is empty or not initialized." << std::endl;
		return;
	}
	if (!pixels) {
		std::cerr << "Error: Provided pixel array is null." << std::endl;
		return;
	}
	if (pixelArraySize != size) {
		std::cerr << "Error: Provided pixel array size does not match buffer size." << std::endl;
		return;
	}
	for (size_t i = 0; i < size; ++i) {
		buffer[i] = pixels[i];
	}
}

void VideoBuffer::downscaleWithAveraging(
	const uint32_t* src, int srcWidth, int srcHeight, 
	uint32_t* dst, int dstWidth, int dstHeight)
{
	for (int y = 0; y < dstHeight; ++y) {
		for (int x = 0; x < dstWidth; ++x) {
			int x0 = x * srcWidth / dstWidth;
			int x1 = (x + 1) * srcWidth / dstWidth;
			int y0 = y * srcHeight / dstHeight;
			int y1 = (y + 1) * srcHeight / dstHeight;

			uint64_t sumR = 0, sumG = 0, sumB = 0, sumA = 0;
			int count = 0;

			for (int sy = y0; sy < y1; ++sy) {
				for (int sx = x0; sx < x1; ++sx) {
					uint32_t pixel = src[sy * srcWidth + sx];
					uint8_t a = (pixel >> 24) & 0xFF;
					uint8_t r = (pixel >> 16) & 0xFF;
					uint8_t g = (pixel >> 8) & 0xFF;
					uint8_t b = pixel & 0xFF;
					sumA += a;
					sumR += r;
					sumG += g;
					sumB += b;
					++count;
				}
			}

			if (count == 0) count = 1;

			uint8_t avgA = static_cast<uint8_t>(sumA / count);
			uint8_t avgR = static_cast<uint8_t>(sumR / count);
			uint8_t avgG = static_cast<uint8_t>(sumG / count);
			uint8_t avgB = static_cast<uint8_t>(sumB / count);

			dst[y * dstWidth + x] = (avgA << 24) | (avgR << 16) | (avgG << 8) | avgB;
		}
	}
}
