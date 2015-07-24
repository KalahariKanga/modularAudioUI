#pragma once
#include "Synth.h"
#include <iostream>
#include "SFML/graphics.hpp"
#include "Draw.h"
#define AUDIO
class ParameterView
{
	sf::RenderWindow* window;
	void setParameter(float value);
public:
	ParameterView(std::string name, sf::RenderWindow* w);
	~ParameterView();
	Synth* s;
	int x, y, xoffset, yoffset;
	int h, w;
	int pos;
	std::string componentName;
	std::string name;

	void onEvent(sf::Event* ev);
	void update();
	sf::Font font;
	sf::Text* nameText;
	sf::RectangleShape* rect;
};

