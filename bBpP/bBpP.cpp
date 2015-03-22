// bBpP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "parser.h"
#include "palette.h"
#include "sprite.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	image* newImage = new palette(NTSC);
	cout << newImage->getHeight() << endl << newImage->getWidth() << endl << newImage->toString() << endl;

	system("PAUSE");

	return 0;
}

