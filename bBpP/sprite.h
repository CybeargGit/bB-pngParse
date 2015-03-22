#include "image.h"
#include "palette.h"

#pragma once
class sprite: public image
{
public:
	sprite(std::string imgFileName);
	~sprite();

	unsigned char* getShape();
	unsigned char* getColors(palette * spritePalette);
};

