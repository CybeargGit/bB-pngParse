#include "stdafx.h"
#include "sprite.h"


sprite::sprite(std::string spriteFileName) : image(spriteFileName)
{
	imageLoaded = width && width % 8 == 0;
}

sprite::~sprite(){}

unsigned char* sprite::getShape()
{
	unsigned char* outputArray = new unsigned char[height * (width / 8)]{0};
	unsigned int i, j, k, pixelIndex;
	unsigned char byte;

	// iterate through sprites in row
	for (i = 0; i < width / 8; i++)
	{
		// iterature through lines of sprite
		for (j = 0; j < height; j++)
		{
			byte = 0; // initialize byte to 0
			// iterate through pixels in sprite line
			for (k = 0; k < 8; k++)
			{
				pixelIndex = (i * 36) + (j * width) + (k * 4);
				if (imageVector[pixelIndex + 3] == 255)
					byte += 1 << k; // if alpha is full, set pixel's bit to 1
			}
			outputArray[(height * i) + j] = byte;
		}
	}

	return outputArray;
}

// return a list of colors for all sprites
unsigned char* sprite::getColors(palette * spritePalette)
{
	unsigned char* outputArray = new unsigned char[height * (width / 8)]{0};
	unsigned int i, j, k, pixelIndex;
	unsigned char r, g, b;

	// iterate through sprites in row
	for (i = 0; i < width / 8; i++)
	{
		// iterature through lines of sprite
		for (j = 0; j < height; j++)
		{
			r = g = b = 0; // initialize red, green, and blue to 0 in case there are no non-transparent pixels
			// iterate through pixels in sprite line
			for (k = 0; k < 8; k++)
			{
				pixelIndex = (i * 36) + (j * width) + (k * 4);
				if (imageVector[pixelIndex + 3] == 255)
				{
					r = imageVector[pixelIndex];
					g = imageVector[pixelIndex + 1];
					b = imageVector[pixelIndex + 2];
					break; // find the first solid pixel and break -- that will be the color for this line
				}
			}
			outputArray[(height * i) + j] = spritePalette->findClosestColor(r, g, b);
		}
	}
	
	return outputArray;
}