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

	
}


SynthView::~SynthView()
{
	BASS_StreamFree(stream);
	BASS_Stop();
	BASS_Free();
	for (auto c : links)
		delete c;
	for (auto c : components)
		delete c.second;
	delete s;
	delete audioThread;
}

void SynthView::addComponentView(std::string name)
{
	components[name] = new ComponentView(name, &window);

	//populate parameters
#ifdef AUDIO
	auto list = s->getComponent(name)->getParameterList();
	for (auto str : list)
		components[name]->addParameter(str);
#endif
}

void SynthView::addAudioLinkView(std::string from, std::string to)
{
	links.push_back(new LinkView(&window, components.at(from), components.at(to)));
}

ComponentView* SynthView::getComponentAtPosition(int x, int y)
{
	ComponentView* cv = nullptr;
	for (auto c : components)
	{
		if ((c.second)->pointInside(x, y))
			cv = c.second;
	}
	return cv;
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
		addComponentView(str);
	}
	//add links
	for (auto str : *list)
	{
		Component* c = s->getComponent(str);
		AudioComponent* a = dynamic_cast<AudioComponent*>(c);
		if (a)
			for (auto l : a->ins)
				addAudioLinkView(l->name, a->name);
	}
#endif
	return 0;
}

void SynthView::addComponent(std::string name, std::string type)
{
	if (type == "" || name == "")
		return;
#ifdef AUDIO
	s->addComponent(name, type);
#endif
	addComponentView(name);
}

void SynthView::addAudioLink(std::string from, std::string to)
{
#ifdef AUDIO
	s->linkAudio(from, to);
#endif
	addAudioLinkView(from, to);
}

void SynthView::update()
{
	//audioUpdate();
	nextState = state;
	window.clear();
	sf::Event event;
	while (window.pollEvent(event))
	{
		for (auto c : components)
			(c.second)->onEvent(&event);
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				componentTypeBox = new OptionBox(s->getComponentTypesList());
				std::string type = componentTypeBox->get();//blocking
				addComponent(type, type);
			}
			if (event.key.code == sf::Keyboard::L)
				nextState = STATE_AUDIO_SELECT_FIRST;
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (state == STATE_AUDIO_SELECT_FIRST)
			{
				//find which component was clicked
				lastSelectedComponent = getComponentAtPosition(event.mouseButton.x, event.mouseButton.y);
				if (lastSelectedComponent)
					nextState = STATE_AUDIO_SELECT_SECOND;
				else
					nextState = STATE_DEFAULT;
			}
			if (state == STATE_AUDIO_SELECT_SECOND)
			{
				//find which component was clicked
				ComponentView* cv = getComponentAtPosition(event.mouseButton.x, event.mouseButton.y);
				if (cv)
				{
					if (cv != lastSelectedComponent)
					{
						//two different components selected
						addAudioLink(lastSelectedComponent->name, cv->name);
						nextState = STATE_DEFAULT;
					}
					else
						nextState = STATE_AUDIO_SELECT_SECOND; //same component twice
				}
				else
					nextState = STATE_DEFAULT;
			}
		}
	}
	for (auto c : components)
		(c.second)->update();
	for (auto c : links)
		c->update();
	
	window.display();
	state = nextState;
}

void SynthView::print()
{
	for (auto c : components)
	{
		(c.second)->print();
	}
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