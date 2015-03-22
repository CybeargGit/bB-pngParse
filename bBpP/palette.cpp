#include "stdafx.h"
#include "palette.h"

palette::palette(paletteType palType)
{
	switch (palType)
	{
		case NTSC:
		{
			palette("ntsc.png");
			break;
		}
		case PAL:
		{
			palette("pal.png");
			break;
		}
	}
}

palette::palette(std::string palFileName) : image(palFileName)
{
	imageLoaded = height == 8 && width == 16;
}

palette::~palette() {}

unsigned char palette::findClosestColor(unsigned char r, unsigned char g, unsigned b)
{
	unsigned char i, paletteIndex = 0;
	unsigned int vectorIndex;

	for (i = 0; i < 128; i++)
	{
		vectorIndex = i * 4;
		if (imageVector[vectorIndex] == r && imageVector[vectorIndex + 1] == g && imageVector[vectorIndex + 2] == b)
			paletteIndex = i;
	}

	return paletteIndex;
}