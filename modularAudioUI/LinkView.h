#pragma once
#include "ComponentView.h"
#include "SFML/graphics.hpp"
#include "Draw.h"
class LinkView 
{

	sf::RenderWindow* window;

public:
	LinkView(sf::RenderWindow* w, ComponentView* a, ComponentView* b);
	~LinkView();
	//std::string from, to;
	ComponentView *from, *to;
	void update();
	sf::VertexArray line;
};

