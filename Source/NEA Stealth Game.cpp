#include "NEA Stealth Game.h"
#include "Scenes/MainMenu.h"

class StealthGame : public Application {

	std::string filepath = getBasePath() + "..\\Fonts\\OpenSans-VariableFont_wdth,wght.ttf";

	SceneTree* sceneTree = nullptr;
	MainMenu* currentScene = new MainMenu("MainMenu");


	void applicationReady() override{
		sceneTree = new SceneTree(currentScene, getRenderer(), getBasePath());
		//Button* button = new Button();
		//currentScene->addChild(button);
	}

	void applicationPhysicsUpdate(float fixedDelta) override {
		sceneTree->physicsUpdateNodes(sceneTree->getRoot(), fixedDelta);
	}

	void applicationUpdate(float delta) override{
		sceneTree->updateNodes(sceneTree->getRoot(), delta);

		//delete all the nodes cleared for deletion once the frame is complete
		//have to queue until end of frame because some Nodes may still need to access a Node the frame before it gets deleted
		//deleting a Node midframe is not very intuitive and usually the source of a lot of glitches
		if (!sceneTree->getQueuedForDeletion()->isEmpty()) {
			for (int i = 0; i < sceneTree->getQueuedForDeletion()->getSize(); i++) {
				sceneTree->freeNodes(sceneTree->getQueuedForDeletion()->get(i));
			}
			sceneTree->getQueuedForDeletion()->clear();
		}

		//reset the input buffers because otherwise it will just press or release every frame, which isn't correct
		sceneTree->resetInputBuffers();
	}

	void handleInput(SDL_Event& event) override{
		sceneTree->handleInput(event);
	}


	void onApplicationExited() {
		delete sceneTree;
	}

};


int main(int argc, char* argv[])
{
	std::cout << "\n";
	StealthGame* game = new StealthGame();
	game->launch();
	delete game;

	return 0;
}