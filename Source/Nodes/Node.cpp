#include "Node.h"


Node::Node(std::string name) {
	id = ID++;
	setName(name);
	this->parent = nullptr;
	this->sceneTree = nullptr;
}

//method for adding children

void Node::addChild(Node* node) {
	if (node->getParent() != nullptr) {
		std::cout << this->name << " cant add " << node->name << " because it already has a parent";
		return;
	}
	node->parent = this;

	this->children.add(node);
	
	if (sceneTree != nullptr) {
		node->sceneTreeEntered(sceneTree);
		sceneTree->readyNodes(node);
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
	Node* node = getChild(index);
	if (sceneTree != nullptr) {
		node->sceneTreeExited();
	}
	node->parent = nullptr;

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




bool Node::hasChild(std::string name) {
	for (int i = 0; i < getChildCount(); i++) {
		if (getChild(i)->name == name) {
			return true;
		}
	}
	return false;
}

bool Node::hasChild(Node* node) {
	for (int i = 0; i < getChildCount(); i++) {
		if (getChild(i) == node) {
			return true;
		}
	}
	return false;
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
	if (isReady) {
		return;
	}
	isReady = true;
	//std::cout << "ready " << name << "\n";
}
void Node::update(float delta) {
	//std::cout << "update " << name << "\n";
}
void Node::physicsUpdate(float fixedDelta) {
	//std::cout << "fixed " << name << "\n";
}


void Node::queueFree() {
	if (getParent() != nullptr) {
		getParent()->removeChild(this);
	}
	getSceneTree()->addToQueueForDeletion(this);
}


Vector2D Node::getMousePosition() {
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	return Vector2D(x, y);
}

void Node::drawRect(Vector2D position, Vector2D size, Color color) {
	SDL_FRect rect = { position.x, position.y, size.x, size.y };
	SDL_SetRenderDrawColor(getSceneTree()->getRenderer(), color.r, color.g, color.b, color.a);
	SDL_RenderFillRectF(getSceneTree()->getRenderer(), &rect);
}


bool Node::isKeyPressed(Uint32 key) {
	return sceneTree->isKeyPressed(key);
}

bool Node::isKeyJustPressed(Uint32 key) {
	return sceneTree->isKeyJustPressed(key);
}

bool Node::isKeyReleased(Uint32 key) {
	return sceneTree->isKeyReleased(key);
}


bool Node::isMouseButtonPressed(Uint8 button) {
	return sceneTree->isMouseButtonPressed(button);
}
bool Node::isMouseButtonJustPressed(Uint8 button) {
	return sceneTree->isMouseButtonJustPressed(button);
}
bool Node::isMouseButtonReleased(Uint8 button) {
	return sceneTree->isMouseButtonReleased(button);
}