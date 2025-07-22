#include "Player.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <zlib.h>

Player::Player(int width, int height, const std::string& filepath) : width(width), height(height), filepath(filepath) {}

void Player::loadFromFile() {
    std::ifstream input(filepath, std::ios::binary);
    if (!input.is_open()) {
        throw std::runtime_error("Failed to open file for playback: " + filepath);
    }

    frames.clear();
    currentFrameIndex = 0;

    const size_t frameSize = width * height;
    uLongf decompressedSize = frameSize * sizeof(uint32_t);

    while (input.peek() != EOF) {
        uLongf compressedSize;
        input.read(reinterpret_cast<char*>(&compressedSize), sizeof(compressedSize));
        if (input.gcount() != sizeof(compressedSize)) break;

        std::vector<Bytef> compressedData(compressedSize);
        input.read(reinterpret_cast<char*>(compressedData.data()), compressedSize);
        if (input.gcount() != compressedSize) break;

        std::vector<uint32_t> buffer(frameSize);
        int res = uncompress(reinterpret_cast<Bytef*>(buffer.data()), &decompressedSize,
            compressedData.data(), compressedSize);
        if (res != Z_OK) {
            throw std::runtime_error("Decompression failed.");
        }
        frames.push_back(buffer);
    }
    input.close();
	//// print frames for debugging
 //   std::cout << "Loaded " << frames.size() << " frames from file: " << file << std::endl;
 //   if (frames.empty()) {
 //       throw std::runtime_error("No frames loaded from the file.");
 //   }
	//// print pixels from frames for debugging
 //   for (const auto& frame : frames) {
 //       std::cout << "Frame size: " << frame.size() << std::endl;
 //       for (size_t i = 0; i < frame.size() / sizeof(uint32_t); ++i) {
 //           std::cout << frame[i] << " ";
 //       }
 //       std::cout << std::endl;
	//}
	currentFrameIndex = 0;
}

int Player::getFrame(std::vector<uint32_t>& frame) {
    if (frames.empty() || currentFrameIndex >= frames.size()) {
        return 1;
    }
    frame = frames[currentFrameIndex++];
    return 0;
}

void Player::handleInput(InputType inp)
{
    switch (inp) {
        case InputType::LOAD:
			loadFromFile();
            break;
	}
}
