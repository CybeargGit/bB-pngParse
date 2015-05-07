#include "stdafx.h"
#include "palette.h"

palette::palette(paletteType palType)
{
	switch (palType)
	{
		case NTSC:
		{
			setImage("ntsc.png");
			break;
		}
		case PAL:
		{
			setImage("pal.png");
			break;
		}
	}
	setImageLoaded();
}

palette::palette(std::string palFileName) : image(palFileName)
{
	setImageLoaded();
}

void palette::setImageLoaded()
{
	imageLoaded = imageLoaded && height == 8 && width == 16;
}

palette::~palette() {}

unsigned char palette::findClosestColor(unsigned char r, unsigned char g, unsigned b)
{
	unsigned char i, colorIndex = 0;
	unsigned int vectorIndex;

	for (i = 0; i < 128; i++)
	{
		vectorIndex = i * 4;
		if (imageVector[vectorIndex] == r && imageVector[vectorIndex + 1] == g && imageVector[vectorIndex + 2] == b)
		{
			colorIndex = i;
			break;
		}
	}

	// convert left-to-right index of image to top-to-bottom index of palette
	return (colorIndex / 16) * 2 + ((colorIndex % 16) * 16);
}