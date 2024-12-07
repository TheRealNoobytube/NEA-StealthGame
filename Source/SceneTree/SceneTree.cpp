#include "SceneTree.h"

SceneTree::SceneTree(Node* mainScene, SDL_Renderer* renderer, std::string basePath) {
	this->root = new Node("Root");
	this->currentScene = mainScene;

	root->addChild(currentScene);

	root->setSceneTree(this); //root doesn't have any parents because its at the top of the tree, so we don't need to set its parent here
	this->renderer = renderer;
	this->basePath = basePath;
}


Node* SceneTree::getRoot() {
	return this->root;
}

SDL_Renderer* SceneTree::getRenderer() {
	return this->renderer;
}

std::string SceneTree::getBasePath() {
	return this->basePath;
}


void SceneTree::readyNodes(Node* current) { //post-order depth first traversal - makes sure all children are ready for use for the parent node
	for (int i = 0; i < current->getChildCount(); i++) {
		readyNodes(current->getChild(i));
	}
	current->ready();
}

void SceneTree::updateNodes(Node * current, float delta) { //pre-order depth first traversal - more intuitive since nodes
	current->update(delta);								   //updated in the order they appear in the tree

	for (int i = 0; i < current->getChildCount(); i++) {
		updateNodes(current->getChild(i), delta);
	}
}

void SceneTree::physicsUpdateNodes(Node* current, float fixedDelta) { //pre-order depth first traversal - more intuitive since nodes
	current->physicsUpdate(fixedDelta);											  //updated in the order they appear in the tree

	for (int i = 0; i < current->getChildCount(); i++) {
		physicsUpdateNodes(current->getChild(i), fixedDelta);
	}
}

void SceneTree::deleteScene(Node* current) {
	for (int i = 0; i < current->getChildCount(); i++) {
		deleteScene(current->getChild(i));
	}
	delete current;
}

void SceneTree::changeScene(Node* newScene) {
	root->removeChild(this->currentScene);
	this->currentScene = newScene;
	root->addChild(this->currentScene);
}

Node* SceneTree::getCurrentScene() {
	return this->currentScene;
}