#include "stdafx.h"
#include "image.h"
#include <iostream>
#include <sstream>

image::image(std::string imgFileName)
{
	setImage(imgFileName);
}

image::image() {}

image::~image() {}

bool image::loaded()
{
	return imageLoaded;
}

unsigned int image::getHeight()
{
	return height;
}

unsigned int image::getWidth()
{
	return width;
}

std::string image::toString()
{
	std::string returnString;

	if (imageLoaded)
	{
		std::stringstream returnStream;
		std::copy(imageVector.begin(), imageVector.end(), std::ostream_iterator<int>(returnStream, " "));
		returnString = returnStream.str();
	}
	else
		returnString = "Image not loaded.\n";

	return returnString;
}

void image::setImage(const std::string fileName)
{
	unsigned int error = lodepng::decode(imageVector, width, height, fileName, LCT_RGBA, 8U);

	if (error)
		std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	imageLoaded = !error;
}