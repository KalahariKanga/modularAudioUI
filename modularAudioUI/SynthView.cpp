#include "SynthView.h"


SynthView::SynthView()
{
	s = new Synth();
	window.create(sf::VideoMode(640, 480), "UI");
	image.create(640, 480);
	
}


SynthView::~SynthView()
{
}

bool SynthView::loadPatch(std::string fname)
{
	
	s->loadPatch(fname);
	//return -1;
	auto list = s->getComponentList();
	for (auto str : list)
	{
		//add component
	}
	return 0;
}

void SynthView::addComponent(std::string name, std::string type)
{
	//assume model and view sync'd
	s->addComponent(name, type);
	components[name] = new ComponentView(name,&image);
	//populate parameters
	auto list = s->getComponent(name)->getParameterList();
	for (auto str : list)
		components[name]->addParameter(str);
}

void SynthView::update()
{
	for (auto c : components)
		(c.second)->update();
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	window.draw(sprite);
	window.display();
}

void SynthView::print()
{
	for (auto c : components)
	{
		(c.second)->print();
	}
}