#include "SynthView.h"


SynthView::SynthView()
{
	s = new Synth();
	window.create(sf::VideoMode(640, 480), "UI");
	image.create(640, 480);
	
	BASS_Init(-1, SAMPLE_RATE, 0, 0, NULL);
	BASS_SetConfig(BASS_CONFIG_BUFFER, 128);
	BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 10);
	stream = BASS_StreamCreate(SAMPLE_RATE, 1, 0, STREAMPROC_PUSH, NULL);
	BASS_ChannelPlay(stream, 0);

	audioThread = new std::thread(&SynthView::audioUpdate, this);
}


SynthView::~SynthView()
{
}

void SynthView::addComponentView(std::string name)
{
	components[name] = new ComponentView(name, &image);
	//populate parameters
	auto list = s->getComponent(name)->getParameterList();
	for (auto str : list)
		components[name]->addParameter(str);
}

void SynthView::addAudioLinkView(std::string from, std::string to)
{
	links.push_back(new LinkView(&image, components.at(from), components.at(to)));
}

bool SynthView::loadPatch(std::string fname)
{
	
	s->loadPatch(fname);
	//return -1;

	auto list = s->getComponentList();
	for (auto str : list)
	{
		//add component
		std::cout << str << "\n";
		addComponentView(str);
	}
	//add links
	for (auto str : list)
	{
		Component* c = s->getComponent(str);
		AudioComponent* a = dynamic_cast<AudioComponent*>(c);
		if (a)
			for (auto l : a->ins)
				addAudioLinkView(l->name, a->name);
	}
	return 0;
}

void SynthView::addComponent(std::string name, std::string type)
{
	s->addComponent(name, type);
	addComponentView(name);
}

void SynthView::addAudioLink(std::string from, std::string to)
{
	s->linkAudio(from, to);
	addAudioLinkView(from, to);
}

void SynthView::update()
{
	//audioUpdate();
	image.create(640, 480);
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

void SynthView::audioUpdate()
{
	while (window.isOpen())
	{
		s->update();
		while (BASS_StreamPutData(stream, NULL, 0) > 10)
			std::this_thread::sleep_for(std::chrono::milliseconds(5));

		BASS_StreamPutData(stream, (void*)s->getBuffer(), BUFFER_LENGTH*sizeof(short));
	}
}

void SynthView::playNoteDuration(Note note, float seconds)
{
	s->playNoteDuration(note, seconds);
}