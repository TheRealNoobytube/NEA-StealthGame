﻿#include "NEA Stealth Game.h"


class StealthGame : public Application {

	void ApplicationReady() override{

	}

	void ApplicationUpdate() override{

	}

};

int main(int argc, char* argv[])
{
	StealthGame* game = new StealthGame();
	game->Launch();
	delete game;

	return 0;
}