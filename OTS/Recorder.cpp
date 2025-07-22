#include <fstream>  
#include <stdexcept>  
#include <cstdint>  
#include <vector>
#include <zlib.h>

#include "Recorder.h"
#include "Platform.h"

Recorder::Recorder(int width, int height, int srcWidth, int srcHeight, Platform* platform, const std::string& filepath)
	: width(width), height(height), srcWidth(srcWidth), srcHeight(srcHeight), platform(platform), filepath(filepath), isRecording(false), totalSize(0)
{
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and height must be positive integers.");
    }
}

int Recorder::getWidth() const
{
    return width;
}

int Recorder::getHeight() const
{
    return height;
}

void Recorder::saveToFile()
{
    std::ofstream OutputFile(filepath, std::ios::binary);
    if (!OutputFile.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filepath);
    }

    for (const auto& frame : frames) {
        //if (frame.size() != static_cast<size_t>(width) * static_cast<size_t>(height)) {
        //    throw std::out_of_range("Frame size does not match the recorder dimensions.");
        //}
        uLongf srcLen = frame.size() * sizeof(uint32_t);
        uLongf destLen = compressBound(srcLen);

        std::vector<Bytef> compressedData(destLen);

        int res = compress2(compressedData.data(), &destLen,
            reinterpret_cast<const Bytef*>(frame.data()), srcLen,
            Z_BEST_COMPRESSION);
        if (res != Z_OK) {
            throw std::runtime_error("Compression failed.");
        }

        OutputFile.write(reinterpret_cast<const char*>(&destLen), sizeof(destLen));
        OutputFile.write(reinterpret_cast<const char*>(compressedData.data()), destLen);
    }
    OutputFile.close();
}

void Recorder::addFrame(std::vector<uint32_t> frameData, const size_t size)  
{  
    //size_t expectedSize = static_cast<size_t>(width) * static_cast<size_t>(height);  
    //if (size != expectedSize) {
    //    throw std::out_of_range("Frame data size does not match the recorder dimensions.");
    //};
    frames.push_back(frameData);  
}

void Recorder::clearFrames()
{
    frames.clear(); 
}

void Recorder::setIsRecording(bool isRecord)
{
	isRecording = isRecord;
}

bool Recorder::getIsRecording() const
{
    return isRecording;
}

int Recorder::getFrame(std::vector<uint32_t>& frame) {
    std::vector<uint32_t>* newFrame = new std::vector<uint32_t>(srcWidth * srcHeight);
    platform->getDesktopPixels(*newFrame);
	frame = *newFrame;
    return 0;
}

void Recorder::handleInput(InputType inp) {
    switch (inp) {
    case InputType::RECORD:
        setIsRecording(true);
    case InputType::SAVE:
        saveToFile();
    }
}
