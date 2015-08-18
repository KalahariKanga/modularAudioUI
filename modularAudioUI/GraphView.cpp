#include "GraphView.h"


GraphView::GraphView(Synth* synth, sf::RenderWindow* w)
{
	
	window = w;
	s = synth;
	state = nextState = STATE_DEFAULT;
	
	addComponentView("output");

	rectangle.left = 128;
	rectangle.width = w->getSize().x - 128;
	rectangle.top = 0;
	rectangle.height = w->getSize().y;

}


GraphView::~GraphView()
{
	for (auto c : links)
		delete c;
	for (auto c : components)
		delete c.second;
}

void GraphView::addComponentView(std::string name)
{
	components[name] = new ComponentView(name, window);
	components[name]->s = s;
	//populate parameters
#ifdef AUDIO
	auto list = s->getComponent(name)->getParameterList();
	for (auto str : list)
		components[name]->addParameter(str);
#endif
}

void GraphView::addAudioLinkView(std::string from, std::string to)
{
	links.push_back(new LinkView(window, components.at(from), components.at(to)));
}

ComponentView* GraphView::getComponentAtPosition(int x, int y)
{
	ComponentView* cv = nullptr;
	for (auto c : components)
	{
		if ((c.second)->pointInside(x, y))
			cv = c.second;
	}
	return cv;
}

void GraphView::addComponent(std::string name, std::string type)
{
	if (type == "" || name == "")
		return;
#ifdef AUDIO
	s->addComponent(name, type);
#endif
	addComponentView(name);
}

void GraphView::addAudioLink(std::string from, std::string to)
{
#ifdef AUDIO
	s->linkAudio(from, to);
#endif
	addAudioLinkView(from, to);
}

void GraphView::update()
{
	for (auto c : components)
		(c.second)->update();
	for (auto c : links)
		c->update();
}

void GraphView::onEvent(sf::Event ev)
{
	for (auto c : components)
		(c.second)->onEvent(&ev);

	if (ev.type == sf::Event::KeyPressed)
	{
		if (ev.key.code == sf::Keyboard::Space)
		{
			componentTypeBox = new OptionBox(s->getComponentTypesList());
			std::string type = componentTypeBox->get();//blocking
			addComponent(type, type);
		}
		if (ev.key.code == sf::Keyboard::L)
			nextState = STATE_AUDIO_SELECT_FIRST;
	}

	if (ev.type == sf::Event::MouseButtonPressed)
	{
		if (rectangle.contains(ev.mouseButton.x, ev.mouseButton.y))
		{
			if (state == STATE_DEFAULT)
			{
				activeComponent = getComponentAtPosition(ev.mouseButton.x, ev.mouseButton.y);
			}
			if (state == STATE_AUDIO_SELECT_FIRST)
			{
				//find which component was clicked
				lastSelectedComponent = getComponentAtPosition(ev.mouseButton.x, ev.mouseButton.y);
				if (lastSelectedComponent)
					nextState = STATE_AUDIO_SELECT_SECOND;
				else
					nextState = STATE_DEFAULT;
			}
			if (state == STATE_AUDIO_SELECT_SECOND)
			{
				//find which component was clicked
				ComponentView* cv = getComponentAtPosition(ev.mouseButton.x, ev.mouseButton.y);
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
	state = nextState;
}

ComponentView* GraphView::getActiveComponent()
{
	return activeComponent;
}