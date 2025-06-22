#pragma once
#include "Pixel.h"
#include "Platform.h"
#include <wingdi.h>
class Screen
{
private:
	Platform platform;
	int width;
	int height;
public:
	Screen(Platform platform);
	~Screen() = default;

	int getWidth() const;
	int getHeight() const;

	void getScreenPixels(uint32_t pixelBuf[]);
	Pixel getPixelAtScreenPosition(int x, int y);
};

