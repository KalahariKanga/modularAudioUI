#include "ComponentView.h"

//sf::Font ComponentView::font;
ComponentView::ComponentView(std::string Name, sf::RenderWindow* win) : name(Name), window(win)
{
	x = rand() % 640;
	y = rand() % 480;
	w = 48;
	h = 64;
	
	font.loadFromFile("arial.ttf");
	nameText = new sf::Text();
	nameText->setFont(font);
	nameText->setColor(sf::Color::Blue);
	nameText->setCharacterSize(12);

	rectangle = new sf::RectangleShape();
	rectangle->setOutlineColor(sf::Color::Red);
	rectangle->setOutlineThickness(1);
}


ComponentView::~ComponentView()
{
	delete nameText;
	delete rectangle;
	for (auto p : parameters)
		delete (p.second);
}

void ComponentView::addParameter(std::string name)
{
	parameters[name] = new ParameterView(name);
}

void ComponentView::onEvent(sf::Event* ev)
{
	for (auto p : parameters)
	{
		(p.second)->onEvent(ev);
	}

	if (ev->type == sf::Event::MouseButtonPressed)
	{
		if (ev->mouseButton.x > x && ev->mouseButton.x < x + w)
			if (ev->mouseButton.y > y && ev->mouseButton.y < y + 8)
			{
				clicked = 1;
				mousexoffset = x - ev->mouseButton.x;
				mouseyoffset = y - ev->mouseButton.y;
			}
	}
	if (ev->type == sf::Event::MouseButtonReleased)
		clicked = 0;
	if (ev->type == sf::Event::MouseMoved)
	{
		if (clicked)
		{
			x = ev->mouseMove.x + mousexoffset;
			y = ev->mouseMove.y + mouseyoffset;
		}
	}
}

void ComponentView::update()
{
	rectangle->setSize(sf::Vector2f(w, h));
	rectangle->setPosition(x, y);

	nameText->setString(name);
	nameText->setPosition(sf::Vector2f(x, y));
	
	window->draw(*rectangle);
	window->draw(*nameText);
}

void ComponentView::print()
{
	std::cout << name << "\n";
	for (auto p : parameters)
	{
		std::cout << "     -" << (p.second)->name << "\n";
	}
}