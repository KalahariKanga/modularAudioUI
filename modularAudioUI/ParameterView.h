#pragma once
#include "Synth.h"
#include <iostream>
class ParameterView
{
public:
	ParameterView(std::string name);
	~ParameterView();

	std::string componentName;
	std::string name;
};

