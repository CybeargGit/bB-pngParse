// bBpP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "parser.h"
#include "palette.h"
#include "sprite.h"

#ifndef UNICODE  
typedef std::string String;
#else
typedef std::wstring String;
#endif

using namespace std;

int outputToFile(bool dpc, bool bB, paletteType palType, string spriteName, string palName, string outputName)
{
	palette* selectedPalette;
	sprite* selectedSprite;
	int outputResult = 0;

	if (palName == "")
		selectedPalette = new palette(palType);
	else
		selectedPalette = new palette(palName);

	if (outputName == "")
		outputName = "output.txt";

	selectedSprite = new sprite(spriteName);

	parser* spriteParser = new parser(selectedSprite, selectedPalette, dpc, bB);

	ofstream outputFile;
	try
	{
		outputFile.open(outputName, ios::out);
		if (outputFile.is_open())
		{
			spriteParser->parseSprite(&outputFile);
		}
		else
			outputResult = 3;
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
		outputResult = 4;
	}

	outputFile.close();

	return outputResult;
}

void outputError(int errorCode)
{
	switch (errorCode)
	{
	case 2:
		cout << "Incorrectly formatted arguments.\n";
		break;
	case 3:
		cout << "Specified output file can't be opened.\n";
		break;
	case 4:
		cout << "Parsing error.\n";
		break;
	case -1: case 1:
		cout << "bB pngParse - Convert png images into formatted sprite/color data for batariBasic. ";
		cout << "Palette files must be 8x16 pixels and sprites must have a width divisible by 8.\n\n";
		cout << "-s \"spritesheet.png\"\tSpecify sprite image (required)\n";
		cout << "-p \"secam.png\"\t\tSpecify palette image (ignores -P flag)\n";
		cout << "-o \"spriteData.txt\"\tSpecify output file (output.txt by default)\n";
		cout << "-P\t\t\tPAL palette (NTSC by default)\n";
		cout << "-D\t\t\tDPC kernel formatted (standard kernel by default)\n";
		cout << "-A\t\t\t6502 ASM formatted (bB formatted by default)\n";
		break;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	bool dpc = false, bB = true;
	paletteType palType = NTSC;
	string spriteName = "", palName = "", outputName = "";
	int outputResult = 0;

	int i = 1;
	while (i < argc && outputResult == 0)
	{
		string currArg = argv[i];
		if (currArg.compare("-help") == 0)
			outputResult = -1;
		else if (currArg.compare("-s") == 0 || currArg.compare("-p") == 0 || currArg.compare("-o") == 0)
		{
			if (i + 1 < argc)
			{
				if (currArg.compare("-s") == 0)
					spriteName = argv[i+1];
				else if (currArg.compare("-p") == 0)
					palName = argv[i+1];
				else if (currArg.compare("-o") == 0)
					outputName = argv[i+1];
				i++;
			}
			else
				outputResult = 2;
		}
		else if (currArg.compare("-D") == 0)
			dpc = true;
		else if (currArg.compare("-A") == 0)
			bB = false;
		else if (currArg.compare("-P") == 0)
			palType = PAL;
		i++;
	}

	if (spriteName.compare("") == 0 && outputResult != -1)
		outputResult = 1;
	else if (outputResult == 0)
		outputResult = outputToFile(dpc, bB, palType, spriteName, palName, outputName);

	// Handle error outputs
	outputError(outputResult);

	if (outputResult != 0)
		system("PAUSE");

	return outputResult;
}