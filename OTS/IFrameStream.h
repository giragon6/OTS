#pragma once

#include <cstdint>

enum class InputType
{
	RECORD,
	SAVE
};

class IFrameStream
{
public:
	virtual void getFrame(std::vector<uint32_t>& frame) = 0;
	virtual void handleInput(InputType inp) = 0;
};