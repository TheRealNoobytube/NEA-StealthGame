#pragma once
#include "../Application/Data Structures/List.h"

class SceneTree; //forward declaration of SceneTree because SceneTree includes Node, but Node hasn't been defined yet
                 //this would lead to dependency issues and a bunch of errors
                 //first we define Node and then we can include SceneTree so no dependencies are missing

class Node {
private:
	SceneTree* sceneTree;
	Node* parent;
	List<Node*> children;

	std::string name;

public:
	Node(std::string name = "Node");

	virtual void ready();
	virtual void update(float delta);
	virtual void physicsUpdate(float fixedDelta);

	void sceneTreeEntered(SceneTree* sceneTree);
	void sceneTreeExited();

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

};

#include "../SceneTree/SceneTree.h"