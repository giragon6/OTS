#pragma once
#include <string>
#include <vector>
#include "IFrameStream.h"

class Player : public IFrameStream
{
private:
    int width;
    int height;
    std::vector<std::vector<uint32_t>> frames;
    int currentFrameIndex = 0;
	std::string filepath;
public:
    Player(int width, int height, const std::string& filepath);
    ~Player() = default;

    void loadFromFile();

    int getFrame(std::vector<uint32_t>& frame) override;
    void handleInput(InputType inp) override;
};
