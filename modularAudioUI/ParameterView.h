#pragma once
#include "Synth.h"
#include <iostream>
#include "SFML/graphics.hpp"
#include "Draw.h"
#define AUDIO
class ParameterView
{
public:
	ParameterView(std::string name);
	~ParameterView();

	std::string componentName;
	std::string name;

	void onEvent(sf::Event* ev);
};

