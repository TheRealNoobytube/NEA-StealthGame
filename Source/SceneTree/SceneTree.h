#pragma once
#include "SDL.h"
#include "Source/Nodes/Node.h"

class SceneTree {

private:
	Node* root;
	Node* currentScene;
	Node* nextScene = nullptr;

	List<Node*> queuedForDeletion;

	SDL_Renderer* renderer;
	std::string basePath;

	Vector2D viewportSize = Vector2D(0,0);

	//input buffers
	const int KEYBUFFERSIZE = SDL_NUM_SCANCODES;
	bool keysPressed[SDL_NUM_SCANCODES] = { false }; //322 is how many possible keys SDL can detect input for
	bool keysJustPressed[SDL_NUM_SCANCODES] = { false };
	bool keysReleased[SDL_NUM_SCANCODES] = { false };

	const int MOUSEBUFFERSIZE = 4;
	bool mouseButtonsPressed[4] = { false }; //only want to take into account 4 possible kinds of mouse presses
	bool mouseButtonsJustPressed[4] = { false };
	bool mouseButtonsReleased[4] = { false };

public:
	SceneTree(Node* mainScene, SDL_Renderer* renderer, Vector2D viewportSize, std::string basePath = SDL_GetBasePath());
	Node* getRoot();
	SDL_Renderer* getRenderer();
	std::string getBasePath();

	void readyNodes(Node* current);
	void updateNodes(Node* current, float delta);
	void physicsUpdateNodes(Node* current, float fixedDelta);
	
	void enqueueForDeletion(Node* node);
	void freeNodes();

	void changeScene(Node* newScene);
	void setCurrentScene();
	Node* getCurrentScene();
	bool requestedSceneChange();

	Vector2D getRenderScale();
	Vector2D getViewportSize();

	void handleInput(SDL_Event& event);

	void resetInputBuffers();

	bool isKeyPressed(int key);
	bool isKeyJustPressed(int key);
	bool isKeyReleased (int key);

	bool isMouseButtonPressed(int button);
	bool isMouseButtonJustPressed(int button);
	bool isMouseButtonReleased(int button);


};