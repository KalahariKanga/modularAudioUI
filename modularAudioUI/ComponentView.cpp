#include "ComponentView.h"


ComponentView::ComponentView(std::string Name, sf::Image* i) : name(Name), image(i)
{
	x = rand() % 640;
	y = rand() % 480;
	w = 48;
	h = 64;
}


ComponentView::~ComponentView()
{
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
	Draw::setColour(sf::Color::Red);
	Draw::rectangle(image, x, y, w, h);
}

void ComponentView::print()
{
	std::cout << name << "\n";
	for (auto p : parameters)
	{
		std::cout << "     -" << (p.second)->name << "\n";
	}
}