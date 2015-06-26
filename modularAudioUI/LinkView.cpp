#include "LinkView.h"


LinkView::LinkView(sf::RenderWindow* w, ComponentView* a, ComponentView* b) : window(w)
{
	from = a;
	to = b;
}


LinkView::~LinkView()
{
}

void LinkView::update()
{
	line.setPrimitiveType(sf::PrimitiveType::Lines);
	line.clear();
	line.append(sf::Vertex(sf::Vector2f(from->x, from->y)));
	line.append(sf::Vertex(sf::Vector2f(to->x, to->y)));
	window->draw(line);
}