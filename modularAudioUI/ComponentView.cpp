#include "ComponentView.h"


ComponentView::ComponentView(std::string Name, sf::Image* i) : name(Name), image(i)
{
}


ComponentView::~ComponentView()
{
}

void ComponentView::addParameter(std::string name)
{
	parameters[name] = new ParameterView(name);
}

void ComponentView::update()
{
	Draw::setColour(sf::Color::Red);
	Draw::rectangle(image, 32, 32, 64, 48);
}

void ComponentView::print()
{
	std::cout << name << "\n";
	for (auto p : parameters)
	{
		std::cout << "     -" << (p.second)->name << "\n";
	}
}