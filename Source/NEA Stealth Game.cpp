#include "NEA Stealth Game.h"

class StealthGame : public Application {

	
	SceneTree* sceneTree = nullptr;

	Sprite* sprite;
	Node* node = new Node();

	void applicationReady() override{
		sceneTree = new SceneTree(node, getRenderer(), getBasePath());

		Texture* texture = new Texture(getRenderer(), getBasePath() + "../Assets/testsprite.png");
		sprite = new Sprite(texture);

		SDL_RenderSetScale(getRenderer(), 2, 2);
	}


	void applicationPhysicsUpdate(float fixedDelta) override {
		sceneTree->physicsUpdateNodes(sceneTree->getRoot(), fixedDelta);
		sprite->posX += 1;
	}

	int timer = 0;

	void applicationUpdate(float delta) override{
		sceneTree->updateNodes(sceneTree->getRoot(), delta);

		timer++;

		if (timer > 10) {
			timer = 0;

			if (sceneTree->getCurrentScene() == node) {
				sceneTree->changeScene(sprite);
			}
			else if (sceneTree->getCurrentScene() == sprite) {
				sceneTree->changeScene(node);
			}
			

		}
	}

	void onApplicationExited() {
		delete sceneTree;
	}

};


int main(int argc, char* argv[])
{
	StealthGame* game = new StealthGame();
	game->launch();
	delete game;

	return 0;
}