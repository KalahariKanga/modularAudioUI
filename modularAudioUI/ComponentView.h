#pragma once
#include "ParameterView.h"
class ComponentView
{
	std::map<std::string, ParameterView*> parameters;
	sf::Image* image;
public:
	ComponentView(std::string name, sf::Image* i);
	~ComponentView();
	
	std::string name;
	void addParameter(std::string name);

	void update();
	void print();
};

