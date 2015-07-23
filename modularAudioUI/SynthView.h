#pragma once
#include "bass.h"
#include "ComponentView.h"
#include "LinkView.h"
#include "OptionBox.h"
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
	ComponentView* getComponentAtPosition(int x, int y);
	ComponentView* lastSelectedComponent = nullptr;
public:
	SynthView();
	~SynthView();
	bool loadPatch(std::string fname);
	void addComponent(std::string name, std::string type);
	void addAudioLink(std::string from, std::string to);
	
	sf::RenderWindow window;
	
	enum State
	{
		STATE_DEFAULT, STATE_AUDIO_SELECT_FIRST, STATE_AUDIO_SELECT_SECOND
	} state, nextState;
	void update();
	void print();
	void audioUpdate();
	
	void playNoteDuration(Note note, float seconds);
	OptionBox* componentTypeBox;
};

