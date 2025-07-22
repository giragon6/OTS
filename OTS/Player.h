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
public:
    Player(int width, int height);
    ~Player() = default;

    void loadFromFile(const std::string& filepath);

    void getFrame(std::vector<uint32_t>& frame) override;
    void handleInput(InputType inp) override;
};
