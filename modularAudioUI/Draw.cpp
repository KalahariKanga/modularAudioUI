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
			point(i, x + cx, y);
			point(i, x + cx, y + h);
		}
		for (int cy = 0; cy < h; cy++)
		{
			point(i, x, y + cy);
			point(i, x + w, y + cy);
		}
	}
	else
		for (int cx = 0; cx < w; cx++)
			for (int cy = 0; cy < h; cy++)
				point(i, x + cx, y + cy);
}

void Draw::point(sf::Image* i, int x, int y)
{
	if (x >= 0 && x < i->getSize().x && y >= 0 && y < i->getSize().y)
		i->setPixel(x, y, colour);
}

void Draw::line(sf::Image* i, int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int dx1 = std::abs(dx);
	int dy1 = std::abs(dy);
	int px = 2 * dy1 - dx1;
	int py = 2 * dx1 - dy1;
	int x, y, xe, ye;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1;
			y = y1;
			xe = x2;
		}
		else
		{
			x = x2;
			y = y2;
			xe = x1;
		}
		point(i, x, y);
		for (int c = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0)
			{
				px = px + 2 * dy1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx>0 && dy>0))
				{
					y = y + 1;
				}
				else
				{
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
			point(i, x, y);
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}
		point(i, x, y);
		for (int c = 0; y < ye; i++)
		{
			y = y + 1;
			if (py <= 0)
			{
				py = py + 2 * dx1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx>0 && dy>0))
				{
					x = x + 1;
				}
				else
				{
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			point(i, x, y);
		}
	}
}
