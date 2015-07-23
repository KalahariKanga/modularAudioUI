// modularAudioUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SynthView.h"
#define AUDIO

int main(int argc, _TCHAR* argv[])
{
	SynthView sv;
	//sv.loadPatch("skies.patch");
	//sv.addComponent("name", "LFO");
	sv.print();

	while (1)
	{
		sv.update();
		if (rand() % 100 == 0)
			sv.playNoteDuration(Note(c3, 100), 1);
	}

	
	return 0;
}

