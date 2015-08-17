#include "ParameterView.h"


ParameterView::ParameterView(std::string Name, sf::RenderWindow* win) : name(Name), window(win)
{
	font.loadFromFile("arial.ttf");

	nameText = new sf::Text();
	nameText->setFont(font);
	nameText->setColor(sf::Color::Green);
	nameText->setCharacterSize(16);

	rect = new sf::RectangleShape();
	
	w = 128;
	h = 32;
	xoffset = 4;
	
}


ParameterView::~ParameterView()
{
	delete nameText;
}

void ParameterView::setParameter(float value)
{
	s->setParameter(componentName, name, value);
	std::cout << "set " << name << " to " << value << "\n";
	std::cout << name << " is " << s->getParameter(componentName, name) << "\n";
}

void ParameterView::onEvent(sf::Event* ev)
{
	if (ev->type == sf::Event::MouseMoved)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			int mx = ev->mouseMove.x;
			int my = ev->mouseMove.y;
			if (mx > x && mx < x + w && my > y && my < y + h)
				setParameter((float)(mx - x) / w);
		}
	}
}

void ParameterView::update()
{
	yoffset = h * pos + 16;
	nameText->setString(name);
	nameText->setPosition(x,y);

	rect->setPosition(x, y);
	rect->setSize(sf::Vector2f(s->getParameter(componentName, name)*w, h));
	
	window->draw(*rect);
	window->draw(*nameText);
	
}