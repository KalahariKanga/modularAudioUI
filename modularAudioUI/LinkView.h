#pragma once
#include "ComponentView.h"
#include "SFML/graphics.hpp"
#include "Draw.h"
class LinkView 
{

	sf::Image* image;

public:
	LinkView(sf::Image* i, ComponentView* a, ComponentView* b);
	~LinkView();
	//std::string from, to;
	ComponentView *from, *to;
	void update();
};

