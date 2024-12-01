#include "NEA Stealth Game.h"

class StealthGame : public Application {

	Node* root = new Node();
	SceneTree* sceneTree = nullptr;

	Sprite* sprite = new Sprite();

	void applicationReady() override{
		sceneTree = new SceneTree(root, getRenderer());

		Node* child1 = new Node();
		child1->setName("one");
		Node* child2 = new Node();
		child2->setName("two");

		root->setName("root");
		root->addChild(child1);
		root->addChild(child2);
		root->addChild(sprite);

		
	}

	void applicationPhysicsUpdate(float fixedDelta) override {
		sceneTree->physicsUpdateNodes(root, fixedDelta);
		sprite->posX += 1;
	}

	void applicationUpdate(float delta) override{
		sceneTree->updateNodes(root, delta);
	}

};




int main(int argc, char* argv[])
{
	StealthGame* game = new StealthGame();
	game->launch();
	delete game;

	return 0;
}