#include "lodepng.h"
#include <string>

#pragma once
class image
{
public:
	image(std::string imgFileName);
	~image();
	unsigned int getWidth();
	unsigned int getHeight();
	bool loaded();
	std::string toString();

protected:
	image();
	std::vector<unsigned char> imageVector;
	void setImage(std::string fileName);

	unsigned int width;
	unsigned int height;
	bool imageLoaded;
};

