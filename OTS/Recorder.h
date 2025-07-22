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
	int srcWidth;
	int srcHeight;
    int totalSize;  
	bool isRecording;
    std::vector<std::vector<uint32_t>> frames;
	std::string filepath;
public:
    Recorder(int width, int height, int srcWidth, int srcHeight, Platform* platform, const std::string& filepath);
    ~Recorder() = default; 

    void saveToFile();  
    void addFrame(std::vector<uint32_t> frameData, size_t size);
    void clearFrames();

    int getFrame(std::vector<uint32_t>& frame) override;
    void handleInput(InputType inp) override;

    void setIsRecording(bool isRecording);
	bool getIsRecording() const;

    int getWidth() const;
    int getHeight() const;
};
