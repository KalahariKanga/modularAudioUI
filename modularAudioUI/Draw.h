#pragma once
#include "sfml/graphics.hpp"
class Draw
{
	static sf::Color colour;
public:
	Draw();
	~Draw();
	
	static void setColour(sf::Color col);
	static void rectangle(sf::Image* i, int x, int y, int w, int h, bool outline = 1);
	static void point(sf::Image* i, int x, int y);
	static void line(sf::Image* i, int x1, int y1, int x2, int y2);
};

