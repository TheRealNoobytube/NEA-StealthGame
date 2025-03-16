#pragma once
#include "Source/Application/Color.h"
#include "Source/Application/Data Structures/List.h"
#include "Source/Application/Vector2D.h"
#include "Source/Application/Signal.h"


#include <algorithm>
#include <iostream>
#include <string>

class SceneTree; //forward declaration of SceneTree because SceneTree includes Node, but Node hasn't been defined yet
                 //this would lead to dependency issues and a bunch of errors
                 //first we define Node and then we can include SceneTree so no dependencies are missing


class Node {
protected:
	inline static int ID = 0; //gets incremented whenever a new Node is created
							  //static so space for this var is only allocated once for the lifetime of the program
							  //means all Nodes share the same ID variable

private:
	SceneTree* sceneTree = nullptr;
	Node* parent;
	List<Node*> children;

	std::string name;

	bool readied = false;

public:
	int id;

	bool ignoreRenderOffset = false;

	Node(std::string name = "Node");
	virtual ~Node();


	virtual void ready();
	virtual void update(float delta);
	virtual void physicsUpdate(float fixedDelta);

	void sceneTreeEntered(SceneTree* sceneTree);
	void sceneTreeExited();
	virtual void onSceneTreeExited();

	void requestReady();

	bool isReady();

	bool hasChild(std::string name);
	bool hasChild(Node* node);
	void removeChild(std::string name);
	void removeChild(Node* node);
	void removeChild(int index);
	void addChild(Node* node);
	Node* getChild(std::string);
	Node* getChild(int index);
	List<Node*> getChildren();
	int getChildCount();

	Node* getParent();
	SceneTree* getSceneTree();
	void setSceneTree(SceneTree* sceneTree);

	void setName(std::string name);
	std::string getName();

	void queueFree();


	float linearInterpolate(float start, float end, float t);

	Vector2D getMousePosition();

	void drawRect(Vector2D position, Vector2D size, Color color = Color(0,0,0));
	void drawLine(Vector2D startPoint, Vector2D endPoint, Color color = Color(0, 0, 0));

	bool isKeyPressed(Uint32 key);
	bool isKeyJustPressed(Uint32 key);
	bool isKeyReleased(Uint32 key);

	bool isMouseButtonPressed(Uint8 button);
	bool isMouseButtonJustPressed(Uint8 button);
	bool isMouseButtonReleased(Uint8 button);
};

#include "../SceneTree/SceneTree.h"
