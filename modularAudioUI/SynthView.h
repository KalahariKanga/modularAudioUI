#pragma once
#include "bass.h"
#include "ComponentView.h"
#include "LinkView.h"
#include <thread>
class SynthView 
{
#ifdef AUDIO
	Synth* s;
#endif
	std::thread* audioThread;
	std::map<std::string, ComponentView*> components;
	std::vector<LinkView*> links;
	HSTREAM stream;

	void addComponentView(std::string name);
	void addAudioLinkView(std::string from, std::string to);
public:
	SynthView();
	~SynthView();
	bool loadPatch(std::string fname);
	void addComponent(std::string name, std::string type);
	void addAudioLink(std::string from, std::string to);
	sf::RenderWindow window;
	/*sf::Sprite sprite;
	sf::Texture texture;
	sf::Image image;*/

	void update();
	void print();
	void audioUpdate();

	void playNoteDuration(Note note, float seconds);
};

