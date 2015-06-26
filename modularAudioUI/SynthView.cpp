#include "SynthView.h"


SynthView::SynthView()
{
	window.create(sf::VideoMode(640, 480), "UI");
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
	window.clear();
	sf::Event event;
	while (window.pollEvent(event))
	{
		for (auto c : components)
			(c.second)->onEvent(&event);
	}
	for (auto c : components)
		(c.second)->update();
	for (auto c : links)
		c->update();
	
	window.display();
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