// modularAudioUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SynthView.h"


int _tmain(int argc, _TCHAR* argv[])
{
	SynthView sv;
	sv.loadPatch("sine.patch");
	sv.print();

	while (1)
	{
		sv.update();
		if (rand() % 100 == 0)
			sv.playNoteDuration(Note(c3, 100), 1);
	}

	return 0;
}

