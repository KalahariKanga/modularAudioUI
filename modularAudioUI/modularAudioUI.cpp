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

	int t = 0;
	while (1)
	{
		t++;
		sv.update();
		if (t % 1000 == 0)
			sv.noteDown(Note(c3, 100));
		if (t % 1000 == 500)
			sv.noteUp(Note(c3, 100));
	}

	
	return 0;
}

