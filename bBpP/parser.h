#include <fstream>
#include "palette.h"
#include "sprite.h"

#pragma once
class parser
{
public:
	parser(sprite* spr, palette* pal, bool dpcFormatted, bool bBFormat);
	~parser();

	void parseSprite(std::ofstream* fileStream);

private:
	bool dpc;
	bool bB;
	sprite* spr;
	palette* pal;
};

