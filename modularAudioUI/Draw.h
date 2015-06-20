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
};

