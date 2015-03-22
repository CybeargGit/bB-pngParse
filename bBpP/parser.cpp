#include "stdafx.h"
#include "parser.h"


parser::parser(bool dpcFormatted, bool bBFormat)
{
	dpc = dpcFormatted;
	bB = bBFormat;
}


parser::~parser() {}

void parser::parsePixels(unsigned char * pixelArray, unsigned int length)
{
	// TO DO
}

void parser::parseColors(unsigned char * colorArray, unsigned int length)
{
	// TO DO
}

void parser::printImage(unsigned char * channelArray, unsigned int length)
{
	// TO DO
}