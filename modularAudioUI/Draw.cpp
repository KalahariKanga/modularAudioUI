#include "Draw.h"

sf::Color Draw::colour = sf::Color::White;
Draw::Draw()
{
}


Draw::~Draw()
{
}

void Draw::setColour(sf::Color col)
{
	colour = col;
}

void Draw::rectangle(sf::Image* i, int x, int y, int w, int h, bool outline)
{
	if (outline)
	{
		for (int cx = 0; cx < w; cx++)
		{
			i->setPixel(x + cx, y, colour);
			i->setPixel(x + cx, y + h, colour);
		}
		for (int cy = 0; cy < h; cy++)
		{
			i->setPixel(x, y + cy, colour);
			i->setPixel(x + w, y + cy, colour);
		}
	}
	else
		for (int cx = 0; cx < w; cx++)
			for (int cy = 0; cy < h; cy++)
				i->setPixel(x + cx, y + cy, colour);
}
