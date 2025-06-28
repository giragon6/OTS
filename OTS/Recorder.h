#pragma once
#include <string>

class Recorder  
{  
public:  
    int width;  
    int height;  
    int totalSize;  
    int frameCount;  
    std::vector<std::vector<uint32_t>> frames; 

    Recorder(int width, int height);  
    ~Recorder() = default; 

    void saveToFile(std::string filepath);  
    void addFrame(const uint32_t* frameData, size_t size);
    void clearFrames();  
};
