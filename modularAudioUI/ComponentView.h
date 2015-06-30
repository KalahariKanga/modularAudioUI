#pragma once
#include "ParameterView.h"

class ComponentView 
{
	std::map<std::string, ParameterView*> parameters;
	sf::RenderWindow* window;
	int w, h;
	int mousexoffset = 0, mouseyoffset = 0;
	bool clicked = 0;

public:

	ComponentView(std::string name, sf::RenderWindow* w);
	~ComponentView();
	
	int x, y;

	std::string name;
	void addParameter(std::string name);

	void onEvent(sf::Event* e);
	void update();
	void print();


	sf::RectangleShape* rectangle;
	sf::Text* nameText;
	sf::Font font;
	//static sf::Font font;
};

