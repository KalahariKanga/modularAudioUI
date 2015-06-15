#pragma once
#include "ComponentView.h"
class SynthView
{
	Synth* s;
	std::map<std::string, ComponentView*> components;
public:
	SynthView();
	~SynthView();
	bool loadPatch(std::string fname);
	void addComponent(std::string name, std::string type);

	void print();
};

