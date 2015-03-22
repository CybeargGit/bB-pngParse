#pragma once
class color
{
public:
	struct channels
	{
		unsigned int red;
		unsigned int green;
		unsigned int blue;
		unsigned int alpha;
	};
	color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);
	~color();
private:
	channels _colorChannels;
};

