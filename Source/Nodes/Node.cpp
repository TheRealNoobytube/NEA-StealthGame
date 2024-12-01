#include "Node.h"
#include <iostream>

Node::Node() {
	this->parent = nullptr;
	this->sceneTree = nullptr;
	this->children = List<Node*>();
}

//method for adding children

void Node::addChild(Node* node) {
	if (node->getParent() != nullptr) {
		std::cout << this->name << " cant add " << node->name << " because it already has a parent";
		return;
	}

	this->children.add(node);
	
	if (sceneTree != nullptr) {
		node->sceneTreeEntered(sceneTree);
		this->sceneTree->readyNodes(node);
	}
}

//methods for removing children

void Node::removeChild(std::string name) {
	removeChild(getChild(name));
}

void Node::removeChild(Node* node) {
	removeChild(this->children.find(node));
}

void Node::removeChild(int index) {
	if (sceneTree != nullptr) {
		getChild(index)->sceneTreeExited();
	}
	this->children.remove(index);
}



void Node::sceneTreeEntered(SceneTree* sceneTree) { //pre-order depth first traversal
	setSceneTree(sceneTree);
	for (int i = 0; i < getChildCount(); i++) {
		getChild(i)->sceneTreeEntered(sceneTree);
	}
}

void Node::sceneTreeExited() { //pre-order depth first traversal
	setSceneTree(nullptr);
	for (int i = 0; i < getChildCount(); i++) {
		getChild(i)->sceneTreeExited();
	}
}



//methods for getting children

Node* Node::getChild(std::string name) {
	for (int i = 0; i < this->children.getSize(); i++) {
		if (children.get(i)->name == name) {
			return children.get(i);
		}
	}
	return nullptr;
}

Node* Node::getChild(int index) {
	return this->children.get(index);
}

List<Node*> Node::getChildren() {
	return this->children;
}

int Node::getChildCount() {
	return this->children.getSize();
}

void Node::setName(std::string name) {
	this->name = name;
}

std::string Node::getName() {
	return this->name;
}


Node* Node::getParent() {
	return this->parent;
}

SceneTree* Node::getSceneTree() {
	return this->sceneTree;
}

void Node::setSceneTree(SceneTree* sceneTree) {
	this->sceneTree = sceneTree;
}

void Node::ready() {
	std::cout << "ready " << name << "\n";
}
void Node::update(float delta) {
	std::cout << "update " << name << "\n";
}
void Node::physicsUpdate(float fixedDelta) {
	std::cout << "fixed " << name << "\n";
}