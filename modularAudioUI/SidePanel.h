#pragma once
#include "SFML/graphics.hpp"
#include "ComponentView.h"

class SidePanel
{
public:
	SidePanel();
	~SidePanel();

	void update(ComponentView* component);
};

