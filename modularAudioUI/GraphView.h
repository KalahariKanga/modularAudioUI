#pragma once
#include "bass.h"
#include "ComponentView.h"
#include "LinkView.h"
#include "OptionBox.h"
class GraphView
{
	Synth* s;
	sf::RenderWindow* window;
	std::map<std::string, ComponentView*> components;
	std::vector<LinkView*> links;

	ComponentView* getComponentAtPosition(int x, int y);
	ComponentView* lastSelectedComponent = nullptr;
	ComponentView* activeComponent = nullptr;

	


public:
	GraphView(Synth* synth, sf::RenderWindow* window);
	~GraphView();

	void addComponentView(std::string name);
	void addAudioLinkView(std::string from, std::string to);
	void addComponent(std::string name, std::string type);
	void addAudioLink(std::string from, std::string to);

	enum State
	{
		STATE_DEFAULT, STATE_AUDIO_SELECT_FIRST, STATE_AUDIO_SELECT_SECOND
	} state, nextState;

	void update();
	void onEvent(sf::Event ev);

	ComponentView* getActiveComponent();

	OptionBox* componentTypeBox;

	sf::Rect<int> rectangle;
};

