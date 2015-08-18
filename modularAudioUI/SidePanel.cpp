#include "SidePanel.h"


SidePanel::SidePanel(sf::RenderWindow* w)
{
	window = w;
	rectangle.left = 0;
	rectangle.width = 128;
	rectangle.top = 0;
	rectangle.height = w->getSize().y;
}


SidePanel::~SidePanel()
{
}

void SidePanel::setFocusedComponent(ComponentView* cv)
{
	component = cv;
}

void SidePanel::update()
{
	if (!component)
		return;

	for (auto p : component->parameters)
	{
		ParameterView* pv = p.second;
		pv->x = pv->xoffset;
		pv->y = pv->yoffset;
		pv->update();
	}
}

void SidePanel::onEvent(sf::Event ev)
{
	if (!component)
		return;

	for (auto p : component->parameters)
	{
		p.second->onEvent(&ev);
	}

}