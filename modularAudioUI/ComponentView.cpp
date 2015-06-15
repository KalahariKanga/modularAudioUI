#include "ComponentView.h"


ComponentView::ComponentView(std::string Name) : name(Name)
{
}


ComponentView::~ComponentView()
{
}

void ComponentView::addParameter(std::string name)
{
	parameters[name] = new ParameterView(name);
}



void ComponentView::print()
{
	std::cout << name << "\n";
	for (auto p : parameters)
	{
		std::cout << "     -" << (p.second)->name << "\n";
	}
}