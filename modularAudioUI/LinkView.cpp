#include "LinkView.h"


LinkView::LinkView(sf::Image* i, ComponentView* a, ComponentView* b) : image(i)
{
	from = a;
	to = b;
}


LinkView::~LinkView()
{
}

void LinkView::update()
{
	Draw::line(image, from->x, from->y, to->x, to->y);
}