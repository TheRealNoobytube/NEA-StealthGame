#pragma once
#include "SDL.h"
#include "../Nodes/Node.h"

class SceneTree {

private:
	Node* root;
	Node* currentScene;

	SDL_Renderer* renderer;
	std::string basePath;

public:
	SceneTree(Node* mainScene, SDL_Renderer* renderer, std::string basePath = SDL_GetBasePath());
	Node* getRoot();
	SDL_Renderer* getRenderer();
	std::string getBasePath();

	void readyNodes(Node* current);
	void updateNodes(Node* current, float delta);
	void physicsUpdateNodes(Node* current, float fixedDelta);

	void deleteScene(Node* current);
	void changeScene(Node* newScene);
	Node* getCurrentScene();
};