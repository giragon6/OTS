#include <fstream>  
#include <stdexcept>  
#include <cstdint>  
#include <vector>  

#include "Recorder.h"

Recorder::Recorder(int width, int height)
	: width(width), height(height), frameCount(0), totalSize(0)
{
    totalSize = static_cast<size_t>(width) * static_cast<size_t>(height) * sizeof(uint32_t);

    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and height must be positive integers.");
    }
}

void Recorder::saveToFile(std::string filepath)
{
    std::ofstream OutputFile(filepath, std::ios::binary);
    if (!OutputFile.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filepath);
    }

    for (const auto& frame : frames) {
        
    }
    OutputFile.close();
}

void Recorder::addFrame(const uint32_t* frameData, const size_t size)  
{  
    if (!frameData) {  
        throw std::invalid_argument("Frame data cannot be null.");  
    }  
    size_t expectedSize = static_cast<size_t>(width) * static_cast<size_t>(height);  
    if (size != expectedSize) {  
        throw std::out_of_range("Frame data size does not match the recorder dimensions.");  
    }  
    std::vector<uint32_t> frame(frameData, frameData + size);  
    frames.push_back(frame);  
}

void Recorder::clearFrames()
{
    frames.clear(); 
}