#include "lodepng.h"
#include "image.h"

enum paletteType { NTSC, PAL, CUSTOM };

#pragma once
class palette: public image
{
public:
	palette(paletteType palType);
	palette(std::string palFileName);
	~palette();

	unsigned char findClosestColor(unsigned char r, unsigned char g, unsigned b);
private:
	void setImageLoaded();
};

