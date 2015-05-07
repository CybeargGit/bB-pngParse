#include "stdafx.h"
#include "parser.h"
#include <stack>
#include <queue>
#include <list>
#include <iomanip>
#include <bitset>

using namespace std;

parser::parser(sprite* s, palette* p, bool dpcFormatted, bool bBFormat)
{
	spr = s;
	pal = p;
	dpc = dpcFormatted;
	bB = bBFormat;
}

parser::~parser() {}

void parser::parseSprite(std::ofstream* fileStream)
{
	stack<unsigned char> spriteStack;
	stack<unsigned char> colorStack;
	queue<unsigned char> spriteQueue;
	queue<unsigned char> colorQueue;
	list<string> outputList;
	unsigned char* spriteArray = spr->getShape();
	unsigned char* colorArray = spr->getColors(pal);
	unsigned int spriteHeight = spr->getHeight();
	unsigned int spriteCount = spr->getWidth() / 8;

	for (unsigned int i = 0; i < spriteCount; i++)
	{
		for (unsigned int j = 0; j < spriteHeight; j++)
		{
			if (!dpc)
			{
				spriteStack.push(spriteArray[j + (i * spriteHeight)]);
				colorStack.push(colorArray[j + (i * spriteHeight)]);
			}
			else
			{
				spriteQueue.push(spriteArray[j + (i * spriteHeight)]);
				colorQueue.push(colorArray[j + (i * spriteHeight)]);
			}
		}

		unsigned char tempByte;

		// Sprite Color Data //
		*fileStream << "__sprite" << i << "color" << endl;
		if (bB) // color header for batariBasic
			*fileStream << " player0color:" << endl;

		while ((!dpc && !colorStack.empty()) || (dpc && !colorQueue.empty()))
		{
			if (!bB) // ASM byte prefix
				*fileStream << "    .byte ";

			if (!dpc) // reverse sprites for standard kernel
			{
				tempByte = colorStack.top();
				colorStack.pop();
			}
			else // don't reverse sprites for DPC
			{
				tempByte = colorQueue.front();
				colorQueue.pop();
			}

			*fileStream << " $" << hex << (int)tempByte << endl;
		}

		if (bB) // color footer for batariBasic
			*fileStream << "end" << endl;

		*fileStream << endl;

		// Sprite Image Data //
		*fileStream << "__sprite" << i << endl;
		if (bB) // sprite header for batariBasic
			*fileStream << " player0:" << endl;

		while ((!dpc && !spriteStack.empty()) || (dpc && !spriteQueue.empty()))
		{
			if (!bB) // ASM byte prefix
				*fileStream << "    .byte ";

			if (!dpc) // reverse sprites for standard kernel
			{
				tempByte = spriteStack.top();
				spriteStack.pop();
			}
			else // don't reverse sprites for DPC
			{
				tempByte = spriteQueue.front();
				spriteQueue.pop();
			}

			*fileStream << " %" << bitset<8>((int)tempByte) << endl;
		}

		if (bB) // sprite footer for batariBasic
			*fileStream << "end" << endl;

		*fileStream << endl;
	}
}