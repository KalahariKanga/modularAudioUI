#pragma once
#include "bass.h"
#include "ComponentView.h"
#include <thread>
class SynthView
{
	Synth* s;
	std::thread* audioThread;
	std::map<std::string, ComponentView*> components;
	HSTREAM stream;

	void addComponentView(std::string name);
public:
	SynthView();
	~SynthView();
	bool loadPatch(std::string fname);
	void addComponent(std::string name, std::string type);
	sf::RenderWindow window;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Image image;

	void update();
	void print();
	void audioUpdate();

	void playNoteDuration(Note note, float seconds);
};

