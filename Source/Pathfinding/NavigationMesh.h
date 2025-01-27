#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/Collision/CollisionBody.h"

class NavigationMesh : public Node2D{
public:
	NavigationMesh(std::string name = "NavigationMesh");

	~NavigationMesh();

	struct AStarNode {

		AStarNode(Vector2D position = Vector2D(0, 0)) : position(position) {}

		~AStarNode() {
			//std::cout << "DELETED\n";
		}

		Vector2D position;
		bool reachable = true;
		List<AStarNode*> neighbors;
		AStarNode* connection;

		float gCost = 0;
		float hCost = 0;

		float getFCost() {
			return hCost + gCost;
		}


		bool operator == (const AStarNode& node) {
			return this->position == node.position;
		}

		bool operator != (const AStarNode& node) {
			return this->position != node.position;
		}

	};

	int bakingCollisionLayer = 1;

	void ready() override;
	void update(float delta) override;
	
	//void drawSquare(Vector2D pos);

	void bakeMesh();
	Vector2D globalToMap(Vector2D position);

	List<List<AStarNode>*> map;

	Vector2D boxSize = Vector2D(10, 10);
	Vector2D size = Vector2D(96 * 8, 96 * 4);

private:

};