#include "SynthView.h"


SynthView::SynthView()
{
	window.create(sf::VideoMode(640, 480), "UI");
	/*if (!ComponentView::font.loadFromFile("arial.ttf"))
		std::cout << "Font loading error\n";*/
#ifdef AUDIO
	s = new Synth();
	
	
	BASS_Init(-1, SAMPLE_RATE, 0, 0, NULL);
	BASS_SetConfig(BASS_CONFIG_BUFFER, 128);
	BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 10);
	stream = BASS_StreamCreate(SAMPLE_RATE, 1, 0, STREAMPROC_PUSH, NULL);
	BASS_ChannelPlay(stream, 0);

	audioThread = new std::thread(&SynthView::audioUpdate, this);
#endif
	graphview = new GraphView(s,&window);
	sidepanel = new SidePanel(&window);

}


SynthView::~SynthView()
{
	BASS_StreamFree(stream);
	BASS_Stop();
	BASS_Free();
	
	delete sidepanel;
	delete graphview;
	delete s;
	delete audioThread;

}

bool SynthView::loadPatch(std::string fname)
{
#ifdef AUDIO
	s->loadPatch(fname);

	//return -1;

	auto list = s->getComponentList();
	for (auto str : *list)
	{
		//add component
		std::cout << str << "\n";
		graphview->addComponentView(str);
	}
	//add links
	for (auto str : *list)
	{
		Component* c = s->getComponent(str);
		AudioComponent* a = dynamic_cast<AudioComponent*>(c);
		if (a)
			for (auto l : a->ins)
				graphview->addAudioLinkView(l->name, a->name);
	}
#endif
	return 0;
}

void SynthView::update()
{
	//audioUpdate();
	
	window.clear();
	sf::Event event;
	sidepanel->setFocusedComponent(graphview->getActiveComponent());
	while (window.pollEvent(event))
	{
		graphview->onEvent(event);
		sidepanel->onEvent(event);
	}
	sidepanel->update();
	graphview->update();
	window.display();
}

void SynthView::print()
{
	/*for (auto c : graphview.components)
	{
		(c.second)->print();
	}*/
}

void SynthView::audioUpdate()
{
#ifdef AUDIO
	while (window.isOpen())
	{
		s->update();
		while (BASS_StreamPutData(stream, NULL, 0) > 10)
			std::this_thread::sleep_for(std::chrono::milliseconds(5));

		BASS_StreamPutData(stream, (void*)s->getBuffer(), BUFFER_LENGTH*sizeof(short));
	}
#endif
}

void SynthView::playNoteDuration(Note note, float seconds)
{
#ifdef AUDIO
	s->playNoteDuration(note, seconds);
#endif
}

void SynthView::noteDown(Note note)
{
	s->noteDown(note);
}

void SynthView::noteUp(Note note)
{
	s->noteUp(note);
}