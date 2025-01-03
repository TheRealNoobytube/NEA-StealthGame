#include "NEA Stealth Game.h"
#include "Scenes/Menus/MainMenu/MainMenu.h"
#include "Scenes/Menus/AboutMenu/AboutMenu.h"

class StealthGame : public Application {

	std::string filepath = getBasePath() + "..\\Fonts\\OpenSans-VariableFont_wdth,wght.ttf";

	SceneTree* sceneTree = nullptr;

	MainMenu* currentScene;

	void applicationReady() override{
		currentScene = new MainMenu();
		sceneTree = new SceneTree(currentScene, getRenderer(), getViewportSize(), getBasePath());
	}

	void applicationPhysicsUpdate(float fixedDelta) override {
		sceneTree->physicsUpdateNodes(sceneTree->getRoot(), fixedDelta);
	}

	void applicationUpdate(float delta) override{
		sceneTree->updateNodes(sceneTree->getRoot(), delta);
		
		if (sceneTree->requestedSceneChange()) {
			sceneTree->setCurrentScene();
		}

		//reset the input buffers because otherwise it will just press or release every frame, which isn't correct
		sceneTree->resetInputBuffers();

		//delete all the Nodes cleared for deletion once the frame is complete
		//have to queue Nodes until end of frame because some Nodes may still need to access a Node the frame before it gets deleted
		//deleting a Node midframe is not very intuitive and usually the source of a lot of glitches
		sceneTree->freeNodes();
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