#include "OptionBox.h"


OptionBox::OptionBox(std::vector<std::string> list) : options(list)
{
	font.loadFromFile("arial.ttf");
	optionsCount = list.size();
	height = buttonHeight * optionsCount;
	
	
	int i = 0;
	for (auto c : options)
	{
		sf::Text* t = new sf::Text(c,font,15);
		t->setPosition(sf::Vector2f(8, i*buttonHeight));
		optionText.push_back(t);
		i++;
	}
	window.create(sf::VideoMode(width, height), "");
}


OptionBox::~OptionBox()
{
	for (auto c : optionText)
		delete c;
}

std::string OptionBox::get()
{
	sf::Event event;
	std::string result = "";
	while (!quit)
	{
		window.clear();
		for (auto c : optionText)
			window.draw(*c);
		window.display();
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonReleased)
			{
				int n = event.mouseButton.y / buttonHeight;
				if (n >= 0 && n < optionsCount)
				{
					result = options[n];
					quit = 1;
					break;
				}
			}
			if (event.type == sf::Event::Closed)
			{
				quit = 1;
				break;
			}
		}

		
	}
	window.close();
	return result;
}