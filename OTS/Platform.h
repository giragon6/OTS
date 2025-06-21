#pragma once
class Platform
{
public:
	Platform() = default;
	~Platform() = default;
	void getDesktopResolution(int& width, int& height);
	void getConsoleResolution(int& width, int& height);
};

