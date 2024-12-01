#pragma once
#include "SDL.h"
#include "../Nodes/Node.h"


class SceneTree {

private:
	Node* root;
	SDL_Renderer* renderer;

public:
	SceneTree(Node* root, SDL_Renderer* renderer);

	Node* getRoot();
	SDL_Renderer* getRenderer();

	void readyNodes(Node* current);
	void updateNodes(Node* current, float delta);
	void physicsUpdateNodes(Node* current, float fixedDelta);
};