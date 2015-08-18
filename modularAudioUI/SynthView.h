#pragma once
#include "GraphView.h"
#include "OptionBox.h"
#include "SidePanel.h"
#include <thread>
class SynthView 
{
#ifdef AUDIO
	Synth* s;
#endif
	std::thread* audioThread;
	HSTREAM stream;

	GraphView* graphview;
	SidePanel* sidepanel;
public:
	SynthView();
	~SynthView();
	bool loadPatch(std::string fname);
	
	sf::RenderWindow window;
	
	void update();

	void print();
	void audioUpdate();
	
	void playNoteDuration(Note note, float seconds);
	void noteDown(Note note);
	void noteUp(Note note);
	
};

