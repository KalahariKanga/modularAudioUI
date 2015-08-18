#pragma once
#include "SFML/graphics.hpp"
#include "ComponentView.h"

class SidePanel
{
	sf::RenderWindow* window;
	ComponentView* component;
public:
	SidePanel(sf::RenderWindow* window);
	~SidePanel();

	void setFocusedComponent(ComponentView* cv);
	void update();
	void onEvent(sf::Event ev);
	sf::Rect<int> rectangle;
};

