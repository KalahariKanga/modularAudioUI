#include "SidePanel.h"


SidePanel::SidePanel()
{
}


SidePanel::~SidePanel()
{
}

void SidePanel::update(ComponentView* component)
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