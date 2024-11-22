#include "NEA Stealth Game.h"

class StealthGame : public Application {

	void applicationReady() override{
		
	}

	void applicationPhysicsUpdate(float delta) override {
		cout << "fixed" << endl;
	}

	void applicationUpdate(float delta) override{
		cout << "regular" << endl;
	}

};

int main(int argc, char* argv[])
{
	StealthGame* game = new StealthGame();
	game->launch();
	delete game;

	return 0;
}