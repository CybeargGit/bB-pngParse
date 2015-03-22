#pragma once
class parser
{
public:
	parser(bool dpcFormatted, bool bBFormat);
	~parser();

	void parsePixels(unsigned char * pixelArray, unsigned int length);
	void parseColors(unsigned char * colorArray, unsigned int length);
	void printImage(unsigned char * channelArray, unsigned int length);

private:
	bool dpc;
	bool bB;
};

