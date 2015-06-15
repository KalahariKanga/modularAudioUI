// modularAudioUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SynthView.h"


int _tmain(int argc, _TCHAR* argv[])
{
	SynthView sv;
	sv.addComponent("osc", "SimpleOscillator");
	sv.print();




	system("pause");
	return 0;
}

