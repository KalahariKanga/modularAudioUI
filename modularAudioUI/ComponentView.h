#pragma once
#include "ParameterView.h"
class ComponentView
{
	std::map<std::string, ParameterView*> parameters;
public:
	ComponentView(std::string name);
	~ComponentView();
	
	std::string name;
	void addParameter(std::string name);


	void print();
};

