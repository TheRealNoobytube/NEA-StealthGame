#include "SceneTree.h"

SceneTree::SceneTree(Node* mainScene, SDL_Renderer* renderer, std::string basePath) {
	this->root = new Node("Root");
	this->currentScene = mainScene;

	root->setSceneTree(this); //root doesn't have any parents because its at the top of the tree, so we don't need to set its parent here
	root->addChild(currentScene);
	root->ready();

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

void SceneTree::updateNodes(Node* current, float delta) { //pre-order depth first traversal - more intuitive since nodes
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


void SceneTree::changeScene(Node* newScene) {
	root->removeChild(this->currentScene);
	this->currentScene = newScene;
	root->addChild(this->currentScene);
}

Node* SceneTree::getCurrentScene() {
	return this->currentScene;
}

void SceneTree::addToQueueForDeletion(Node* node) {
	if (this->queuedForDeletion.find(node) == -1) { //dont want to delete the same node more than once
		this->queuedForDeletion.add(node);
	}
}

List<Node*>* SceneTree::getQueuedForDeletion() {
	return &queuedForDeletion;
}

void SceneTree::freeNodes(Node* current) {
	for (int i = 0; i < current->getChildCount(); i++) {
		freeNodes(current->getChild(i));
	}
	delete current;
}

Vector2D SceneTree::getRenderScale() {
	float x;
	float y;
	SDL_RenderGetScale(getRenderer(), &x, &y);
	return Vector2D(x, y);
}



//keyboard key pressed functions
bool SceneTree::isKeyPressed(int key) {
	return keysPressed[key];
}
bool SceneTree::isKeyJustPressed(int key) {
	return keysJustPressed[key];
}
bool SceneTree::isKeyReleased(int key) {
	return keysReleased[key];
}

//mouse button pressed functions
bool SceneTree::isMouseButtonPressed(int button) {
	return mouseButtonsPressed[button];
}
bool SceneTree::isMouseButtonJustPressed(int button) {
	return mouseButtonsJustPressed[button];
}
bool SceneTree::isMouseButtonReleased(int button) {
	return mouseButtonsReleased[button];
}

void SceneTree::resetInputBuffers() {
	for (int i = 0; i < KEYBUFFERSIZE; i++) {
		keysJustPressed[i] = false;
		keysReleased[i] = false;
	}
	for (int i = 0; i < MOUSEBUFFERSIZE; i++) {
		mouseButtonsJustPressed[i] = false;
		mouseButtonsReleased[i] = false;
	}
}

void SceneTree::handleInput(SDL_Event& event) {
	Uint32 key = event.key.keysym.scancode;
	Uint8 button = event.button.button;

	if (event.key.repeat != 0) { //make sure repeat scancodes aren't processed, will mess with the buffers
		return;
	}

	switch (event.type) {

	case SDL_KEYDOWN: 
		keysJustPressed[key] = true;
		keysPressed[key] = true;
		keysReleased[key] = false;
		break;

	case SDL_KEYUP: 
		keysReleased[key] = true;
		keysPressed[key] = false;
		break;

	case SDL_MOUSEBUTTONDOWN: 
		mouseButtonsJustPressed[button] = true;
		mouseButtonsPressed[button] = true;
		mouseButtonsReleased[button] = false;
		break;

	case SDL_MOUSEBUTTONUP:
		mouseButtonsReleased[button] = true;
		mouseButtonsPressed[button] = false;
		break;
	}

}

