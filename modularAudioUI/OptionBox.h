#pragma once
#include "SFML/graphics.hpp"

class OptionBox
{
	sf::RenderWindow window;
	std::vector<std::string> options;
	
	const int width = 128;
	const int buttonHeight = 32;
	int height;
	bool quit = 0;
	int optionsCount = 0;
	std::vector<sf::Text*> optionText;
	sf::Font font;
public:
	OptionBox(std::vector<std::string> list);
	~OptionBox();
	std::string get();//could override ()
};

