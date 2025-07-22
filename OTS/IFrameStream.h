#pragma once

#include <cstdint>

enum class InputType
{
	RECORD,
	SAVE,
	LOAD
};

class IFrameStream
{
public:
	virtual int getFrame(std::vector<uint32_t>& frame) = 0;
	virtual void handleInput(InputType inp) = 0;
};