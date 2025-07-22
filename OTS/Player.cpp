#include "Player.h"
#include <stdexcept>
#include <iostream>
#include <fstream>

Player::Player(int width, int height) : width(width), height(height) {}

void Player::loadFromFile(const std::string& file) {
    std::ifstream input(file, std::ios::binary);
    if (!input.is_open()) {
        throw std::runtime_error("Failed to open file for playback: " + file);
    }

    frames.clear();
    currentFrameIndex = 0;

    const size_t frameSize = width * height;
    std::vector<uint32_t> buffer(frameSize);

    while (input.read(reinterpret_cast<char*>(buffer.data()), frameSize * sizeof(uint32_t))) {
        frames.push_back(buffer);
    }
    input.close();
}

void Player::getFrame(std::vector<uint32_t>& frame) {
    if (frames.empty() || currentFrameIndex >= frames.size()) {
        return;
    }
    frame = frames[currentFrameIndex++];
}

void Player::handleInput(InputType inp)
{
}
