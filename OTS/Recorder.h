#pragma once
#include <vector>
#include "Platform.h"
#include "IFrameStream.h"

class Recorder : public IFrameStream
{  
private:
	Platform* platform;
    int width;  
    int height;  
    int totalSize;  
	bool isRecording;
    std::vector<std::vector<uint32_t>> frames;
public:
    Recorder(int width, int height, Platform* platform);  
    ~Recorder() = default; 

    void saveToFile(std::string filepath);  
    void addFrame(std::vector<uint32_t> frameData, size_t size);
    void clearFrames();

    void getFrame(std::vector<uint32_t>& frame) override;
    void handleInput(InputType inp) override;

    void setIsRecording(bool isRecording);
	bool getIsRecording() const;
};
